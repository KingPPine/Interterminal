#pragma once
#include <OGL3D/OPrerequisites.h>
#include <OGL3D/Math/OVec3.h>

class OMat4 //4x4 matrix class
{
public:
	OMat4() //default constructor. Sets it to the identity matrix
	{
		setIdentity();
	}

	void setIdentity() //sets this matrix to the identity matrix (diagonal 1's from top left to bottom right, 0' otherwise)
	{
		::memset(mat, 0, sizeof(mat));
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void setScale(const OVec3& scale) //takes in a vector3 and assigns the value to create a scaling matrix. useful in matrix multiplication
	{
		mat[0][0] = scale.x;
		mat[1][1] = scale.y;
		mat[2][2] = scale.z;
	}

	void setTranslation(const OVec3& translation) //takes in a vector3 and assigns the value to create a translation matrix. useful in matrix multiplication
	{
		mat[3][0] = translation.x;
		mat[3][1] = translation.y;
		mat[3][2] = translation.z;
	}

	void setRotationX(f32 x) //takes in a float and assigns the value to create a rotation matrix along the x axis. useful in matrix multiplication
	{
		mat[1][1] = cos(x);
		mat[1][2] = sin(x);
		mat[2][1] = -sin(x);
		mat[2][2] = cos(x);
	}

	void setRotationY(f32 y) //takes in a float and assigns the value to create a rotation matrix along the y axis. useful in matrix multiplication
	{
		mat[0][0] = cos(y);
		mat[0][2] = -sin(y);
		mat[2][0] = sin(y);
		mat[2][2] = cos(y);
	}

	void setRotationZ(f32 z) //takes in a float and assigns the value to create a rotation matrix along the z axis. useful in matrix multiplication
	{
		mat[0][0] = cos(z);
		mat[0][1] = sin(z);
		mat[1][0] = -sin(z);
		mat[1][1] = cos(z);
	}

	void operator *=(const OMat4& matrix) //allows for matrix multiplication
	{
		OMat4 out;

		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.mat[i][j] =
					mat[i][0] * matrix.mat[0][j] +
					mat[i][1] * matrix.mat[1][j] +
					mat[i][2] * matrix.mat[2][j] +
					mat[i][3] * matrix.mat[3][j];
			}
		}
		*this = out;
	}

	void setOrthoLH(f32 width, f32 height, f32 nearPlane, f32 farPlane) //this is to generate an orthogonal matrix based on the values provided. Useful in matrix multiplication
	{
		//orthogonal matrix
		mat[0][0] = 2.0f / width;
		mat[1][1] = 2.0f / height;
		mat[2][2] = 1.0f / (farPlane - nearPlane);
		mat[3][2] = -(nearPlane / (farPlane - nearPlane));
	}

	void setPerspectiveLH(f32 width, f32 height, f32 nearPlane, f32 farPlane) //this is to generate a perspective matrix based on the values provided
	{
		//perspective matrix. https://www.songho.ca/opengl/gl_projectionmatrix.html
		mat[0][0] = (2.0f * nearPlane) / width;
		mat[1][1] = (2.0f * nearPlane) / height;
		mat[2][2] = -(farPlane + nearPlane) / (farPlane - nearPlane);
		mat[2][3] = -1;
		mat[3][2] = (-2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
		mat[3][3] = 0;
	}

	public:
		f32 mat[4][4] = {};
};