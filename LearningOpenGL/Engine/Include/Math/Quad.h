#pragma once

#include <Prerequisites.h>

class Quad
{
public:
	Quad(){}
	Quad(I32 width, I32 height) : width(width), height(height) {}
	Quad(I32 left, I32 top, I32 width, I32 height) : left(left), top(top), width(width), height(height) {}
	Quad(const Quad& quad) : left(quad.left), top(quad.top), width(quad.width), height(quad.height) {}
public:
	int width = 0, height = 0, left = 0, top = 0;
};

