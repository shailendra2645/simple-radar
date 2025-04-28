import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import serial

sensor_range = 100
frames = 181

# Set up the serial connection (make sure the port and baud rate match your Arduino)
ser = serial.Serial('COM3', 9600, timeout=1)  # Replace 'COM3' with your port
angles = np.zeros(shape=frames)
distances = np.zeros(shape=frames)

 
 
# Create a figure and polar axis
fig = plt.figure(facecolor="k")
ax = fig.add_subplot(111, projection='polar')

# Initial plot with line from center at 0 degrees
line, = ax.plot([], [], lw=2, color="g")
points, = ax.plot([], [], "ow")


def init():
    """Function to initialize the plot"""
    ax.set_ylim(0, sensor_range)
    ax.set_facecolor("k")
    ax.grid(color="g")
    ax.tick_params(colors="green")
    return line,

# Function to update the line for each frame


def update(frame):
    if frame > 180:
        frame -= 180
    angle = np.radians(frame)  # Convert degrees to radians
    # Plot from (0,0) to the line at the angle
    line.set_data([0, angle], [0, sensor_range])
    data = ser.readline().decode("utf-8").strip()
    if data:
        try:
            angle, distance = map(float, data.split(","))
            angles[frame], distances[frame] = np.deg2rad(angle), distance
            points.set_data(angles[:frame], distances[:frame])
        except ValueError:
            pass

    return line, points


# Create the animation for 180 degrees
ani = FuncAnimation(fig, update, frames=np.arange(0, 361),
                    init_func=init, blit=False, interval=10)

# Display the animation
plt.show()
