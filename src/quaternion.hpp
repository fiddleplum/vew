#pragma once

#include "matrix.hpp"

namespace vew
{
	// This is a standard mathematical quaternion class. T is the type of its elements.
	template <typename T>
	class Quaternion
	{
	public:
		// Constructs it as the identity.
		Quaternion();

		// Constructs it with specific numbers.
		Quaternion(T w, T x, T y, T z);

		// Constructs it with a real and imaginary part.
		Quaternion(T w, Vector<3, T> xyz);

		// Constructs it with an angle and axis. If axisIsNormalized is true, the axis will not be normalized.
		Quaternion(T angle, Vector<3, T> const & axis, bool axisIsNormalized);

		// Constructs it as a rotation from start to end. If vectorsAreNormalized is true, start and end will not be normalized.
		Quaternion(Vector<3, T> const & start, Vector<3, T> const & end, bool vectorsAreNormalized);

		// Constructs it as a trio of euler angles.
		Quaternion(T yaw, T pitch, T roll);

		// Returns an identity quaterion;
		static Quaternion<T> identity();

		// Access element at index i.
		T & operator[](int i);

		// Access element at index i.
		T operator[](int i) const;

		// Returns the conjugate.
		Quaternion<T> conjugate() const;

		// Returns the reciprocal.
		Quaternion<T> reciprocal() const;

		// Returns the norm.
		T norm() const;

		// Returns the square of the norm.
		T normSq() const;

		// Normalizes it.
		void normalize();

		// Returns the vector of the quaternion as a rotation operation applied to vector v. Assumes this is normalized.
		Vector<3, T> rotate(Vector<3, T> const & v) const;

		// Returns the 0, 1, or 2 axis of the frame represented by this. Assumes this is normalized.
		Vector<3, T> getAxis(int i) const;

		// Returns the rotation matrix represented by this, for pre-multiplying. Assumes this is normalized.
		Matrix<3, 3, T> getMatrix() const;

	private:
		// The real part.
		T w;

		// The imaginary part.
		Vector<3, T> xyz;
	};

	typedef Quaternion<float> Quaternionf;
	typedef Quaternion<double> Quaterniond;

	// Returns the addition of two quaternions.
	template <typename T>
	Quaternion<T> operator+(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs);

	// Returns the subtraction of two quaternions.
	template <typename T>
	Quaternion<T> operator-(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs);

	// Returns the multplication of two quaternions.
	template <typename T>
	Quaternion<T> operator*(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs);

	// Returns the multiplication of a quaternion and a scalar.
	template <typename T>
	Quaternion<T> operator*(Quaternion<T> const & q, T t);

	// Returns the multiplication of a scalar and a quaternion.
	template <typename T>
	Quaternion<T> operator*(T t, Quaternion<T> const & q);

	// Template implementation

	template <typename T>
	Quaternion<T>::Quaternion()
	{
		w = 1;
		xyz = {0, 0, 0};
	}

	template <typename T>
	Quaternion<T>::Quaternion(T w_, T x, T y, T z)
	{
		w = w_;
		xyz = {x, y, z};
	}

	template <typename T>
	Quaternion<T>::Quaternion(T w_, Vector<3, T> xyz_)
	{
		w = w_;
		xyz = xyz_;
	}

	template <typename T>
	Quaternion<T>::Quaternion(Vector<3, T> const & start, Vector<3, T> const & end, bool vectorsAreNormalized)
	{
		w = start.dot(end);
		Vector<3, T> axis;
		if (w != -1)
		{
			xyz = start.cross(end);
		}
		else
		{
			xyz = start.perpendicular();
		}
		if (vectorsAreNormalized)
		{
			w += 1;
		}
		else
		{
			w += start.norm() * end.norm();
		}
		normalize();
	}

	template <typename T>
	Quaternion<T>::Quaternion(T angle, Vector<3, T> const & axis, bool axisIsNormalized)
	{
		w = std::cos(angle / (T)2);
		if (axisIsNormalized)
		{
			xyz = axis;
		}
		else
		{
			xyz = axis.unit();
		}
		xyz *= std::sin(angle / (T)2);
	}

	template <typename T>
	Quaternion<T>::Quaternion(T yaw, T pitch, T roll)
	{
		// remember yaw goes positive to the right (if you're looking down +y)
		T cosYaw2 = cos(yaw / 2);
		T sinYaw2 = sin(yaw / 2);
		T cosPitch2 = cos(pitch / 2);
		T sinPitch2 = sin(pitch / 2);
		T cosRoll2 = cos(roll / 2);
		T sinRoll2 = sin(roll / 2);
		w = cosYaw2 * cosPitch2 * cosRoll2 - sinYaw2 * sinPitch2 * sinRoll2;
		xyz[1] = cosYaw2 * cosPitch2 * sinRoll2 + sinYaw2 * sinPitch2 * cosRoll2;
		xyz[0] = cosYaw2 * sinPitch2 * cosRoll2 - sinYaw2 * cosPitch2 * sinRoll2;
		xyz[2] = sinYaw2 * cosPitch2 * cosRoll2 + cosYaw2 * sinPitch2 * sinRoll2;
	}

	template <typename T>
	Quaternion<T> Quaternion<T>::identity()
	{
		return Quaternion<T>();
	}

	template <typename T>
	T & Quaternion<T>::operator[](int i)
	{
		if (i == 0)
		{
			return w;
		}
		else
		{
			return xyz[i - 1];
		}
	}

	template <typename T>
	T Quaternion<T>::operator[](int i) const
	{
		if (i == 0)
		{
			return w;
		}
		else
		{
			return xyz[i - 1];
		}
	}

	template <typename T>
	Quaternion<T> Quaternion<T>::conjugate() const
	{
		return Quaternion<T>(w, -xyz);
	}

	template <typename T>
	Quaternion<T> Quaternion<T>::reciprocal() const
	{
		T nSq = normSq();
		if (nSq == 0)
		{
			throw std::exception();
		}
		return conjugate() / nSq;
	}

	template <typename T>
	T Quaternion<T>::norm() const
	{
		return std::sqrt((w * w) + xyz.normSq());
	}

	template <typename T>
	T Quaternion<T>::normSq() const
	{
		return (w * w) + xyz.normSq();
	}

	template <typename T>
	void Quaternion<T>::normalize()
	{
		T n = norm();
		if (n == 0)
		{
			throw std::exception();
		}
		w /= n;
		xyz /= n;
	}

	template <typename T>
	Vector<3, T> Quaternion<T>::rotate(Vector<3, T> const & v) const
	{
		Vector<3, T> t = (T)2 * xyz.cross(v);
		return v + w * t + xyz.cross(t);
	}

	template <typename T>
	Vector<3, T> Quaternion<T>::getAxis(int i) const
	{
		if (i >= 3)
		{
			throw std::exception();
		}
		Vector3f axis;
		int j = (i + 1) % 3;
		int k = (i + 2) % 3;
		axis[i] = (T)1 - (T)2 * (xyz[j] * xyz[j] + xyz[k] * xyz[k]);
		axis[j] = (T)2 * (xyz[i] * xyz[j] + xyz[k] * w);
		axis[k] = (T)2 * (xyz[i] * xyz[k] - xyz[j] * w);
		return axis;
	}

	template <typename T>
	Matrix<3, 3, T> Quaternion<T>::getMatrix() const
	{
		Matrix<3, 3, T> m;
		float xx = xyz[0] * xyz[0];
		float xy = xyz[0] * xyz[1];
		float xz = xyz[0] * xyz[2];
		float xw = xyz[0] * w;
		float yy = xyz[1] * xyz[1];
		float yz = xyz[1] * xyz[2];
		float yw = xyz[1] * w;
		float zz = xyz[2] * xyz[2];
		float zw = xyz[2] * w;
		m(0, 0) = (T)1 - (T)2 * (yy + zz);
		m(0, 1) = (T)2 * (xy - zw);
		m(0, 2) = (T)2 * (xz + yw);
		m(1, 0) = (T)2 * (xy + zw);
		m(1, 1) = (T)1 - (T)2 * (xx + zz);
		m(1, 2) = (T)2 * (yz - xw);
		m(2, 0) = (T)2 * (xz - yw);
		m(2, 1) = (T)2 * (yz + xw);
		m(2, 2) = (T)1 - (T)2 * (xx + yy);
		return m;
	}

	template <typename T>
	Quaternion<T> operator+(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs)
	{
		return Quaternion<T>(q_lhs.w + q_rhs.r, q_lhs.xyz + q_rhs.xyz);
	}

	template <typename T>
	Quaternion<T> operator-(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs)
	{
		return Quaternion<T>(q_lhs.w - q_rhs.r, q_lhs.xyz - q_rhs.xyz);
	}

	template <typename T>
	Quaternion<T> operator*(Quaternion<T> const & q_lhs, Quaternion<T> const & q_rhs)
	{
		return Quaternion<T>(q_lhs.w * q_rhs.w - q_lhs.xyz.dot(q_rhs.xyz), q_lhs.w * q_rhs.xyz + q_rhs.w * q_lhs.xyz + q_lhs.xyz.cross(q_rhs.xyz));
	}

	template <typename T>
	Quaternion<T> operator*(Quaternion<T> const & q, T t)
	{
		return Quaternion<T>(q.w * t, q.xyz * t);
	}

	template <typename T>
	Quaternion<T> operator*(T t, Quaternion<T> const & q)
	{
		return Quaternion<T>(t * q.w, t * q.xyz);
	}
}