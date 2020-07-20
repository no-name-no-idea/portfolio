import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import pandas as pd
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras import optimizers

df = pd.read_csv('02.pandas.cvs')
data_set = df.values

X = data_set[:, 0:12] #[모든행, 0~11]
Y = data_set[:, 12]

model = Sequential()
model.add(Dense(30, input_dim=12, activation='relu'))
model.add(Dense(1, activation='sigmoid'))

model.compile(loss='binary_crossentropy', optimizer='sgd', metrics=['accuracy'])

model.fit(X, Y, batch_size=10, epochs=50)

print(model.predict(np.array(6.6, 0.22, 0.23, 17.3, 0.047, 37, 118, 0.99906, 3.08, 0.46, 8.8, 6)))
