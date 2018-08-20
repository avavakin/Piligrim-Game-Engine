#pragma once
class Shader;
struct vec3;

class IDrawable
{
public:
	virtual void draw() = 0;
};