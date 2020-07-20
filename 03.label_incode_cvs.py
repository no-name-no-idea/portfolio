import os
os.environ['TF_CPP_MIN_LOG_LEVEL'] = '2'

import pandas as pd
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
print(Y)
