import numpy as np

def softmax(z):
    return np.exp(z)/sum(np.exp(z))
def stable_softmax(z):
    return np.exp(z-max(z))/sum(np.exp(z-max(z)))

a = np.array([1000.0, 2000.0, 3000.0])
print(stable_softmax(a))