#pragma once

template<class T >class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x, T y);
	~Vector2Temple();
	T x;
	T y;
	//二項演算子
	Vector2Temple operator +(Vector2Temple vec); //operatorは日本語で演算子となる　そのあとに演算子の何？とくる。
	Vector2Temple operator -(Vector2Temple vec);
	Vector2Temple operator *(Vector2Temple vec);
	Vector2Temple operator /(Vector2Temple vec);
	Vector2Temple operator %(Vector2Temple vec);

	//代入演算子
	Vector2Temple& operator =(const Vector2Temple& vec);

	//添え字演算子
	int& operator[](int j );

	//単項演算子
	Vector2Temple& operator += (const Vector2Temple& vec);
	Vector2Temple& operator -= (const Vector2Temple& vec);
	Vector2Temple& operator *= (const Vector2Temple& vec);
	Vector2Temple& operator /= (const Vector2Temple& vec);
	Vector2Temple& operator %= (const Vector2Temple& vec);
	Vector2Temple operator +() const;
	Vector2Temple operator -() const;

	//比較演算子
	bool operator ==(const Vector2Temple& vec)const;
	bool operator !=(const Vector2Temple& vec)const;
	bool operator <=(const Vector2Temple& vec)const;
	bool operator <(const Vector2Temple& vec)const;
	bool operator >=(const Vector2Temple& vec)const;
	bool operator >(const Vector2Temple& vec)const;
	
};
template<class T>
Vector2Temple<T> operator + (const Vector2Temple<T>& u, T k);		//外に書く最大の理由はconstがつけれるつけれない
template<class T>
Vector2Temple<T> operator - (const Vector2Temple<T>& u, T k);
template<class T>
Vector2Temple<T> operator * (const Vector2Temple<T>& u, T k);
template<class T>
Vector2Temple<T> operator / (const Vector2Temple<T>& u, T k);
template<class T>
Vector2Temple<T> operator % (const Vector2Temple<T>& u, T k);

using Vector2 = Vector2Temple<int>;
using Vector2Flt = Vector2Temple<float>;
using Vector2Dbl = Vector2Temple<double>;

#include"Detail/Vector2.h"
