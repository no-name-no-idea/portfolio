import numpy as np
import matplotlib.pyplot as plt

def odds(p):
    return np.log(p/(1-p))

p = np.arange(0.001, 0.999, 0.001)
z = [odds(n) for n in p]

plt.plot(p, z)
plt.xlabel('p')
plt.ylabel('logit')

plt.show()