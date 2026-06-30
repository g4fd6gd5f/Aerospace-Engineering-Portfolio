import csv
import matplotlib.pyplot as plt


DETECTION_THRESHOLD_CM = 40


def read_radar_data(filename):
    angles = []
    distances = []

    with open(filename, mode="r") as file:
        reader = csv.DictReader(file)

        for row in reader:
            angles.append(float(row["angle"]))
            distances.append(float(row["distance_cm"]))

    return angles, distances


def analyze_detections(angles, distances, threshold):
    detections = []

    for angle, distance in zip(angles, distances):
        if distance <= threshold:
            detections.append({
                "angle": angle,
                "distance_cm": distance
            })

    if detections:
        closest_detection = min(detections, key=lambda item: item["distance_cm"])
        average_detection_distance = sum(item["distance_cm"] for item in detections) / len(detections)
    else:
        closest_detection = None
        average_detection_distance = None

    summary = {
        "total_measurements": len(angles),
        "number_of_detections": len(detections),
        "detection_threshold_cm": threshold,
        "closest_detection": closest_detection,
        "average_detection_distance": average_detection_distance,
        "detections": detections
    }

    return summary


def save_detection_summary(summary, filename):
    with open(filename, mode="w", newline="") as file:
        writer = csv.writer(file)

        writer.writerow(["Metric", "Value"])
        writer.writerow(["Total measurements", summary["total_measurements"]])
        writer.writerow(["Number of detections", summary["number_of_detections"]])
        writer.writerow(["Detection threshold (cm)", summary["detection_threshold_cm"]])

        if summary["closest_detection"] is not None:
            writer.writerow(["Closest detection angle (deg)", summary["closest_detection"]["angle"]])
            writer.writerow(["Closest detection distance (cm)", summary["closest_detection"]["distance_cm"]])
            writer.writerow(["Average detection distance (cm)", summary["average_detection_distance"]])
        else:
            writer.writerow(["Closest detection angle (deg)", "No detection"])
            writer.writerow(["Closest detection distance (cm)", "No detection"])
            writer.writerow(["Average detection distance (cm)", "No detection"])

        writer.writerow([])
        writer.writerow(["Detected angle (deg)", "Distance (cm)"])

        for detection in summary["detections"]:
            writer.writerow([detection["angle"], detection["distance_cm"]])


def plot_distance_vs_angle(angles, distances, threshold):
    detected_angles = []
    detected_distances = []
    clear_angles = []
    clear_distances = []

    for angle, distance in zip(angles, distances):
        if distance <= threshold:
            detected_angles.append(angle)
            detected_distances.append(distance)
        else:
            clear_angles.append(angle)
            clear_distances.append(distance)

    plt.figure(figsize=(10, 6))

    plt.plot(angles, distances, linewidth=1, label="Radar distance reading")
    plt.scatter(clear_angles, clear_distances, label="No object detected")
    plt.scatter(detected_angles, detected_distances, label="Object detected")

    plt.axhline(
        y=threshold,
        linestyle="--",
        label=f"Detection threshold: {threshold} cm"
    )

    plt.xlabel("Angle (degrees)")
    plt.ylabel("Distance (cm)")
    plt.title("Arduino Radar Distance vs Angle")
    plt.grid(True)
    plt.legend()

    plt.savefig("distance_vs_angle_plot.png", dpi=300)
    plt.show()


def print_summary(summary):
    print("\n========== Radar Data Analysis Summary ==========")
    print(f"Total measurements:       {summary['total_measurements']}")
    print(f"Detection threshold:      {summary['detection_threshold_cm']} cm")
    print(f"Number of detections:     {summary['number_of_detections']}")

    if summary["closest_detection"] is not None:
        print(f"Closest object angle:     {summary['closest_detection']['angle']} degrees")
        print(f"Closest object distance:  {summary['closest_detection']['distance_cm']} cm")
        print(f"Average detection dist.:  {summary['average_detection_distance']:.2f} cm")
    else:
        print("No objects detected.")

    print("=================================================\n")


def main():
    input_file = "sample_radar_data.csv"
    output_file = "detection_summary.csv"

    angles, distances = read_radar_data(input_file)

    summary = analyze_detections(
        angles,
        distances,
        DETECTION_THRESHOLD_CM
    )

    print_summary(summary)
    save_detection_summary(summary, output_file)
    plot_distance_vs_angle(
        angles,
        distances,
        DETECTION_THRESHOLD_CM
    )

    print("Files created:")
    print("- detection_summary.csv")
    print("- distance_vs_angle_plot.png")


if __name__ == "__main__":
    main()