import tensorflow as tf
import numpy as np
import os
from PIL import Image

# === CONFIGURATION ===
saved_model_dir = "C:\\Users\\daisy\\Documents\\Proyectos_electr-nicos\\out\\saved_model"
image_dir = "C:\\Users\\daisy\Downloads\\Pothole Detection.v10-v5-rotation-only.coco\\train"
output_tflite_file = "model_uint8.tflite"
image_size = (96, 96)  # (width, height)

# === LOAD IMAGES FOR REPRESENTATIVE DATASET ===
def load_images_from_folder(folder, size=(96, 96), max_images=100):
    image_list = []
    count = 0
    for filename in os.listdir(folder):
        if filename.lower().endswith(('.png', '.jpg', '.jpeg')) and count < max_images:
            image_path = os.path.join(folder, filename)
            img = Image.open(image_path).convert('RGB')
            img = img.resize(size)
            img_array = np.array(img, dtype=np.uint8)
            image_list.append(img_array)
            count += 1
    return np.array(image_list)

# Load a sample of representative images
my_sample_data = load_images_from_folder(image_dir, size=image_size, max_images=100)

# === REPRESENTATIVE DATASET GENERATOR ===
def representative_data_gen():
    for input_value in my_sample_data:
        input_value = np.expand_dims(input_value, axis=0)  # shape: (1, 96, 96, 3)
        yield [input_value.astype(np.uint8)]

# === CONVERT TO TFLITE ===
converter = tf.lite.TFLiteConverter.from_saved_model(saved_model_dir)
converter.target_spec.supported_ops = [
    tf.lite.OpsSet.TFLITE_BUILTINS,
    tf.lite.OpsSet.SELECT_TF_OPS  # Enable TF Select for unsupported ops
]
converter.optimizations = [tf.lite.Optimize.DEFAULT]
converter.representative_dataset = representative_data_gen
converter.inference_input_type = tf.uint8
converter.inference_output_type = tf.uint8

tflite_model = converter.convert()

# === SAVE TFLITE MODEL ===
with open(output_tflite_file, "wb") as f:
    f.write(tflite_model)

print(f"TFLite model saved to {output_tflite_file}")
