#include <iostream>
#include <vector>
#include "SOM.hpp"

using namespace std;


vector<double *> getRandomVectors(int,int,double,double,int);

int main()
{
  //各設定変数の初期化
  int vectorLength = 3;
  int vectorNum = 100000;
  double min = 0.;
  double max = 1.;
  int seed = 1111;
  int trainIteration = 1;
  int size = 20;

  //SOMインスタンスを作成し，初期化
  SOM<double> som;
  som._init(vectorLength,size,size,seed,min,max);

  //学習に使うベクトル群を生成
  vector<double *> vecs = getRandomVectors(vectorNum, vectorLength, min, max ,seed);

  //学習開始
  cout << "start" <<endl;
  som._train(vecs,trainIteration);

  //学習結果を保存
  cout << "save" << endl;
  som._save("result.csv");
  return 0;
}

/**
 * 指定された範囲・数・長さの乱数を生成してvectorに格納し返す関数
 * @param vectorNum    ベクトルの長さ
 * @param vectorLength ベクトルの数
 * @param min          乱数の下限
 * @param max          乱数の上限
 * @param seed         乱数のシード値
 */
vector<double *> getRandomVectors(int vectorNum,int vectorLength,double min,double max,int seed)
{
  vector<double *> vec;
  double** tmp = new double*[vectorNum];
  mt19937 rand_src(seed);
  uniform_real_distribution<> randD(min,max);
  for(int iter = 0;iter < vectorNum;iter++)
  {
    tmp[iter] = new double[vectorLength];
    for(int i = 0;i < vectorLength;i++)
    {
      tmp[iter][i] = randD(rand_src);
    }
    vec.push_back(tmp[iter]);
  }
  return vec;
}
