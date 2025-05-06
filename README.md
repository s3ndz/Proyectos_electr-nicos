Smart Pothole Detection System

An embedded system for real-time pothole detection and data logging using ESP32-based microcontrollers, designed to assist organizations in monitoring road conditions from moving vehicles.

Overview

This system uses two ESP32 modules to detect potholes, record location data, and transmit it via Wi-Fi for remote visualization and analysis.

- ESP32-S3 Unit (Main Unit)
  - Collects and logs GPS coordinates
  - Reads sensor values ( ultrasonic)
  - Communicates with server (Wi-Fi)
  - Responds to camera alerts to trigger data capture

- ESP32-CAM Unit (Camera Node) 
  - Monitors road using computer vision  
  - Detects visual anomalies (potholes)  
  - Sends alert to Main Unit via serial or Wi-Fi/ESP-NOW
Authors

- Daisy Berríos – Embedded Systems Developer  
- Italo Sessarego – Embedded Systems Developer  
- Sofía Velásquez – Domain Expert  
- Sebastián Zapata – Project Manager  
