import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras import optimizers
#데이터셋 설정
X = np.array([[73, 80, 75],
              [93, 88, 93],
              [89, 91, 90],
              [96, 98, 100],
              [73, 66, 70]])

Y = np.array([72, 88, 92, 100, 71])

X_test = np.array([[90, 88, 93], [70, 70, 70]])
#모델 구성
model = Sequential()
model.add(Dense(1, input_dim=3, activation='linear'))

#모델 컴파일
sgd = optimizers.SGD(lr=0.00001) #하이퍼파라미터 lr = 학습률
model.compile(optimizer=sgd, loss='mse', metrics=['mse'])

#모델 학습
model.fit(X, Y, batch_size=1, epochs=100, shuffle=False)

#모델 예측
print(model.predict([X_test]))
