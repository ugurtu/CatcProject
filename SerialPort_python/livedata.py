# @author Ugur Turhal

# This python file reads the serial port of the Arduino and gives a live plot
import serial
import time
import csv
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

matplotlib.use("tkAgg")

ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

plot_window = 360
y_var = np.array(np.zeros([plot_window]))

plt.ion()
fig, ax = plt.subplots()
ax.grid(linestyle="--")
ax.set_ylabel("°Celsius")
ax.set_xlabel("x")
ax.set(xlabel='x', ylabel='°Celsius',
       title='Increase & Decrease of \n Temperature')
line, = ax.plot(y_var)

while True:
    try:
        ser_bytes = ser.readline()
        try:
            decoded_bytes = ser_bytes[0:len(ser_bytes) - 2].decode("utf-8")
            print(decoded_bytes)
        except:
            continue
        with open("test_data.csv", "a") as f:
            writer = csv.writer(f, delimiter=",")
            writer.writerow([time.time(), decoded_bytes])
        y_var = np.append(y_var, decoded_bytes)
        y_var = y_var[1:plot_window + 1]
        line.set_ydata(y_var)
        ax.relim()
        ax.autoscale_view()
        fig.canvas.draw()
        fig.canvas.flush_events()
        fig.savefig('full_figure.png')

    except:
        print("Stopped")
        break
