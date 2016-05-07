
#include "mhelp.h"
#include "core.h"
float tanks::grad_to_rad(float grad)
{
	return (grad * R_PI) / 180;
};

float tanks::rad_to_grad(float rad)
{
	return rad * 180.0 / R_PI;
}

float tanks::get_angle_between_vectors(Vector3 v1, Vector3 v2)
{
	float rad_angle_betwen = acos(
		(v1.x * v2.x + v1.y * v2.y + v1.z * v2.z) /
		(sqrt(pow(v1.x, 2) + pow(v1.y, 2) + pow(v1.z, 2)) * sqrt(pow(v2.x, 2) + pow(v2.y, 2) + pow(v2.z, 2)))
		);

	return tanks::rad_to_grad(rad_angle_betwen);
}

float tanks::get_angle_between_objects(Vector3 current_position, Vector3 current_direction, Vector3 next_position)
{
	// vertex from object to player
	float vpx = next_position.x - current_position.x;
	float vpy = next_position.y - current_position.y;
	float vpz = next_position.z - current_position.z;

	float rad_angle_betwen = acos(
		(current_direction.x * vpx + current_direction.y * vpy + current_direction.z * vpz)
		/
		(
			sqrt(pow(current_direction.x, 2) + pow(current_direction.y, 2) + pow(current_direction.z, 2)) *
			sqrt(pow(vpx, 2) + pow(vpy, 2) + pow(vpz, 2))
			));

	float grad_angle_betwen = tanks::rad_to_grad(rad_angle_betwen);
	return grad_angle_betwen;
};

Vector3 tanks::get_orthogonal(Vector3 direction)
{
	/*
	get perpendicular vector towards current
	u * v = vx * ux + vy * uy + vz * uz = 0
	ux = 1, uy = 1 - arbitrary
	vz * uz = -vx * ux - vy * uy
	uz = (-vx * ux - vy * uy) / vz
	*/
	float vx = direction.x, vy = direction.y, vz = direction.z;
	float ux = 0, uy = 0;
	float uz = (-vx * ux - vy * uy) / vz;
	Vector3 orthogonal = Vector3(ux, uy, uz);
	orthogonal.normalise();
	return orthogonal;
};

float tanks::direction_to_angle(float x, float y)
{
	/*
		| arctan(y/x)			if x > 0
		| arctan(y / x) + Pi	if x < 0 and y >= 0
	Q =	| arctan(y / x) - Pi	if x < 0 and y < 0
		| Pi/2					if x = 0 and y > 0
		| -Pi/2					if x = 0 and y < 0
		| 0						if x = 0 and y = 0
 	*/
	
	if (x > 0)
		return tanks::rad_to_grad(atan(y / x));

	if (x < 0 && y >= 0)
		return tanks::rad_to_grad(atan(y / x) + R_PI);

	if(x < 0 && y < 0)
		return tanks::rad_to_grad(atan(y / x) - R_PI);

	if(x == 0 && y > 0)
		return tanks::rad_to_grad(R_PI / 2);

	if(x == 0 && y < 0)
		return tanks::rad_to_grad(-R_PI / 2);

	return tanks::rad_to_grad(0);
};

Vector3 angle_to_direction(float angle, float magnitude)
{
	/*
		(r, Q) -> (x, y) = r * cosQ , r * sinQ
	*/
	float x = magnitude * cos(angle);
	float z = magnitude * sin(angle);
	Vector3 direction(x, 0.0, z);
	return direction;
};
