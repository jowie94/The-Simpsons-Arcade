#ifndef __RECTANGLE3_H__
#define __RECTANGLE3_H__

#include "Point3.h"
#include "Engine.h"

template<typename T>
class Rectangle3
{
public:
	enum Side
	{
		CONTAINED = 0,
		LEFT = 1,
		RIGHT = 2,
		UP = 4,
		DOWN = 8,
	};

	Point3<T> Position;
	T w, h;

	Rectangle3(T x, T y, T z, T w, T h) : Position(Point3<T>(x, y, z)), w(w), h(h)
	{	
	}

	~Rectangle3()
	{
	}

	bool Overlaps(const Rectangle3<T>& other) const
	{
		return (Position.z - other.Position.z < 10) 
				&& !(Position.x > other.Position.x + other.w 
					 || other.Position.x > Position.x + w
					 || Position.y > other.Position.y + other.h
					 || other.Position.y > Position.y + h);
	}

	Side PlacedSide(const Rectangle3<T>& other) const
	{
		int side = CONTAINED;

		if (Position.x >= other.Position.x + other.w)
			side |= LEFT;
		if (other.Position.x >= Position.x + w)
			side |= RIGHT;
		if (Position.y >= other.Position.y + other.h)
			side |= DOWN;
		if (other.Position.y < Position.y + h)
			side |= UP;

		return Side(side);
	}
};

typedef Rectangle3<int> iRectangle3;

#endif // __RECTANGLE3_H__
