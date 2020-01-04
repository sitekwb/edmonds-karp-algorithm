import numpy as np
import sys
import pandas as pd
import matplotlib.pyplot as plt

if len(sys.argv) != 2:
    print("Wrong arguments")
    sys.exit(1)

df = pd.read_csv(sys.argv[1], sep=';', names=['valves', 'edges', 'time'])

v = df['valves']
e = df['edges']
t = df['time']

fig = plt.figure()
plt.plot(v*e*e + v*v*e, t)
plt.xlabel('Predicted complexity: E*V^2 + V*E^2')
plt.ylabel('Time')
plt.show()
fig.savefig("plot.png")
