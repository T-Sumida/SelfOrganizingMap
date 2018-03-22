#ifndef SOM_h
#define SOM_h

#include <vector>
#include <math.h>
#include <fstream>
#include "Buffer3D.hpp"

template <class T> class SOM
{
private:
  /**
   * 学習率
   */
  double _learnningRatio;
  /**
   * 自己組織化マップの縦数
   */
  unsigned int _row;
  /**
   * 自己組織化マップの横数
   */
  unsigned int _col;
  /**
   * 入力ベクトルの次元数
   */
  unsigned int _N;
  /**
   * ある入力ベクトルに最もマッチしたベクトルを持つ自己組織化マップの座標を保持する配列
   * 0 : row , 1 : col
   */
  unsigned int _bestIndex[2];
  /**
   * 自己組織化マップのデータを保持するクラスインスタンス
   */
  Buffer3D<T> _map;

  /**
   * 2つのベクトルの距離を計算し，返す関数
   * @param  data1 ベクトル１
   * @param  data2 ベクトル２
   * @return       ２ベクトルの距離
   */
  inline T _calcDistance(T* data1,T* data2)
  {
    T sum = 0.0;
    T norm1 = 0.0;
    T norm2 = 0.0;
    for(int i = 0;i < this->_N;i++)
    {
      norm1 += data1[i];
      norm2 += data2[i];
    }
    norm1 = sqrt(norm1);
    norm2 = sqrt(norm2);
    for(int i = 0;i < this->_N;i++)
      sum += (data1[i]/norm1-data2[i]/norm2) * (data1[i]/norm1-data2[i]/norm2);
    return sqrt(sum);
  }

  /**
   * 入力されたデータに最も近いMapデータを探索し，その座標を保存する関数
   * @param data 探索したいデータ
   */
  void _getBestMatchingNodeIndex(T* data)
  {
    T min = 1.0e+11;
    for(int i = 0;i < this->_row;i++)
    {
      for(int j = 0;j < this->_col;j++)
      {
        T distance = _calcDistance(data, this->_map._getVector(i,j));
        if(min > distance)
        {
          min = distance;
          this->_bestIndex[0] = i;
          this->_bestIndex[1] = j;
        }
      }
    }
  }

  /**
   * Alpha値（更新回数によって変動する値）を計算して返す関数
   * @param  now   今回の更新回数
   * @param  total 全更新回数
   * @return       Alpha値
   */
  double _getAlpha(unsigned int now,unsigned int total)
  {
    return (1 - double(now)/double(total));
  }

  /**
   * _map内のデータを更新する関数
   * @param bestX 今回のデータに最も近い_mapの座標X
   * @param bestY 今回のデータに最も近い_mapの座標Y
   * @param alpha Alpha値
   * @param data  今回のデータ
   */
  void _updateNode(unsigned int bestX,unsigned int bestY,double alpha,T* data)
  {
    for(int i = 0;i < this->_row;i++)
    {
      for(int j = 0;j < this->_col;j++)
      {
        T dis = sqrt(pow(this->_bestIndex[0]-i,2) + pow(this->_bestIndex[1]-j,2));
        T bias = this->_learnningRatio * exp(-(dis*dis)/(alpha*alpha));
        for(int c = 0; c < this->_N;c++)
        {
          this->_map._getVector(i,j)[c] +=  bias * (data[c] - this->_map._getVector(i,j)[c]);
        }
      }
    }
  }

public:
  /**
   * 初期化関数
   * @param N    ベクトルの長さ
   * @param row  自己組織化マップの縦数
   * @param col  自己組織化マップの横数
   * @param seed 乱数のシード値
   */
  void _init(int N,int row,int col,unsigned int seed,T min,T max)
  {
    this->_row = row;
    this->_col = col;
    this->_N = N;
    this->_learnningRatio = 0.2;
    _map._resize(row,col,N);
    _map._random(seed,min,max);
  }

  /**
   * 自己組織化マップの学習を行う関数
   * @param vectors 学習に使うベクトル（配列）を格納したstd::vector
   * @param iter    最大更新回数
   */
  void _train(std::vector<T*> vectors,unsigned int iter)
  {
    for(int i = 0;i < iter;i++)
    {
      for(int c = 0; c < vectors.size();c++)
      {
        _getBestMatchingNodeIndex(vectors[c]);
        _updateNode(this->_bestIndex[0],this->_bestIndex[1],this->_getAlpha(i, iter), vectors[c]);
      }
    }
  }

  /**
   * 学習率のセッター
   * @param ratio 学習率
   */
  void _setLearningRation(double ratio){ this->_learnningRatio = ratio; }

  /**
   * _mapの情報をCSV形式に書き出す関数
   * 1行目に自己組織化マップの「縦数, 横数, ベクトル長」を記述
   * 2行目からは「縦インデックス, 横インデックス, ベクトル・・・」となっている
   */
  void _save(const char* filename)
  {
    std::ofstream ofs;
    ofs.open(filename);
    ofs << this->_row << "," << this->_col << "," << this->_N << std::endl;
    for(int i = 0;i < this->_row;i++)
    {
      for(int j = 0;j < this->_col;j++)
      {
        ofs << i << "," << j;
        for(int c = 0; c < this->_N;c++)
        {
          ofs << "," << this->_map._getVector(i,j)[c];
        }
        ofs << std::endl;
      }
    }
  }
};
#endif
