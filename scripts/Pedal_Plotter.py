"""
Created by Marshal Stewart
4/25/22

Used to parse csv file from teensy with pedal position information

"""


import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

f = open("pedal_data.csv", "r")
buffer = f.readlines()
f.close()

pedal_0 = list(range(len(buffer)))
pedal_1 = list(range(len(buffer)))

for i, val in enumerate(buffer):
    pedal_0[i], pedal_1[i] = val.replace('\n', '').split(',')

for i in range(len(buffer)):
    pedal_0[i] = int(pedal_0[i])
    pedal_1[i] = int(pedal_1[i])

print(pedal_0, pedal_1)

x = list(range(0, len(buffer)))
for i, val in enumerate(x):
    x[i] = val*100

plt.plot(x, pedal_0, label="Pedal 0")
plt.plot(x, pedal_1, label="Pedal 1")
plt.title('Acceleration Pedal Curve')
plt.xlabel('Time (ms)')
plt.ylabel('ADC Reading')
plt.legend(loc="upper left")

plt.tight_layout()
plt.show()



