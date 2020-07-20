import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'


import numpy as np
import pandas as pd

from keras.models import Sequential
from keras.layers import Dense
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder

df = pd.read_csv('C:\\Users\\user\\Desktop\\pytinstudy\\keras_study\\Iris.csv')

# X 데이터 할당
data_set = df.values
X = data_set[:, 0:4].astype(float)

# Y 데이터 할당
obj_Y = data_set[:, 4]

#LabelEncoder : 수치변환
encoder = LabelEncoder()
encoder.fit(obj_Y)
Y_encodered = encoder.transform(obj_Y)

#one-hot-encoding
Y = pd.get_dummies(Y_encodered).values

model = Sequential()
model.add(Dense(16, input_dim=4, activation='relu'))
model.add(Dense(3, activation='softmax'))

model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
model.fit(X, Y, epochs=100, batch_size=1)

print(model.predict(np.array([[4.7, 3.2, 1.3, 0.2]])))
