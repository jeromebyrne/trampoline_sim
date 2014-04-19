#ifndef MATRIX4x4_H
#define MATRIX4x4_H

#define EPSILONSQUARED 0.001 * 0.001

class Matrix4x4
{
private:
		
	// 4 by 4 matrix elements
		float m11,m12,m13,m14;			        
		float m21,m22,m23,m24;
		float m31,m32,m33,m34;          
		float m41,m42,m43,m44;

public:
		friend inline Matrix4x4 operator-(const Matrix4x4 &a);
		friend inline Matrix4x4 operator+(const Matrix4x4 &a, const Matrix4x4 &b);
		friend inline Matrix4x4 operator-(const Matrix4x4 &a, const Matrix4x4 &b);
		friend inline Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &b);
		friend inline Matrix4x4& operator+=(Matrix4x4 &a, const Matrix4x4 &b);
		friend inline Matrix4x4& operator-=(Matrix4x4 &a, const Matrix4x4 &b);
		friend inline Matrix4x4& operator*=(Matrix4x4 &a, const Matrix4x4 &b);

		friend inline Vector3 operator*(const Matrix4x4 &matrix, const Vector3 &vector);
		friend inline Vector3 operator*(const Vector3 &vector, const Matrix4x4 &matrix);
		friend inline Vector3& operator*=(Vector3 &vector, const Matrix4x4 &matrix);

		friend inline Matrix4x4 operator*(const Matrix4x4 &a, float s);
		friend inline Matrix4x4 operator/(const Matrix4x4 &a, float s);
		friend inline Matrix4x4& operator*=(Matrix4x4 &a, float s);
		friend inline Matrix4x4& operator/=(Matrix4x4 &a, float s);
		friend inline Matrix4x4 operator*(float s, const Matrix4x4 &a);
		friend inline Matrix4x4& operator*=(float s, Matrix4x4 &a);

		Matrix4x4() {};// default constructor

		/// construct a matrix from three basis vectors.
		/// the x,y,z values from each of these basis vectors map to rows in the 3x3 sub matrix.
		/// note: the rest of the matrix (row 4 and column 4 are set to identity)

		Matrix4x4(const Vector3 &a, const Vector3 &b, const Vector3 &c)
		{
			// ax ay az 0
			// bx by bz 0
			// cx cy cz 0
			// 0  0  0  1

			m11 = a.X;
			m12 = a.Y;
			m13 = a.Z;
			m14 = 0;
			m21 = b.X;
			m22 = b.Y;
			m23 = b.Z;
			m24 = 0;
			m31 = c.X;
			m32 = c.Y;
			m33 = c.Z;
			m34 = 0;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}
		
		// constructor which takes explicit values for the 3x3 part of the matrix - rest stays as identity
		Matrix4x4(float m11, float m12, float m13,
			   float m21, float m22, float m23,
			   float m31, float m32, float m33)
		{
			this->m11 = m11;
			this->m12 = m12;
			this->m13 = m13;
			this->m14 = 0;
			this->m21 = m21;
			this->m22 = m22;
			this->m23 = m23;
			this->m24 = 0;
			this->m31 = m31;
			this->m32 = m32;
			this->m33 = m33;
			this->m34 = 0;
			this->m41 = 0;
			this->m42 = 0;
			this->m43 = 0;
			this->m44 = 1;
		}
		
		// constructor which takes explicit values for the whole matrix
		Matrix4x4(float m11, float m12, float m13, float m14,
			      float m21, float m22, float m23, float m24,
			      float m31, float m32, float m33, float m34,
			      float m41, float m42, float m43, float m44)
		{
			this->m11 = m11;
			this->m12 = m12;
			this->m13 = m13;
			this->m14 = m14;
			this->m21 = m21;
			this->m22 = m22;
			this->m23 = m23;
			this->m24 = m24;
			this->m31 = m31;
			this->m32 = m32;
			this->m33 = m33;
			this->m34 = m34;
			this->m41 = m41;
			this->m42 = m42;
			this->m43 = m43;
			this->m44 = m44;
		}

		// create matrix from float array
		Matrix4x4(const float data[])
		{
			this->m11 = data[0];
			this->m12 = data[1];
			this->m13 = data[2];
			this->m14 = data[3];
			this->m21 = data[4];
			this->m22 = data[5];
			this->m23 = data[6];
			this->m24 = data[7];
			this->m31 = data[8];
			this->m32 = data[9];
			this->m33 = data[10];
			this->m34 = data[11];
			this->m41 = data[12];
			this->m42 = data[13];
			this->m43 = data[14];
			this->m44 = data[15];
		}
		
		// set the matrix to zero
		void Zero()
		{
			m11 = 0;
			m12 = 0;
			m13 = 0;
			m14 = 0;
			m21 = 0;
			m22 = 0;
			m23 = 0;
			m24 = 0;
			m31 = 0;
			m32 = 0;
			m33 = 0;
			m34 = 0;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 0;
		}
		
		// set to identity matrix
		void Identity()
		{
			m11 = 1;
			m12 = 0;
			m13 = 0;
			m14 = 0;
			m21 = 0;
			m22 = 1;
			m23 = 0;
			m24 = 0;
			m31 = 0;
			m32 = 0;
			m33 = 1;
			m34 = 0;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}
		
		// set to a translation matrix
		void Translate(float x, float y, float z)
		{
			m11 = 1;		  // 1 0 0 x 
			m12 = 0;		  // 0 1 0 y
			m13 = 0;		  // 0 0 1 z
			m14 = x;		  // 0 0 0 1
			m21 = 0;
			m22 = 1;
			m23 = 0;
			m24 = y;
			m31 = 0;
			m32 = 0;
			m33 = 1;
			m34 = z;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}

		/// set to a translation matrix.

		void Translate(const Vector3 &vector)
		{
			m11 = 1;		  // 1 0 0 x 
			m12 = 0;		  // 0 1 0 y
			m13 = 0;		  // 0 0 1 z
			m14 = vector.X;   // 0 0 0 1
			m21 = 0;
			m22 = 1;
			m23 = 0;
			m24 = vector.Y;
			m31 = 0;
			m32 = 0;
			m33 = 1;
			m34 = vector.Z;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}

		/// set to a scale matrix.

		void Scale(float s)
		{
			m11 = s;
			m12 = 0;
			m13 = 0;
			m14 = 0;
			m21 = 0;
			m22 = s;
			m23 = 0;
			m24 = 0;
			m31 = 0;
			m32 = 0;
			m33 = s;
			m34 = 0;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}

		/// set to a diagonal matrix.

		void Diagonal(float a, float b, float c, float d = 1)
		{
			m11 = a;
			m12 = 0;
			m13 = 0;
			m14 = 0;
			m21 = 0;
			m22 = b;
			m23 = 0;
			m24 = 0;
			m31 = 0;
			m32 = 0;
			m33 = c;
			m34 = 0;
			m41 = 0;
			m42 = 0;
			m43 = 0;
			m44 = d;
		}

		/// set to a rotation matrix about a specified axis / angle.
		
		void Rotate(float angle, Vector3 axis)
		{
			if (axis.LengthSquared()<EPSILONSQUARED)
			{
				Identity();
			}
			else
			{
				axis.Normalise();

				float fCos = (float) cos(angle);
				float fSin = (float) sin(angle);
				float fOneMinusCos = 1.0f-fCos;
				float fX2 = axis.X*axis.X;
				float fY2 = axis.Y*axis.Y;
				float fZ2 = axis.Z*axis.Z;
				float fXYM = axis.X*axis.Y*fOneMinusCos;
				float fXZM = axis.X*axis.Z*fOneMinusCos;
				float fYZM = axis.Y*axis.Z*fOneMinusCos;
				float fXSin = axis.X*fSin;
				float fYSin = axis.Y*fSin;
				float fZSin = axis.Z*fSin;
			
				m11 = fX2*fOneMinusCos+fCos;
				m12 = fXYM-fZSin;
				m13 = fXZM+fYSin;
				m14 = 0;
				
				m21 = fXYM+fZSin;
				m22 = fY2*fOneMinusCos+fCos;
				m23 = fYZM-fXSin;
				m24 = 0;
				
				m31 = fXZM-fYSin;
				m32 = fYZM+fXSin;
				m33 = fZ2*fOneMinusCos+fCos;
				m34 = 0;
				
				m41 = 0;
				m42 = 0;
				m43 = 0;
				m44 = 1;
			}
		}

		void Lookat( Vector3 &eye,  Vector3 &at,  Vector3 &up)
		{
			// left handed

			Vector3 z_axis = at - eye;
			Vector3 x_axis = up.Cross(z_axis);
			Vector3 y_axis = z_axis.Cross(x_axis);

			x_axis.Normalise();
			y_axis.Normalise();
			z_axis.Normalise();

			m11	= x_axis.X;
			m12 = x_axis.Y;
			m13 = x_axis.Z;
			m14 = - x_axis.Dot(eye);

			m21	= y_axis.X;
			m22 = y_axis.Y;
			m23 = y_axis.Z;
			m24 = - y_axis.Dot(eye);

			m31	= z_axis.X;
			m32 = z_axis.Y;
			m33 = z_axis.Z;
			m34 = - z_axis.Dot(eye);

			m41	= 0;
			m42 = 0;
			m43 = 0;
			m44 = 1;
		}


};
#endif