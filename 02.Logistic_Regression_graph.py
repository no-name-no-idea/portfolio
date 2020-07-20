import numpy as np
import matplotlib.pyplot as plt

def sigmoid(wx):
    return 1/(1 + np.exp(-wx))

wx = np.arange(-8.0, 8.0, 0.1)
y = sigmoid(wx)

plt.plot(wx, y, 'b')#x축 , y축, 색깔
plt.grid()
plt.xlabel('z', size = 10)
plt.ylabel('(z)', size = 10)
plt.title('Logistic | Sigmoid function')

plt.show()