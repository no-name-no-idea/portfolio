import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import numpy as np
from keras.utils import np_utils
from sklearn.preprocessing import LabelEncoder

X = np.array(['dog', 'cat', 'fish', 'bird'])

#라벨인코더 생성
encoder = LabelEncoder()

#숫자로 변환
encoder.fit(X)
y = encoder.transform(X)
print(y)

#디코더
print(encoder.inverse_transform([3,2,1,0]))

#one_hot_encoding
Y = np_utils.to_categorical(y)
print(Y)

