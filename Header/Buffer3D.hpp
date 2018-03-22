#ifndef Buffer2D_h
#define Buffer2D_h
#include <random>
#include <iostream>

template <class T> class Buffer3D
{
private:
  /**
   * ３次元配列の第一インデックスの数
   */
  unsigned int _x;
  /**
   * 3次元配列の第二インデックスの数
   */
  unsigned int _y;
  /**
   * ３次元配列の第三インデックスの数
   */
  unsigned int _z;
  /**
   * データ本体の配列
   */
  T*** _value;

  /**
   * 配列のメモリを開放する関数
   */
  void _free()
  {
    if(this->_value)
    {
      for(int i = 0;i < this->_x;i++)
      {
        for(int j = 0;j < this->_y;j++)
          if(this->_value[i][j]) delete [] this->_value[i][j];
        delete [] this->_value[i];
      }
      delete [] this->_value;
    }
  }

public:
  /**
   * コンストラクタ
   * 各変数を初期化
   */
  Buffer3D()
  {
    this->_value = nullptr;
    this->_x = 0;
    this->_y = 0;
    this->_z = 0;
  }

  /**
   * デストラクタ
   * メモリ解放
   */
  ~Buffer3D()
  {
    this->_free();
  }

  /**
   * ３次元配列をリサイズして０で埋める関数
   * @param x 新しい第一インデックスの数
   * @param y 新しい第二インデックスの数
   * @param z 新しい第三インデックスの数
   */
  void _resize(unsigned int x,unsigned int y,unsigned int z)
  {
    this->_free();
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_value = new T**[x];
    for(int i = 0; i < x; i++)
    {
      this->_value[i] = new T*[y];
      for(int j = 0;j < y;j++)
        this->_value[i][j] = new T[z];
    }
    this->_zero();
  }

  /**
   * 指定されたインデックスの配列に引数データをコピーする関数
   * @param x      ３次元配列の第一インデックス
   * @param y      ３次元配列の第二インデックス
   * @param vector コピーするデータ
   */
  void _copy(unsigned int x,unsigned int y,T* vector)
  {
    if(x >= this->_x || x < 0 || y >= this->_y || y < 0 ) return;
    for(int i = 0;i < this->z;i++)
      this->_value[x][y][i] = vector[i];
  }

  /**
   * データを0で埋める関数
   */
  void _zero()
  {
    for(int i = 0;i < this->_x;i++)
      for(int j = 0;j < this->_y;j++)
        for(int c = 0;c < this->_z;c++)
          this->_value[i][j][c] = 0.0;
  }

  /**
   * データを指定された範囲の乱数で初期化する
   * @param seed 乱数のシード値
   * @param min  乱数の下限
   * @param max  乱数の上限
   */
  void _random(unsigned int seed,T min,T max)
  {
    std::mt19937 rand_src(seed);
    std::uniform_real_distribution<> randD(min, max);
    for(int i = 0;i < this->_x;i++)
      for(int j = 0;j < this->_y;j++)
        for(int c=0;c < this->_z;c++)
          this->_value[i][j][c] = randD(rand_src);
  }

  /**
   * 指定された配列のデータを返す関数
   * @param  x ３次元配列の第一インデックス
   * @param  y ３次元配列の第二インデックス
   * @return   指定されたインデックスのベクトル
   */
  T* _getVector(unsigned int x,unsigned int y){ return this->_value[x][y];}

};
#endif
