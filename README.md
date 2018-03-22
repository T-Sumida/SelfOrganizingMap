# SelfOrganizingMap
## Overview
C++で実装した自己組織化マップアルゴリズム．

バッチ処理は現在実装しておらず，逐次処理のみを実装しています．

コード内に問題がある可能性があるので、もしお気づきになられたら修正 or 連絡をお願い致します。


## Usage
テストプログラムは make を用いればコンパイルされ， ./main で実行されます．
```
$ make all
$ ./main
```
で実行可能です．

テストプログラムでは，RGB色空間に対してのSOMを実行しており，その結果を result.csv として書き出しています．

```
$ python plot.py
```
を実行すれば，結果をカラーマップで確認することができます．


## Requirement
C++11

GNU Make 3.81

Python 3.6.0

numpy 1.14.1

matplotlib 2.1.2


## License
Copyright © 2016 T_Sumida Distributed under the MIT License.
