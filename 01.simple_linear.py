import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras import optimizers
#데이터셋 설정
공부시간 = np.array([1, 2, 3, 4, 5, 6])
점수결과 = np.array([10,20,30,40,50,60])

#모델 구성
model = Sequential()
model.add(Dense(1, input_dim=1, activation='linear')) #Dense는 계층 Dense(출력인자, 입력인자, 활성함수)

#모델 컴파일
sgd = optimizers.SGD(lr=0.01) #하이퍼파라미터 lr = 학습률
model.compile(optimizer=sgd, loss='mse', metrics=['accuracy'])#optimizer = 최적화 방식, loss = 손실함수부분, #metrics = 평가기준률
#손실함수 종류 mse(선형회귀) binary_crossentropy(로지스틱 회귀(2진분류)) categorical_crossentropy(소프트맥스 회귀(다중클래스 분류))

#모델 학습
model.fit(공부시간, 점수결과, batch_size=1, epochs=100, shuffle=False)#batch_size 데이터묶음 ,epochs 몇번 학습할껀지, shuffle 섞을껀지

#모델 예측
print(model.predict([10]))

