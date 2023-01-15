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

t_vec	diff_vec(t_vec v1, t_vec v2)
{
	t_vec	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec	normalize_vec(t_vec bef)
{
	t_vec	id;
	float	abs;

	abs = sqrtf(vec_equ(bef));
	id.x = bef.x / abs;
	id.y = bef.y / abs;
	id.z = bef.z / abs;
	return (id);
}

float	vec_equ(t_vec v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}