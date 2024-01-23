#pragma once
struct Position
{
public:
	float x, y, z;
	Position(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
struct DegreeWithDirection
{
public:
	float deg;
	char direction;
	DegreeWithDirection(float degree, char direction) {
		this->deg = degree;
		this->direction = direction;
	}

};
