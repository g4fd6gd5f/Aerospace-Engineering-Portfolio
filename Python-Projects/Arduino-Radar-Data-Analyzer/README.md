# Arduino Radar Data Analyzer

This project is a Python data analysis tool for Arduino radar sensor data.

It reads angle-distance measurements from an Arduino radar system, identifies object detections based on a distance threshold, calculates summary statistics, and generates a distance-versus-angle plot.

## Project Overview

This project builds on an Arduino radar detection system that uses an ultrasonic sensor mounted on a servo motor. The Arduino measures distance at different scan angles and outputs angle-distance data.

The Python analyzer processes this data to identify where objects were detected during the radar sweep.

## Features

- Reads radar angle-distance data from a CSV file
- Identifies object detections below a selected distance threshold
- Finds the closest detected object
- Calculates the average detected distance
- Exports a detection summary CSV file
- Generates a distance-versus-angle plot

## Files

- [`radar_data_analyzer.py`](./radar_data_analyzer.py) — Python analysis script
- [`sample_radar_data.csv`](./sample_radar_data.csv) — sample radar scan data
- [`detection_summary.csv`](./detection_summary.csv) — exported detection summary
- [`distance_vs_angle_plot.png`](./distance_vs_angle_plot.png) — generated plot

## Input Data Format

The input CSV file uses this format:

```csv
angle,distance_cm
15,80
20,78
25,75
