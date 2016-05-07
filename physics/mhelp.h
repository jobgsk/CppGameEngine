#ifndef MATH_HELPER_H
#define MATH_HELPER_H

#include <cmath>

class Vector3;
namespace tanks {

	float grad_to_rad(float grad);

	float rad_to_grad(float rad);
	/*
	angle between of vectors
	*/
	float get_angle_between_vectors(Vector3 v1, Vector3 v2);
	/*
	angle between of objects
	*/
	float get_angle_between_objects(Vector3 current_position, Vector3 current_direction, Vector3 next_position);
	/*
	get perpendicular vector towards current
	*/
	Vector3 get_orthogonal(Vector3 direction);
	/*
	get angle by direction vector around Y
	*/
	float direction_to_angle(float x, float y);

	Vector3 angle_to_direction(float angle);
};
#endif // MATH_HELPER_H
