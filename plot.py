# -*- coding:utf-8 -*-

"""
テストプログラム（main.cpp）で書き出された result.csv を読み込み，カラーマップを描画するプログラム．
基本的にベクトル長=3でしか動かない．（本当にテスト用）
"""


import matplotlib.pyplot as plt
import csv
import numpy as np
f = open("result.csv")
reader = csv.reader(f)
counter = 0
data = np.zeros([100,100,3])
x = 0
y = 0
z = 0
for d in reader:
    # print(counter,d)
    if counter == 0:
        data = np.zeros([int(d[0]),int(d[1]),int(d[2])])
        x = int(d[0])
        y = int(d[1])
        z = int(d[2])
        counter += 1
    else:
        counter +=1
        data[int(d[0])][int(d[1])] = d[2:]

plt.imshow(data.reshape((x,y,z)),
           interpolation='none')
plt.show()
