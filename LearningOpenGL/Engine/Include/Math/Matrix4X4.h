#pragma once

#include <Prerequisites.h>
#include <Math\Vector4.h>

class Matrix4X4
{
public:
	Matrix4X4()
	{
		SetIdentity();
	}

	void SetIdentity()
	{
		::memset(mat, 0, sizeof(F32) * 16);
		mat[0][0] = 1;
		mat[1][1] = 1;
		mat[2][2] = 1;
		mat[3][3] = 1;
	}

	void SetScale(const Vector4& scale) 
	{
		mat[0][0] *= scale.x;
		mat[1][1] *= scale.y;
		mat[2][2] *= scale.z;
	}

	void SetTranslation(const Vector4& translation)
	{
		mat[3][0] += translation.x;
		mat[3][1] += translation.y;
		mat[3][2] += translation.z;
	}

	void operator *=(const Matrix4X4 matrix)
	{
		Matrix4X4 out;
		for (auto i = 0; i < 4; i++)
		{
			for (auto j = 0; j < 4; j++)
			{
				out.mat[i][j] = mat[i][0] * matrix.mat[0][j] +
								mat[i][1] * matrix.mat[1][j] +
								mat[i][2] * matrix.mat[2][j] +
								mat[i][3] * matrix.mat[3][j];
			}
		}

		*this = out;
	}


public:
	F32 mat[4][4] = {};
};
