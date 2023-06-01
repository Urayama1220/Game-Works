#pragma once

template<class T >class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x, T y);
	~Vector2Temple();
	T x;
	T y;
	//�񍀉��Z�q
	Vector2Temple operator +(Vector2Temple vec); //operator�͓��{��ŉ��Z�q�ƂȂ�@���̂��Ƃɉ��Z�q�̉��H�Ƃ���B
	Vector2Temple operator -(Vector2Temple vec);
	Vector2Temple operator *(Vector2Temple vec);
	Vector2Temple operator /(Vector2Temple vec);
	Vector2Temple operator %(Vector2Temple vec);

	//������Z�q
	Vector2Temple& operator =(const Vector2Temple& vec);

	//�Y�������Z�q
	int& operator[](int j );

	//�P�����Z�q
	Vector2Temple& operator += (const Vector2Temple& vec);
	Vector2Temple& operator -= (const Vector2Temple& vec);
	Vector2Temple& operator *= (const Vector2Temple& vec);
	Vector2Temple& operator /= (const Vector2Temple& vec);
	Vector2Temple& operator %= (const Vector2Temple& vec);
	Vector2Temple operator +() const;
	Vector2Temple operator -() const;

	//��r���Z�q
	bool operator ==(const Vector2Temple& vec)const;
	bool operator !=(const Vector2Temple& vec)const;
	bool operator <=(const Vector2Temple& vec)const;
	bool operator <(const Vector2Temple& vec)const;
	bool operator >=(const Vector2Temple& vec)const;
	bool operator >(const Vector2Temple& vec)const;
	
};
template<class T>
Vector2Temple<T> operator + (const Vector2Temple<T>& u, T k);		//�O�ɏ����ő�̗��R��const����������Ȃ�
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
