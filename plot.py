import numpy as np
import sys
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import linear_model

if len(sys.argv) != 2:
    print("Wrong arguments")
    sys.exit(1)

df = pd.read_csv(sys.argv[1], sep=';', names=['valves', 'edges', 'time'])

v = df['valves']
e = df['edges']
t = df['time']

X = df.iloc[:, [0,1]]
complexity = v*e*e + v*v*e
y = t

regressor = linear_model.LinearRegression()
regressor.fit(X, t)
y_pred = regressor.predict(X)

mediana = int(len(df.index) / 2)
t_mediana = np.array(t)[mediana]
vm = np.array(v)[mediana]
em = np.array(e)[mediana]
T_mediana = vm*em*em + vm*vm*em
T = np.array(complexity)


res = np.array([v, e, t * T_mediana / (T * t_mediana)])

res = np.transpose(res)
np.savetxt("tabelka.csv", res, delimiter=";", fmt="%f")

fig = plt.figure()
plt.scatter(complexity, y, color="black")
plt.plot(complexity, y_pred, color="blue", linewidth=3.0)
plt.xlabel('Predicted complexity: E*V^2 + V*E^2')
plt.ylabel('Time')
plt.show()
fig.savefig("plot.png")

