import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score
from sklearn.neighbors import KNeighborsClassifier
import streamlit as st

data=pd.read_csv('iotfeed.csv')
X=data.iloc[:,1:3].values
Y=data.iloc[:,-1].values

X_train,X_test,Y_train,Y_test=train_test_split(X,Y,test_size=0.3)

classifier=KNeighborsClassifier()
classifier.fit(X_train,Y_train)

st.header('ML Model Prediction for IoT Data')

hum=st.text_input('Enter Humidity')
temp=st.text_input('Enter Temperature')

if st.button('predict'):
    hum=float(hum)
    temp=float(temp)
    output=classifier.predict([[hum,temp]])
    output=output[0]
    st.success('Label: {}'.format(output))