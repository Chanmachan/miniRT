//
// Created by 本間優之介 on 2023/01/15.
//
#include "../includes/minirt.h"

t_vec	init_vec(float x, float y, float z)
{
	t_vec	ret;

	ret.x = x;
	ret.y = y;
	ret.z = z;
	return (ret);
}

t_vec	get_vec_diff(int x, int y, t_vec eye_dir)
{
	t_vec	tmp;
	t_vec	ret;

	//Firstly, convert screen to coord
	tmp.x = 2 * (float)x / (WIDTH - 1) - 1;
	tmp.y = -2 * (float)y / (HEIGHT - 1) + 1;
	tmp.z = 0;

	//diff
	ret.x = eye_dir.x - tmp.x;
	ret.y = eye_dir.y - tmp.y;
	ret.z = eye_dir.z - tmp.z;
	return (ret);
}

float	vec_equ(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}