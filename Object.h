#pragma once
#include <iostream>
using namespace std;

class Object
{
	public:
		char value;
		int x;
		int y;
		bool is_static;
		bool enable_left_arrow;
		bool enable_right_arrow;

		Object(int value, int x, int y);

		Object(int x, int y);

		void DownwardMovement();

		void LeftArrow();

		void RightArrow();

		void DoStatic();

		void ChangeValue();

};

