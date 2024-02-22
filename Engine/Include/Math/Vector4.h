#pragma once

#include <Prerequisites.h>

class Vector4
{
public:
	Vector4()
	{}

	Vector4(F32 x, F32 y, F32 z, F32 w) : x(x), y(y), z(z), w(w)
	{}

	~Vector4()
	{}

public:
	F32 x = 0, y = 0, z = 0, w = 0;
};
