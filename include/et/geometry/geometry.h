/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#pragma once

#include <et/core/et.h>
#include <et/geometry/ray.h>
#include <et/geometry/triangle.h>
#include <et/geometry/segment2d.h>
#include <et/geometry/segment3d.h>
#include <et/geometry/plane.h>
#include <et/geometry/parallelepiped.h>
#include <et/geometry/equations.h>

namespace et
{
	typedef Parallelepiped<float> parallelepiped;
	
	typedef Line2d<float> line2d;
	
	typedef Ray2d<float> ray2d;
	typedef Ray3d<float> ray3d;
	
	typedef Segment2d<float> segment2d;
	typedef Segment3d<float> segment3d;
	
	typedef Triangle<float> triangle;
	typedef Plane<float> plane;
	
	template<typename T>
	inline T sqr(T value) 
		{ return value*value; }

	template<typename T>
	inline vector2<T> absv(const vector2<T>& value) 
		{ return vector2<T>(std::abs(value.x), std::abs(value.y)); }

	template<typename T>
	inline vector3<T> absv(const vector3<T>& value) 
		{ return vector3<T>(std::abs(value.x), std::abs(value.y), std::abs(value.z)); }

	template<typename T>
	inline vector4<T> absv(const vector4<T>& value)
		{ return vector4<T>(std::abs(value.x), std::abs(value.y), std::abs(value.z), std::abs(value.w)); }

	inline vector2<int> absv(const vector2<int>& value) 
		{ return vector2<int>(std::abs(value.x), std::abs(value.y)); }
	
	inline vector3<int> absv(const vector3<int>& value) 
		{ return vector3<int>(std::abs(value.x), std::abs(value.y), std::abs(value.z)); }
	
	inline vec4i absv(const vec4i& value)
		{ return vec4i(std::abs(value.x), std::abs(value.y), std::abs(value.z), std::abs(value.w)); }

	template<typename T>
	inline vector2<T> maxv(const vector2<T>& v1, const vector2<T>& v2) 
		{ return vector2<T>(etMax(v1.x, v2.x), etMax(v1.y, v2.y)); }

	template<typename T>
	inline vector3<T> maxv(const vector3<T>& v1, const vector3<T>& v2) 
		{ return vector3<T>(etMax(v1.x, v2.x), etMax(v1.y, v2.y), etMax(v1.z, v2.z)); }

	template<typename T>
	inline vector4<T> maxv(const vector4<T>& v1, const vector4<T>& v2)
		{ return vector4<T>(etMax(v1.x, v2.x), etMax(v1.y, v2.y), etMax(v1.z, v2.z), etMax(v1.w, v2.w)); }

	template<typename T>
	inline vector2<T> minv(const vector2<T>& v1, const vector2<T>& v2) 
		{ return vector2<T>(etMin(v1.x, v2.x), etMin(v1.y, v2.y)); }

	template<typename T>
	inline vector3<T> minv(const vector3<T>& v1, const vector3<T>& v2) 
		{ return vector3<T>(etMin(v1.x, v2.x), etMin(v1.y, v2.y), etMin(v1.z, v2.z)); }

	template<typename T>
	inline vector4<T> minv(const vector4<T>& v1, const vector4<T>& v2)
		{ return vector4<T>(etMin(v1.x, v2.x), etMin(v1.y, v2.y), etMin(v1.z, v2.z), etMin(v1.w, v2.w)); }

	template <typename T>
	inline vector2<T> floorv(const vector2<T>& v)
		{ return vector2<T>(std::floor(v.x), std::floor(v.y)); }

	template <typename T>
	inline vector3<T> floorv(const vector3<T>& v)
		{ return vector3<T>(std::floor(v.x), std::floor(v.y), std::floor(v.z)); }

	template <typename T>
	inline vector4<T> floorv(const vector4<T>& v)
		{ return vector4<T>(std::floor(v.x), ::floor(v.y), std::floor(v.z), std::floor(v.w)); }

	template <typename T>
	inline vector4<T> sqrtv(const vector4<T>& v)
		{ return vector4<T>(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z), std::sqrt(v.w)); }
	
	template <typename T>
	inline vector3<T> sqrtv(const vector3<T>& v)
		{ return vector3<T>(std::sqrt(v.x), std::sqrt(v.y), std::sqrt(v.z)); }
	
	template <typename T>
	inline vector2<T> sqrtv(const vector2<T>& v)
		{ return vector2<T>(std::sqrt(v.x), std::sqrt(v.y)); }
	
	template <typename T>
	inline T length(const vector2<T>& v)
		{ return v.length(); }

	template <typename T>
	inline T length(const vector3<T>& v)
		{ return v.length(); }
	
	template <typename T>
	inline T length(const vector4<T>& v)
		{ return v.length(); }

	inline float length(float v)
		{ return std::abs(v); }

	template<typename T>
	inline vector4<T> mix(const vector4<T>& v1, const vector4<T>& v2, const T& t)
	{
		T nt = T(1) - t;
		return vector4<T>(v1.x * nt + v2.x * t, v1.y * nt + v2.y * t,
			v1.z * nt + v2.z * t, v1.w * nt + v2.w * t);
	}

	template<typename T>
	inline vector3<T> mix(const vector3<T>& v1, const vector3<T>& v2, const T& t)
	{ 
		T nt = T(1) - t;
		return vector3<T>(v1.x * nt + v2.x * t, v1.y * nt + v2.y * t, v1.z * nt + v2.z * t);
	}

	template<typename T>
	inline vector2<T> mix(const vector2<T>& v1, const vector2<T>& v2, const T& t)
	{
		T nt = T(1) - t;
		return vector2<T>(v1.x * nt + v2.x * t, v1.y * nt + v2.y * t);
	}
	
	inline float mix(float v1, float v2, float t)
		{ return v1 * (1.0f - t) + v2 * t; }
	
	template<typename T>
	inline Quaternion<T> slerp(const Quaternion<T>& from, const Quaternion<T>& to, T t)
	{
		T cosom = dot(from.vector, to.vector) + from.scalar * to.scalar;
		
		Quaternion<T> temp = to;
		if (cosom < 0.0f)
		{
			temp = -to;
			cosom = -cosom;
		}
		
		T scale0 = static_cast<T>(1) - t;
		T scale1 = t;
		
		if ((static_cast<T>(1) - cosom) > static_cast<T>(1.0e-5))
		{
			T omega = std::acos(cosom);
			T sinom = static_cast<T>(1) / std::sin(omega);
			scale0 = std::sin((static_cast<T>(1) - t) * omega) * sinom;
			scale1 = std::sin(t * omega) * sinom;
		}
		
		Quaternion<T> result;
		result.scalar = scale0 * from.scalar + scale1 * temp.scalar;
		result.vector = scale0 * from.vector + scale1 * temp.vector;
		return result;
	}

	template<typename T>
	inline vector3<T>fromSpherical(T theta, T phi)
	{
		T fCosTheta = std::cos(theta);
		return vec3(fCosTheta * std::cos(phi), std::sin(theta), fCosTheta * std::sin(phi));
	}
	
	template<typename T>
	inline vector3<T>fromSphericalRotated(T theta, T phi)
	{
		T fSinTheta = std::sin(theta);
		return vec3(fSinTheta * std::cos(phi), std::cos(theta), fSinTheta * std::sin(phi));
	}

	template <typename T>
	inline vector3<T> toSpherical(const vector3<T>& vec)
	{
		vector3<T> normalized_v = normalize(vec);
		return vector3<T>(std::atan2(normalized_v.z, normalized_v.x), std::asin(normalized_v.y), vec.length());
	}

	template <typename T>
	inline vector2<T> normalize(const vector2<T>& v) 
	{ 
		T l = v.dotSelf();
		return (l > 0) ? v / std::sqrt(l) : vector2<T>(0);
	}

	template <typename T>
	inline vector3<T> normalize(const vector3<T>& v) 
	{ 
		T l = v.dotSelf();
		return (l > 0) ? v / std::sqrt(l) : vector3<T>(0);
	}

	template <typename T>
	inline vector4<T> normalize(const vector4<T>& v)
	{ 
		T l = v.dotSelf();
		return (l > 0) ? v / std::sqrt(l) : vector4<T>(0);
	}

	template <typename T>
	inline Quaternion<T> normalize(const Quaternion<T>& q)
	{ 
		T l = q.length();
		return (l > 0) ? q / std::sqrt(l) : Quaternion<T>();
	}

	template <typename T>
	inline vector4<T> normalizePlane(const vector4<T>& v)
	{ 
		T l = v.xyz().dotSelf();
		return (l > 0) ? v / std::sqrt(l) : vector4<T>(0);
	}

	template <typename T>
	inline vector3<T> cross(const vector3<T>& v1, const vector3<T>& v2) 
		{ return v1.cross(v2); }

	template <typename T>
	inline T dot(const vector2<T>& v1, const vector2<T>& v2) 
		{ return v1.x*v2.x + v1.y*v2.y; }

	template <typename T>
	inline T dot(const vector3<T>& v1, const vector3<T>& v2)
		{ return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z; }

	template <typename T>
	inline T dot(const vector4<T>& v1, const vector4<T>& v2)
		{ return v1.x*v2.x + v1.y*v2.y + v1.z*v2.z + v1.w*v2.w; }

	template <typename T>
	inline T outerProduct(const vector2<T>& v1, const vector2<T>& v2)
		{ return v1.x * v2.y - v1.y * v2.x; }
	
	template <typename T> 
	inline vector3<T> reflect(const vector3<T>& v, const vector3<T>& n)
		{ return v - static_cast<T>(2) * dot(v, n) * n; }

	template <typename T>
	Triangle<T> operator * (const matrix3<T>& m, const Triangle<T>& t)
		{ return Triangle<T>(m * t.v1, m * t.v2, m * t.v3); }

	template <typename T>
	Triangle<T> operator * (const matrix4<T>& m, const Triangle<T>& t)
		{ return Triangle<T>(m * t.v1(), m * t.v2(), m * t.v3()); }
	
	template <typename T>
	inline matrix4<T> translationMatrix(T x, T y, T z)
	{
		matrix4<T> M;
		M[0][0] = M[1][1] = M[2][2] = static_cast<T>(1);
		M[3] = vector4<T>(x, y, z, static_cast<T>(1));
		return M;
	}

	template <typename T>
	inline matrix4<T> translationScaleMatrix(T tx, T ty, T tz, T sx, T sy, T sz)
	{
		matrix4<T> M;
		M[0][0] = sx;
		M[1][1] = sy;
		M[2][2] = sz;
		M[3] = vector4<T>(tx, ty, tz, static_cast<T>(1));
		return M;
	}

	template <typename T>
	inline matrix4<T> scaleMatrix(T x, T y, T z)
	{
		matrix4<T> M;
		M[0][0] = x;
		M[1][1] = y;
		M[2][2] = z;
		M[3][3] = static_cast<T>(1);
		return M;
	}

	template <typename T>
	inline matrix4<T> rotationYXZMatrix(T x, T y, T z)
	{
		matrix4<T> m(static_cast<T>(1));

		float sx = std::sin(x);
		float cx = std::cos(x);
		float sy = std::sin(y);
		float cy = std::cos(y);
		float sz = std::sin(z);
		float cz = std::cos(z);

		m[0][0] =  cz*cy - sz*sx*sy; m[0][1] = -cx*sz; m[0][2] = cz*sy + sz*sx*cy;
		m[1][0] =  sz*cy + cz*sx*sy; m[1][1] =  cx*cz; m[1][2] = sz*sy - cz*sx*cy;
		m[2][0] = -cx*sy;            m[2][1] =  sx;    m[2][2] = cx*cy;           

		return m;
	}

	template <typename T>
	inline matrix4<T> translationRotationYXZMatrix(T tx, T ty, T tz, T rx, T ry, T rz)
	{
		matrix4<T> m;

		float sx = std::sin(rx);
		float cx = std::cos(rx);
		float sy = std::sin(ry);
		float cy = std::cos(ry);
		float sz = std::sin(rz);
		float cz = std::cos(rz);

		m[0][0] =  cz*cy - sz*sx*sy; m[0][1] = -cx*sz; m[0][2] = cz*sy + sz*sx*cy;
		m[1][0] =  sz*cy + cz*sx*sy; m[1][1] =  cx*cz; m[1][2] = sz*sy - cz*sx*cy;
		m[2][0] = -cx*sy;            m[2][1] =  sx;    m[2][2] = cx*cy;           
		m[3][0] =  tx;				 m[3][1] =  ty;    m[3][2] = tz;
		m[3][3] = 1;

		return m;
	}

	template <typename T>
	inline matrix4<T> rotationScaleMatrix(T rx, T ry, T rz, T scx, T scy, T scz)
	{
		matrix4<T> m;

		float sx = std::sin(rx);
		float cx = std::cos(rx);
		float sy = std::sin(ry);
		float cy = std::cos(ry);
		float sz = std::sin(rz);
		float cz = std::cos(rz);

		m[0][0] = scx * (cz*cy - sz*sx*sy); 
		m[0][1] = scy * (-cx*sz); 
		m[0][2] = scz * (cz*sy + sz*sx*cy);

		m[1][0] = scx * (sz*cy + cz*sx*sy);
		m[1][1] = scy * (cx*cz); 
		m[1][2] = scz * (sz*sy - cz*sx*cy);

		m[2][0] = scx * (-cx*sy);
		m[2][1] = scy * (sx);
		m[2][2] = scz * (cx*cy);
		m[3][3] = 1;

		return m;
	}

	template <typename T>
	inline matrix4<T> transformYXZMatrix(T tx, T ty, T tz, T rx, T ry, T rz)
	{
		matrix4<T> m;

		float sx = std::sin(rx);
		float cx = std::cos(rx);
		float sy = std::sin(ry);
		float cy = std::cos(ry);
		float sz = std::sin(rz);
		float cz = std::cos(rz);

		m[0][0] =  cz*cy - sz*sx*sy; m[0][1] = -cx*sz; m[0][2] = cz*sy + sz*sx*cy;
		m[1][0] =  sz*cy + cz*sx*sy; m[1][1] =  cx*cz; m[1][2] = sz*sy - cz*sx*cy;
		m[2][0] = -cx*sy;            m[2][1] =  sx;    m[2][2] = cx*cy;
		m[3][0] =  tx;               m[3][1] =  ty;    m[3][2] = tz; 

		m[3][3] = 1;

		return m;
	}
	
	template <typename T>
	inline matrix4<T> orientationForNormal(const vector3<T>& n)
	{
		vector3<T> up = normalize(n);
		T theta = asin(up.y) - static_cast<T>(HALF_PI);
		T phi = atan2(up.z, up.x) + static_cast<T>(HALF_PI);
		T csTheta = cos(theta);
		vector3<T> side2(csTheta * cos(phi), sin(theta), csTheta * sin(phi));
		vector3<T> side1 = up.cross(side2);
		
		matrix4<T> result;
		result[0].xyz() = vector3<T>(side1.x, up.x, side2.x);
		result[1].xyz() = vector3<T>(side1.y, up.y, side2.y);
		result[2].xyz() = vector3<T>(side1.z, up.z, side2.z);
		return result;
	}	

	template <typename T>
	inline vector2<T> multiplyWithoutTranslation(const vector2<T>& v, const matrix4<T>& m)
		{ return vector2<T>(m[0][0] * v.x + m[1][0] * v.y, m[0][1] * v.x + m[1][1] * v.y); }

	template <typename T>
	inline vector2<T> operator * (const matrix4<T>& m, const vector2<T>& v)
	{
		return vector2<T>(m[0][0] * v.x + m[1][0] * v.y + m[3][0],
			m[0][1] * v.x + m[1][1] * v.y + m[3][1]);
	}

	inline mat4 translationMatrix(const vec3& v)
		{ return translationMatrix<float>(v.x, v.y, v.z); }

	inline mat4 translationScaleMatrix(const vec3& t, const vec3& s)
		{ return translationScaleMatrix<float>(t.x, t.y, t.z, s.x, s.y, s.z); }

	inline mat4 scaleMatrix(const vec3& v) 
		{ return scaleMatrix<float>(v.x, v.y, v.z); }

	inline mat4 rotationYXZMatrix(const vec3& v) 
		{ return rotationYXZMatrix<float>(v.x, v.y, v.z); }

	inline mat4 rotationScaleMatrix(const vec3& r, const vec3& s) 
		{ return rotationScaleMatrix<float>(r.x, r.y, r.z, s.x, s.y, s.z); }

	inline mat4 translationRotationYXZMatrix(const vec3& t, const vec3& r) 
		{ return translationRotationYXZMatrix<float>(t.x, t.y, t.z, r.x, r.y, r.z); }

	inline mat4 transformYXZMatrix(vec3 translate, vec3 rotate) 
		{ return transformYXZMatrix<float>(translate.x, translate.y, translate.z, rotate.x, rotate.y, rotate.z); }

	inline void normalizeAngle(float& angle)
	{
		while (angle < -PI) angle += DOUBLE_PI;
		while (angle > PI) angle -= DOUBLE_PI;
	}
	
	template <typename T>
	inline T intPower(T value, size_t power)
	{
		T result = static_cast<T>(1);
		for (size_t i = 1; i <= power; ++i)
			result *= value;
		return result;
	}
	
	template <typename T>
	inline vec2 vector2ToFloat(const vector2<T>& v)
		{ return vec2(static_cast<float>(v.x), static_cast<float>(v.y)); }

	template <typename T>
	inline vec3 vector3ToFloat(const vector3<T>& v)
		{ return vec3(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z)); }

	template <typename T>
	inline vec4 vector4ToFloat(const vector4<T>& v)
		{ return vec4(static_cast<float>(v.x), static_cast<float>(v.y), static_cast<float>(v.z), static_cast<float>(v.w)); }
	
	template <typename T>
	T bezierCurve(T* points, size_t size, float time)
	{
		ET_ASSERT((size > 0) && (points != nullptr))

		if (size == 1)
			return *points;
		
		if (size == 2)
			return mix(*points, points[1], time);

		if (size == 3)
		{
			float invTime = 1.0f - time;
			return sqr(invTime) * points[0] + 2.0f * invTime * time * points[1] + sqr(time) * points[2];
		}
		
		return mix(bezierCurve<T>(points, size-1, time), bezierCurve<T>(points+1, size-1, time), time);
	}
	
	quaternion matrixToQuaternion(const mat3& m);
	quaternion matrixToQuaternion(const mat4& m);

	vec3 removeMatrixScale(mat3& m);
	void decomposeMatrix(const mat4& mat, vec3& translation, quaternion& rotation, vec3& scale);
	
	vec3 randVector(float sx = 1.0f, float sy = 1.0f, float sz = 1.0f);
	
	uint32_t randomInteger(uint32_t limit = RAND_MAX);
	
	float randomFloat(float low, float up);
	float randomFloat();
	
	float signOrZero(float s);
	float signNoZero(float s);

	mat4 rotation2DMatrix(float angle);
	mat4 transform2DMatrix(float a, const vec2& scale, const vec2& translate);
	mat3 rotation2DMatrix3(float angle);
	
	vec3 circleFromPoints(const vec2& p1, const vec2& p2, const vec2& p3);
	vec3 perpendicularVector(const vec3&);
	vec3 randomVectorOnHemisphere(const vec3& normal, float distributionAngle);
	
	quaternion quaternionFromAngels(float x, float y, float z);
}
