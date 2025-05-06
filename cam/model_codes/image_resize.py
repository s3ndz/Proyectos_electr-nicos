import cv2
import os
import numpy as np

def load_and_resize_images(folder, target_size=(96, 96)):
    images = []
    for filename in os.listdir(folder):
        if filename.endswith(".jpg") or filename.endswith(".png"):
            img_path = os.path.join(folder, filename)
            img = cv2.imread(img_path)
            if img is not None:
                resized = cv2.resize(img, target_size)
                images.append(resized)
        if len(images) >= 100:
            break
    return np.array(images, dtype=np.uint8)

# Example usage for quantization
my_sample_data = load_and_resize_images("pothole_dataset/train/images", (96, 96))
