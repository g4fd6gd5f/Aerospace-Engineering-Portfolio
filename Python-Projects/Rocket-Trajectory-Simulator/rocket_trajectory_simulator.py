import math
import csv
import matplotlib.pyplot as plt


def simulate_trajectory(
    initial_velocity,
    launch_angle_deg,
    mass,
    drag_coefficient,
    cross_sectional_area,
    air_density,
    time_step,
):
    g = 9.81

    angle_rad = math.radians(launch_angle_deg)

    vx = initial_velocity * math.cos(angle_rad)
    vy = initial_velocity * math.sin(angle_rad)

    x = 0.0
    y = 0.0
    t = 0.0

    time_values = []
    x_values = []
    y_values = []
    vx_values = []
    vy_values = []
    speed_values = []
    drag_values = []

    while True:
        speed = math.sqrt(vx**2 + vy**2)

        drag_force = 0.5 * air_density * drag_coefficient * cross_sectional_area * speed**2

        if speed > 0:
            drag_x = drag_force * (vx / speed)
            drag_y = drag_force * (vy / speed)
        else:
            drag_x = 0.0
            drag_y = 0.0

        ax = -drag_x / mass
        ay = -g - (drag_y / mass)

        time_values.append(t)
        x_values.append(x)
        y_values.append(max(y, 0))
        vx_values.append(vx)
        vy_values.append(vy)
        speed_values.append(speed)
        drag_values.append(drag_force)

        vx += ax * time_step
        vy += ay * time_step

        x += vx * time_step
        y += vy * time_step

        t += time_step

        if y < 0 and t > 0:
            break

        if t > 300:
            print("Simulation stopped after 300 seconds to avoid infinite loop.")
            break

    return {
        "time": time_values,
        "x": x_values,
        "y": y_values,
        "vx": vx_values,
        "vy": vy_values,
        "speed": speed_values,
        "drag": drag_values,
    }


def save_results_to_csv(results, filename):
    with open(filename, mode="w", newline="") as file:
        writer = csv.writer(file)

        writer.writerow([
            "time_s",
            "x_position_m",
            "y_position_m",
            "x_velocity_m_s",
            "y_velocity_m_s",
            "speed_m_s",
            "drag_force_N",
        ])

        for i in range(len(results["time"])):
            writer.writerow([
                results["time"][i],
                results["x"][i],
                results["y"][i],
                results["vx"][i],
                results["vy"][i],
                results["speed"][i],
                results["drag"][i],
            ])


def plot_trajectory(results):
    plt.figure(figsize=(10, 6))
    plt.plot(results["x"], results["y"], marker=".", markersize=2)
    plt.xlabel("Horizontal Distance (m)")
    plt.ylabel("Altitude (m)")
    plt.title("Rocket / Projectile Trajectory with Drag")
    plt.grid(True)
    plt.savefig("trajectory_plot.png", dpi=300)
    plt.show()


def plot_velocity(results):
    plt.figure(figsize=(10, 6))
    plt.plot(results["time"], results["speed"], marker=".", markersize=2)
    plt.xlabel("Time (s)")
    plt.ylabel("Speed (m/s)")
    plt.title("Speed vs Time")
    plt.grid(True)
    plt.savefig("velocity_plot.png", dpi=300)
    plt.show()


def print_summary(results):
    max_height = max(results["y"])
    range_distance = results["x"][-1]
    flight_time = results["time"][-1]
    max_speed = max(results["speed"])
    max_drag = max(results["drag"])

    print("\n========== Simulation Summary ==========")
    print(f"Number of time steps: {len(results['time'])}")
    print(f"Flight time:          {flight_time:.2f} s")
    print(f"Range:                {range_distance:.2f} m")
    print(f"Maximum height:       {max_height:.2f} m")
    print(f"Maximum speed:        {max_speed:.2f} m/s")
    print(f"Maximum drag force:   {max_drag:.2f} N")
    print("========================================")


def get_positive_float(prompt):
    while True:
        try:
            value = float(input(prompt))
            if value <= 0:
                print("Enter a positive number.")
            else:
                return value
        except ValueError:
            print("Invalid input. Enter a number only.")


def main():
    print("========================================")
    print(" Rocket / Projectile Trajectory Simulator")
    print("========================================\n")

    print("Use numbers only. Do not type units.\n")

    initial_velocity = get_positive_float("Enter initial velocity (m/s): ")
    launch_angle_deg = get_positive_float("Enter launch angle (degrees): ")
    mass = get_positive_float("Enter mass (kg): ")
    drag_coefficient = get_positive_float("Enter drag coefficient Cd: ")
    cross_sectional_area = get_positive_float("Enter cross-sectional area (m^2): ")
    air_density = get_positive_float("Enter air density (kg/m^3): ")
    time_step = get_positive_float("Enter time step (s): ")

    if launch_angle_deg >= 90:
        print("For this simple model, use an angle below 90 degrees.")
        return

    results = simulate_trajectory(
        initial_velocity,
        launch_angle_deg,
        mass,
        drag_coefficient,
        cross_sectional_area,
        air_density,
        time_step,
    )

    print_summary(results)
    save_results_to_csv(results, "simulation_results.csv")
    plot_trajectory(results)
    plot_velocity(results)

    print("\nFiles created:")
    print("- simulation_results.csv")
    print("- trajectory_plot.png")
    print("- velocity_plot.png")


if __name__ == "__main__":
    main()