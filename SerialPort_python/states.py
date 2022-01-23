# @author Ugur Turhal

# This python file reads the serial port of the Arduino and
# reads the state of the LEDs out and Shows the Temperature

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import serial
import time
import csv
from drawnow import *

plt.style.use('seaborn')
ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

ledRedPin = []
ledGreen = []
temperature = []


def makeFig():
    plt.close("all")
    plt.title('HIGH and LOW of \n selected pins')
    plt.ylim(0, 1.5, 0.4)
    plt.plot(ledRedPin, label='digitalRead_Red', color='red')
    plt.legend(bbox_to_anchor=(1.0, 0.5), loc='upper left')

    plt2 = plt.twinx()
    plt.ylim(0, 30, 6)
    plt2.plot(temperature, label='°C')
    plt2.legend(bbox_to_anchor=(1.0, 1.01), loc='upper left')

    plt3 = plt.twinx();
    plt.ylim(0, 1.5)
    plt3.plot(ledGreen, label='digitalRead_Green', color='green')
    plt3.legend(bbox_to_anchor=(1.0, 0), loc='upper left')

    plt.tight_layout()
    plt.savefig("digitalRead.png")


def main():
    while True:
        ser_bytes = ser.readline()
        while ser.inWaiting() == 0:
            pass
        try:
            r = float(ser_bytes[0:1].decode("utf-8"));
            g = float(ser_bytes[1:len(ser_bytes) - 7].decode("utf-8"));
            temp = float(ser_bytes[3:len(ser_bytes)].decode("utf-8"));
            ledRedPin.append(r)
            temperature.append(temp)
            ledGreen.append(g)
            drawnow(makeFig)
        except:
            continue
            print("ERROR")
        with open("states.csv", "a") as f:
            writer = csv.writer(f, delimiter=",")
            writer.writerow([r, g, temp])


if __name__ == '__main__':
    print(main())
