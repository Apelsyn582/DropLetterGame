#include "Object.h"

Object::Object(int Value, int X, int Y)
{
	value = Value;
	x = X;
	y = Y;
	is_static = false;
	enable_left_arrow = true;
	enable_right_arrow = true;
}

Object::Object(int X, int Y)
{
	x = X;
	y = Y;
	is_static = false;
}

void Object::DownwardMovement()
{
	if(!this->is_static) x++;
}

void Object::LeftArrow()
{
	if (!is_static && y - 1 != -1 && enable_left_arrow) y--;
}

void Object::RightArrow()
{
	if (!this->is_static && y + 1 != 5 && enable_right_arrow) y++;
}

void Object::DoStatic()
{
	is_static = true;
}

void Object::ChangeValue()
{
	value += '1' - '0';
}