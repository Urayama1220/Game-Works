#include "../Vector2.h"


template<class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;
}

template<class T>
Vector2Temple<T>::Vector2Temple(T x, T y)  //:x(x)		//	Ç±ÇÍÇ‡Ç≈Ç‡èëÇØÇ»Ç≠ÇÕÇ»Ç¢Ç™
{
	Vector2Temple::x = x;
	Vector2Temple::y = y;

	 //this->x = x;		//Ç±ÇÍÇ‡ìØÇ∂
	 //this->y = y;		//Ç±ÇÍÇ‡ìØÇ∂

	/*x_ = x;
	y_ = y;*/
}
template<class T>
Vector2Temple<T>::~Vector2Temple()
{

}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator+(Vector2Temple<T> vec)
{
	return Vector2Temple(x + vec.x, y + vec.y);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator-(Vector2Temple<T> vec)
{
	return Vector2Temple(x - vec.x, y - vec.y);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator*(Vector2Temple<T> vec)
{
	return Vector2Temple(x * vec.x, y * vec.y);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator/(Vector2Temple<T> vec)
{
	return Vector2Temple(x / vec.x, y / vec.y);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator%(Vector2Temple<T> vec)
{
	return Vector2Temple(x % vec.x, y % vec.y);
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator=(const Vector2Temple<T>& vec)
{
	//this->x	Ç±Ç§èëÇ≠Ç±Ç∆Ç‡Ç≈Ç´ÇÈ	
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
int& Vector2Temple<T>::operator[](int j)
{
	/*int a[3];
	a[1];*/
	if (j = 0)
	{
		return x;
		if (j = 1)
		{
			return y;
		}
	}
	return x;
}

template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, T k)
{
	
	return { u.x + k,u.y + k};
}

template<class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, T k)
{
	return { u.x - k, u.y - k };
}

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T k)
{
	return { u.x * k ,u.y * k };
}

template<class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& u, T k)
{
	return { u.x / k, u.y / k };
}

template<class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& u, T k)
{
	return { u.x % k, u.y % k };
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple<T>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(const Vector2Temple<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(const Vector2Temple<T>& vec)
{
	if (vec.x )
	{
		x /= vec.x;
	}
	else
	{
		x = 0;
	}
	
	if (vec.y)
	{
		y /= vec.y;
	}
	else
	{
		y = 0;
	}
	
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator%=(const Vector2Temple<T>& vec)
{
	if (vec.x)
	{
		x %= vec.x;
	}
	else
	{
		x = 0;
	}

	if (vec.y)
	{
		y %= vec.y;
	}
	else
	{
		y = 0;
	}
	return *this;
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	return *this;
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	-x;
	-y;
	
	return *this;
}

template<class T>
bool Vector2Temple<T>::operator==(const Vector2Temple<T>& vec) const
{
	return (x == vec.x && y == vec.y);
}

template<class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple<T>& vec) const
{
	return !(x == vec.x && y == vec.y);
}

template<class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple<T>& vec) const
{
	return (x <= vec.x && y <= vec.y);
}

template<class T>
bool Vector2Temple<T>::operator<(const Vector2Temple<T>& vec) const
{
	return (x < vec.x&& y < vec.y);
}

template<class T>
bool Vector2Temple<T>::operator>=(const Vector2Temple<T>& vec) const
{
	return (x >= vec.x && y >= vec.y);
}

template<class T>
bool Vector2Temple<T>::operator>(const Vector2Temple<T>& vec) const
{
	return  (x > vec.x && y > vec.y);
}


