/*
 * This file is part of `et engine`
 * Copyright 2009-2015 by Sergey Reznik
 * Please, modify content only if you know what are you doing.
 *
 */

#pragma once

#include <et/geometry/matrix3.h>

namespace et
{
	template<typename T>
	struct matrix4
	{
	public:
		enum : size_t
		{
			Rows = 4,
			ComponentSize = sizeof(T),
			RowSize = Rows * vector4<T>::ComponentSize
		};
		
		typedef vector4<T> RowType;
		
	public:
		RowType mat[Rows];

	public:
		matrix4()
			{ }
		
		explicit matrix4(T s)
		{
			mat[0] = RowType(s, 0, 0, 0);
			mat[1] = RowType(0, s, 0, 0);
			mat[2] = RowType(0, 0, s, 0);
			mat[3] = RowType(0, 0, 0, s);
		}

		matrix4(const RowType& c0, const RowType& c1, const RowType& c2, const RowType& c3)
		{
			mat[0] = c0;
			mat[1] = c1;
			mat[2] = c2;
			mat[3] = c3;
		}

		matrix4(const matrix3<T>& transform, const vector3<T>& translation, bool explicitTranslation)
		{
			mat[0] = RowType(transform[0], 0);
			mat[1] = RowType(transform[1], 0);
			mat[2] = RowType(transform[2], 0);
			mat[3] = RowType(explicitTranslation ? translation : transform * translation, T(1));
		}

		explicit matrix4(const matrix3<T>& m)
		{
			mat[0] = RowType(m[0], 0.0f);
			mat[1] = RowType(m[1], 0.0f);
			mat[2] = RowType(m[2], 0.0f);
			mat[3] = RowType(0.0f, 0.0f, 0.0f, 1.0f);
		}

		matrix4& operator = (const matrix4& c)
		{
			mat[0] = c[0];
			mat[1] = c[1];
			mat[2] = c[2];
			mat[3] = c[3];
			return *this;
		}
		
		T* data()
			{ return mat[0].data(); }  

		const T* data() const
			{ return mat[0].data(); }  

		char* binary()
			{ return mat[0].binary(); }  

		const char* binary() const
			{ return mat[0].binary(); }  

		T& operator () (int i)
			{ return *(mat[0].data() + i); }
		
		const T& operator () (int i) const
			{ return *(mat[0].data() + i); }

		RowType& operator [] (int i)
			{ return mat[i];}

		const RowType& operator [] (int i) const
			{ return mat[i];}

		T& operator () (size_t i)
			{ return *(mat[0].data() + i); }
		
		const T& operator () (size_t i) const
			{ return *(mat[0].data() + i); }
		
		RowType& operator [] (size_t i)
			{ return mat[i];}
		
		const RowType& operator [] (size_t i) const
			{ return mat[i];}
		
		RowType column(int c) const
			{ return RowType( mat[0][c], mat[1][c], mat[2][c], mat[3][c]); }

		matrix4 operator * (T s) const
			{ return matrix4(mat[0] * s, mat[1] * s, mat[2] * s, mat[3] * s); }

		matrix4 operator / (T s) const
			{ return matrix4(mat[0] / s, mat[1] / s, mat[2] / s, mat[3] / s); }

		matrix4 operator + (const matrix4& m) const
			{ return matrix4(mat[0] + m.mat[0], mat[1] + m.mat[1], mat[2] + m.mat[2], mat[3] + m.mat[3]); }

		matrix4 operator - (const matrix4& m) const
			{ return matrix4(mat[0] - m.mat[0], mat[1] - m.mat[1], mat[2] - m.mat[2], mat[3] - m.mat[3]); }

		matrix4& operator /= (T m)
		{
			mat[0] /= m;
			mat[1] /= m;
			mat[2] /= m;
			mat[3] /= m; 
			return *this;
		}

		vector3<T> operator * (const vector3<T>& v) const
		{
			vector3<T> r;
			r.x = mat[0].x * v.x + mat[1].x * v.y + mat[2].x * v.z + mat[3].x;
			r.y = mat[0].y * v.x + mat[1].y * v.y + mat[2].y * v.z + mat[3].y;
			r.z = mat[0].z * v.x + mat[1].z * v.y + mat[2].z * v.z + mat[3].z;
			T w = mat[0].w * v.x + mat[1].w * v.y + mat[2].w * v.z + mat[3].w;
			return (w*w > 0) ? r / w : r;
		}

		RowType operator * (const RowType& v) const
		{
			return RowType(
				mat[0].x * v.x + mat[1].x * v.y + mat[2].x * v.z + mat[3].x * v.w,
				mat[0].y * v.x + mat[1].y * v.y + mat[2].y * v.z + mat[3].y * v.w,
				mat[0].z * v.x + mat[1].z * v.y + mat[2].z * v.z + mat[3].z * v.w,
				mat[0].w * v.x + mat[1].w * v.y + mat[2].w * v.z + mat[3].w * v.w );
		}

		matrix4& operator += (const matrix4& m)
		{
			mat[0] += m.mat[0];
			mat[1] += m.mat[1];
			mat[2] += m.mat[2];
			mat[3] += m.mat[3];
			return *this;
		}

		matrix4& operator -= (const matrix4& m)
		{
			mat[0] -= m.mat[0];
			mat[1] -= m.mat[1];
			mat[2] -= m.mat[2];
			mat[3] -= m.mat[3];
			return *this;
		}

		matrix4& operator *= (const matrix4& m)
		{
			RowType r0, r1, r2, r3;

			r0.x = mat[0].x*m.mat[0].x + mat[0].y*m.mat[1].x + mat[0].z*m.mat[2].x + mat[0].w*m.mat[3].x;
			r0.y = mat[0].x*m.mat[0].y + mat[0].y*m.mat[1].y + mat[0].z*m.mat[2].y + mat[0].w*m.mat[3].y;
			r0.z = mat[0].x*m.mat[0].z + mat[0].y*m.mat[1].z + mat[0].z*m.mat[2].z + mat[0].w*m.mat[3].z;
			r0.w = mat[0].x*m.mat[0].w + mat[0].y*m.mat[1].w + mat[0].z*m.mat[2].w + mat[0].w*m.mat[3].w;
			r1.x = mat[1].x*m.mat[0].x + mat[1].y*m.mat[1].x + mat[1].z*m.mat[2].x + mat[1].w*m.mat[3].x;
			r1.y = mat[1].x*m.mat[0].y + mat[1].y*m.mat[1].y + mat[1].z*m.mat[2].y + mat[1].w*m.mat[3].y;
			r1.z = mat[1].x*m.mat[0].z + mat[1].y*m.mat[1].z + mat[1].z*m.mat[2].z + mat[1].w*m.mat[3].z;
			r1.w = mat[1].x*m.mat[0].w + mat[1].y*m.mat[1].w + mat[1].z*m.mat[2].w + mat[1].w*m.mat[3].w;
			r2.x = mat[2].x*m.mat[0].x + mat[2].y*m.mat[1].x + mat[2].z*m.mat[2].x + mat[2].w*m.mat[3].x;
			r2.y = mat[2].x*m.mat[0].y + mat[2].y*m.mat[1].y + mat[2].z*m.mat[2].y + mat[2].w*m.mat[3].y;
			r2.z = mat[2].x*m.mat[0].z + mat[2].y*m.mat[1].z + mat[2].z*m.mat[2].z + mat[2].w*m.mat[3].z;
			r2.w = mat[2].x*m.mat[0].w + mat[2].y*m.mat[1].w + mat[2].z*m.mat[2].w + mat[2].w*m.mat[3].w;
			r3.x = mat[3].x*m.mat[0].x + mat[3].y*m.mat[1].x + mat[3].z*m.mat[2].x + mat[3].w*m.mat[3].x;
			r3.y = mat[3].x*m.mat[0].y + mat[3].y*m.mat[1].y + mat[3].z*m.mat[2].y + mat[3].w*m.mat[3].y;
			r3.z = mat[3].x*m.mat[0].z + mat[3].y*m.mat[1].z + mat[3].z*m.mat[2].z + mat[3].w*m.mat[3].z;
			r3.w = mat[3].x*m.mat[0].w + mat[3].y*m.mat[1].w + mat[3].z*m.mat[2].w + mat[3].w*m.mat[3].w;

			mat[0] = r0;
			mat[1] = r1;
			mat[2] = r2;
			mat[3] = r3;

			return *this;
		}

		matrix4 operator * (const matrix4& m) const
		{
			RowType r0, r1, r2, r3;

			r0.x = mat[0].x*m.mat[0].x + mat[0].y*m.mat[1].x + mat[0].z*m.mat[2].x + mat[0].w*m.mat[3].x;
			r0.y = mat[0].x*m.mat[0].y + mat[0].y*m.mat[1].y + mat[0].z*m.mat[2].y + mat[0].w*m.mat[3].y;
			r0.z = mat[0].x*m.mat[0].z + mat[0].y*m.mat[1].z + mat[0].z*m.mat[2].z + mat[0].w*m.mat[3].z;
			r0.w = mat[0].x*m.mat[0].w + mat[0].y*m.mat[1].w + mat[0].z*m.mat[2].w + mat[0].w*m.mat[3].w;

			r1.x = mat[1].x*m.mat[0].x + mat[1].y*m.mat[1].x + mat[1].z*m.mat[2].x + mat[1].w*m.mat[3].x;
			r1.y = mat[1].x*m.mat[0].y + mat[1].y*m.mat[1].y + mat[1].z*m.mat[2].y + mat[1].w*m.mat[3].y;
			r1.z = mat[1].x*m.mat[0].z + mat[1].y*m.mat[1].z + mat[1].z*m.mat[2].z + mat[1].w*m.mat[3].z;
			r1.w = mat[1].x*m.mat[0].w + mat[1].y*m.mat[1].w + mat[1].z*m.mat[2].w + mat[1].w*m.mat[3].w;

			r2.x = mat[2].x*m.mat[0].x + mat[2].y*m.mat[1].x + mat[2].z*m.mat[2].x + mat[2].w*m.mat[3].x;
			r2.y = mat[2].x*m.mat[0].y + mat[2].y*m.mat[1].y + mat[2].z*m.mat[2].y + mat[2].w*m.mat[3].y;
			r2.z = mat[2].x*m.mat[0].z + mat[2].y*m.mat[1].z + mat[2].z*m.mat[2].z + mat[2].w*m.mat[3].z;
			r2.w = mat[2].x*m.mat[0].w + mat[2].y*m.mat[1].w + mat[2].z*m.mat[2].w + mat[2].w*m.mat[3].w;

			r3.x = mat[3].x*m.mat[0].x + mat[3].y*m.mat[1].x + mat[3].z*m.mat[2].x + mat[3].w*m.mat[3].x;
			r3.y = mat[3].x*m.mat[0].y + mat[3].y*m.mat[1].y + mat[3].z*m.mat[2].y + mat[3].w*m.mat[3].y;
			r3.z = mat[3].x*m.mat[0].z + mat[3].y*m.mat[1].z + mat[3].z*m.mat[2].z + mat[3].w*m.mat[3].z;
			r3.w = mat[3].x*m.mat[0].w + mat[3].y*m.mat[1].w + mat[3].z*m.mat[2].w + mat[3].w*m.mat[3].w;

			return matrix4(r0, r1, r2, r3);  
		}

		bool operator == (const matrix4& m) const
		{
			return (mat[0] == m.mat[0]) && (mat[1] == m.mat[1]) &&
				(mat[2] == m.mat[2]) && (mat[3] == m.mat[3]);
		}

		bool operator != (const matrix4& m) const
		{
			return (mat[0] != m.mat[0]) || (mat[1] != m.mat[1]) ||
				(mat[2] != m.mat[2]) || (mat[3] != m.mat[3]);
		}

		T determinant() const
		{
			const T& a10 = mat[1].x; const T& a11 = mat[1].y; const T& a12 = mat[1].z; const T& a13 = mat[1].w;
			const T& a20 = mat[2].x; const T& a21 = mat[2].y; const T& a22 = mat[2].z; const T& a23 = mat[2].w; 
			const T& a30 = mat[3].x; const T& a31 = mat[3].y; const T& a32 = mat[3].z; const T& a33 = mat[3].w;

			return mat[0].x * (a11 * (a22*a33 - a23*a32) +	a12 * (a31*a23 - a21*a33) + a13 * (a21*a32 - a22*a31)) +
				   mat[0].y * (a10 * (a23*a32 - a22*a33) +	a20 * (a12*a33 - a13*a32) + a30 * (a13*a22 - a12*a23)) +
				   mat[0].z * (a10 * (a21*a33 - a31*a23) +	a11 * (a30*a23 - a20*a33) +	a13 * (a20*a31 - a21*a30)) +
				   mat[0].w * (a10 * (a22*a31 - a21*a32) +	a11 * (a20*a32 - a30*a22) +	a12 * (a21*a30 - a20*a31));
		}

		matrix3<T> mat3() const
		{
			return matrix3<T>(mat[0].xyz(), mat[1].xyz(), mat[2].xyz());
		}

		matrix3<T> subMatrix(int r, int c) const
		{
			matrix3<T> m;

			int i = 0; 
			for (int y = 0; y < 4; ++y)
			{
				if (y != r)
				{
					int j = 0;
					if (0 != c) m[i][j++] = mat[y].x;
					if (1 != c) m[i][j++] = mat[y].y;
					if (2 != c) m[i][j++] = mat[y].z;
					if (3 != c) m[i][j++] = mat[y].w;
					++i;
				} 
			}
			return m;
		}

		matrix4 adjugateMatrix() const
		{
			matrix4 m;

			m[0].x = subMatrix(0, 0).determinant();
			m[0].y = -subMatrix(1, 0).determinant();
			m[0].z = subMatrix(2, 0).determinant();
			m[0].w = -subMatrix(3, 0).determinant();

			m[1].x = -subMatrix(0, 1).determinant();
			m[1].y = subMatrix(1, 1).determinant();
			m[1].z = -subMatrix(2, 1).determinant();
			m[1].w = subMatrix(3, 1).determinant();

			m[2].x = subMatrix(0, 2).determinant();
			m[2].y = -subMatrix(1, 2).determinant();
			m[2].z = subMatrix(2, 2).determinant();
			m[2].w = -subMatrix(3, 2).determinant();

			m[3].x = -subMatrix(0, 3).determinant();
			m[3].y = subMatrix(1, 3).determinant();
			m[3].z = -subMatrix(2, 3).determinant();
			m[3].w = subMatrix(3, 3).determinant();

			return m;
		}

		vector3<T> rotationMultiply(const vector3<T>& v) const
		{
			const RowType& c0 = mat[0];
			const RowType& c1 = mat[1];
			const RowType& c2 = mat[2];
			return vector3<T>(c0.x * v.x + c1.x * v.y + c2.x * v.z, c0.y * v.x + c1.y * v.y + c2.y * v.z,
				c0.z * v.x + c1.z * v.y + c2.z * v.z);
		}

		matrix4 inverse() const
		{
			T det = determinant();
			return (det * det > 0) ? adjugateMatrix() / det : matrix4(0);
		}

		bool isModelViewMatrix()
		{
			vector3<T>c1 = vector3<T>(mat[0][0], mat[1][0], mat[2][0]);
			vector3<T>c2 = vector3<T>(mat[0][1], mat[1][1], mat[2][1]);
			vector3<T>c3 = vector3<T>(mat[0][2], mat[1][2], mat[2][2]);
			vector3<T>c4 = vector3<T>(mat[0][3], mat[1][3], mat[2][3]);
			T l1 = c1.length();
			T l2 = c2.length();
			T l3 = c3.length();
			T l4 = c4.length();
			T c1dotc2 = c1.dot(c2);
			T c1dotc3 = c1.dot(c3);
			T c2dotc3 = c2.dot(c3);
			const T one = T(1);
			return (l1 == one) && (l2 = one) && (l3 = one) && (l4 = 0) && (c1dotc2 == 0) && (c1dotc3 == 0) && (c2dotc3 == 0);
		}

		matrix4 scaleWithPreservedPosition(const vector3<T>& p)
		{
			RowType r1 = RowType(mat[0].xyz() * p, mat[0].w);
			RowType r2 = RowType(mat[1].xyz() * p, mat[1].w);
			RowType r3 = RowType(mat[2].xyz() * p, mat[2].w);
			return matrix4(r1, r2, r3, mat[3]);
		}
	};
}

