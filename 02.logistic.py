import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras import optimizers

import matplotlib.pyplot as plt

X=np.array([-10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
Y=np.array([  0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1])

model = Sequential()
model.add(Dense(1, input_dim=1, activation='sigmoid'))
sgd = optimizers.SGD(lr=0.01)
model.compile(optimizer=sgd, loss='binary_crossentropy', metrics=['binary_accuracy']) #sigmoid는 손실함수로 binary_crossentropy 사용
model.fit(X, Y, batch_size=1, epochs=1000, shuffle=False)

print(model.predict([8.1])) #threshold 0.5 이상으로
print(model.predict([6.9]))
plt.plot(X, model.predict(X), 'b', X, Y, 'k.')
plt.show()