#ifndef __POINT3_H__
#define __POINT3_H__

template<class TYPE>
class Point3
{
public:
	enum Side
	{
		CONTAINED = 0,
		LEFT = 1,
		RIGHT = 2,
		UP = 4,
		DOWN = 8,
		SAME_Z = 12
	};

	TYPE x, y, z;

	Point3() : Point3(0, 0, 0)
	{}

	Point3(TYPE x, TYPE y, TYPE z) : x(x), y(y), z(z)
	{}

	// Operators ------------------------------------------------
	Point3 operator -(const Point3 &v) const
	{
		Point3 r;

		r.x = x - v.x;
		r.y = y - v.y;
		r.z = z - v.z;

		return(r);
	}

	Point3 operator + (const Point3 &v) const
	{
		Point3 r;

		r.x = x + v.x;
		r.y = y + v.y;
		r.z = z + v.z;

		return(r);
	}

	const Point3& operator -=(const Point3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return(*this);
	}

	const Point3& operator +=(const Point3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return(*this);
	}

	bool operator ==(const Point3& v) const
	{
		return (x == v.x && y == v.y && z == v.z);
	}

	bool operator !=(const Point3& v) const
	{
		return (x != v.x || y != v.y || z != v.z);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0 && z == 0);
	}

	Point3& SetToZero()
	{
		x = y = z = 0;
		return(*this);
	}

	Point3& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const Point3& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;
		TYPE fz = z - v.z;

		return sqrt((fx*fx) + (fy*fy) + (fz*fz));
	}

	Side SidePlaced(const Point3<TYPE>& other) const
	{
		int side = CONTAINED;

		if (x > other.x)
			side |= LEFT;
		if (other.x > x)
			side |= RIGHT;
		if (z >= other.z)
			side |= DOWN;
		if (other.z >= z)
			side |= UP;

		return Side(side);
	}

};

typedef Point3<int> iPoint3;
typedef Point3<float> fPoint3;

#endif //__POINT3_H__
