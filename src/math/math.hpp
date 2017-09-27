// #pragma once
// .
// /*

// I've decided that having a vector as an array isn't a good idea. This is because quaternion doesn't work well as a 4-array, because the first element is the real number w, and so it's hard to operate on the 1, 2, and 3 elements as a vector. And with matrices, a 16-array doesn't allow nice row/col access and a 4-4-array inverts the row and col access.

// But I do like the idea of a static math class that accesses these. So I think I will have vector, quaternion, and matrix classes with just constructors, [] operators.

// */

// #include <cmath>
// #include <array>

// namespace vew
// {
// 	class Math final
// 	{
// 	public:
// 		typedef std::array<int, 2> Vector2i;
// 		typedef std::array<int, 3> Vector3i;
// 		typedef std::array<int, 4> Vector4i;
// 		typedef std::array<float, 2> Vector2f;
// 		typedef std::array<float, 3> Vector3f;
// 		typedef std::array<float, 4> Vector4f;
// 		typedef std::array<double, 2> Vector2d;
// 		typedef std::array<double, 3> Vector3d;
// 		typedef std::array<double, 4> Vector4d;
// 		typedef std::array<float, 4> Quaternionf;
// 		typedef std::array<double, 4> Quaterniond;

// 		// Returns an array with all zeroes.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> zero();

// 		// Returns an array as a unit axis.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> axis(int axis);

// 		// Returns the norm/magnitude/length of value. If you want the square, just use dot(value, value).
// 		template <typename T, int DIM>
// 		static T length(std::array<T, DIM> value);

// 		// Returns value as unit length. If value has length zero, it remains zero.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> unit(std::array<T, DIM> value);

// 		// Returns value as an identity. If value has length zero, it remains zero.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> unit(std::array<T, DIM> value);

// 		// Returns the dot product of lhs and rhs.
// 		template <typename T, int DIM>
// 		static T dot(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 		// Returns the cross product of lhs and rhs.
// 		template <typename T>
// 		static std::array<T, 3> cross(std::array<T, 3> lhs, std::array<T, 3> rhs);

// 		// Returns the two dimensional cross product of lhs and rhs. It equals |lhs| |rhs| sin(the angle between them).
// 		template <typename T>
// 		static T cross(std::array<T, 2> lhs, std::array<T, 2> rhs);

// 		// Returns value rotated by 90 degrees counter-clockwise.
// 		template <typename T>
// 		static std::array<T, 2> perp(std::array<T, 2> value);

// 		// Returns value rotated counter-clockwise by the angle in radians.
// 		template <typename T>
// 		static std::array<T, 2> rotate(std::array<T, 2> value, T angle);

// 		// Returns an array with each element in lhs multiplied by the corresponding element in rhs.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> scale(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 		// Returns an array with each element in lhs divided by the corresponding element in rhs.
// 		template <typename T, int DIM>
// 		static std::array<T, DIM> scaleInv(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 		template <typename T, int DIM>
// 		std::array<T, DIM> clamp(std::array<T, DIM> value, T min, T max);

// 		template <typename T, int DIM>
// 		std::array<T, DIM> clamp(std::array<T, DIM> value, std::array<T, DIM> min, std::array<T, DIM> max);
// 	};

// 	// Returns lhs == rhs.
// 	template <typename T, int DIM>
// 	bool operator==(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 	// Returns lhs != rhs.
// 	template <typename T, int DIM>
// 	bool operator!=(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 	// Returns true if the the first element in v0 that is not equal to the corresponding element in v1 is less than the other element. If they are all equal, it returns false.
// 	template <typename T, int DIM>
// 	bool operator<std::array<T, DIM> lhs, std::array<T, DIM> rhs)

// 	// Returns -value.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator-(std::array<T, DIM> value)

// 	// Returns +value.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator+(std::array<T, DIM> value)

// 	// Returns lhs + rhs.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator+(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 	// Returns lhs - rhs.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator-(std::array<T, DIM> lhs, std::array<T, DIM> rhs);

// 	// Returns lhs * rhs.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator*(std::array<T, DIM> lhs, T rhs);

// 	// Returns lhs * rhs.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator*(T lhs, std::array<T, DIM> rhs);

// 	// Returns lhs / rhs.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator/(std::array<T, DIM> lhs, T rhs);

// 	// Inline Implementations

// 	// Returns an array with all zeroes.
// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::zero()
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = 0;
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::axis(int axis)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = 0;
// 		}
// 		r[axis] = 1;
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	T Math::length(std::array<T, DIM> value)
// 	{
// 		return std::sqrt(dot(value, value));
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::unit(std::array<T, DIM> value)
// 	{
// 		T lengthSq = dot(value, value);
// 		if (lengthSq > 0)
// 		{
// 			return value / std::sqrt(lengthSq);
// 		}
// 		return value;
// 	}

// 	template <typename T, int DIM>
// 	T Math::dot(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		T r = 0;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r += lhs[i] * rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T>
// 	std::array<T, 3> Math::cross(std::array<T, 3> lhs, std::array<T, 3> rhs)
// 	{
// 		return {lhs[1] * rhs[2] - lhs[2] * rhs[1],
// 				lhs[2] * rhs[0] - lhs[0] * rhs[2],
// 				lhs[0] * rhs[1] - lhs[1] * rhs[0]};
// 	}

// 	template <typename T>
// 	T Math::cross(std::array<T, 2> lhs, std::array<T, 2> rhs)
// 	{
// 		return lhs[0] * rhs[1] - lhs[1] * rhs[0];
// 	}

// 	template <typename T>
// 	std::array<T, 2> Math::perp(std::array<T, 2> value)
// 	{
// 		return {-value[1], value[0]};
// 	}

// 	template <typename T>
// 	std::array<T, 2> Math::rotate(std::array<T, 2> value, T angle)
// 	{
// 		T c = std::cos(angle);
// 		T s = std::sin(angle);
// 		return {value[0] * c - value[1] * s,
// 				value[0] * s + value[1] * c};
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::scale(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] * rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::scaleInv(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] / rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::clamp(std::array<T, DIM> value, T min, T max)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = (min <= value[i] ? (value[i] <= max ? value[i] : max) : min);
// 		}
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> Math::clamp(std::array<T, DIM> value, std::array<T, DIM> min, std::array<T, DIM> max)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = (min[i] <= value[i] ? (value[i] <= max[i] ? value[i] : max[i]) : min[i]);
// 		}
// 	}

// 	template <typename T, int DIM>
// 	bool operator==(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			if (lhs[i] != rhs[i])
// 			{
// 				return false;
// 			}
// 		}
// 		return true;
// 	}

// 	template <typename T, int DIM>
// 	bool operator!=(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			if (lhs[i] != rhs[i])
// 			{
// 				return true;
// 			}
// 		}
// 		return false;
// 	}

// 	template <typename T, int DIM>
// 	bool operator<std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			if (lhs[i] != rhs[i])
// 			{
// 				return (lhs[i] < rhs[i]);
// 			}
// 		}
// 		return false;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator-(std::array<T, DIM> value)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = -value[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator+(std::array<T, DIM> value)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = +value[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator+(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] + rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator-(std::array<T, DIM> lhs, std::array<T, DIM> rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] - rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator*(std::array<T, DIM> lhs, T rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] * rhs;
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator*(T lhs, std::array<T, DIM> rhs)
// 	{
// 		std::array<T, DIM> r;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs * rhs[i];
// 		}
// 		return r;
// 	}

// 	template <typename T, int DIM>
// 	std::array<T, DIM> operator/(std::array<T, DIM> lhs, T rhs)
// 	{
// 		std::array<T, DIM> r;
// 		T rhsInv = (T)1 / rhs;
// 		for (int i = 0; i < DIM; i++)
// 		{
// 			r[i] = lhs[i] * rhsInv;
// 		}
// 		return r;
// 	}
// }