# @author Ugur Turhal
# This python skript reads a CSV file, which
# is filtered and Plots in a log Plot the temperature

import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.style.use('seaborn')


def main():
    df = pd.read_csv("groupeddata.csv", usecols=['Measurement', 'Temperature']).drop_duplicates(keep='first').reset_index()
    measurement = df['Measurement']
    temperature = df['Temperature']
    df.to_csv("cleanData.csv");
    colors = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
              30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55,
              56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81,
              82, 83, 84, 85, 86, 87, 88, 89, 90]

    plt.scatter(x=measurement, y=temperature, s=25, c=colors, alpha=0.6, edgecolor='black', linewidth=1,
                    cmap='Blues_r')

    cbar = plt.colorbar()
    cbar.set_label('Mesurements with Temperature')
    plt.xscale('log')
    plt.yscale('log')
    plt.title('Scatter of Temperature')
    plt.xlabel('Measurement')
    plt.ylabel('Temperature')

    plt.savefig("data.png")
    plt.show()


if __name__ == "__main__":
    print(main())
