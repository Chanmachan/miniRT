#include "../includes/minirt.h"

t_dis	intersect_discriminant(t_shape *shape, t_ray *ray)
{
	t_dis		dis;
	float		t1;
	float		t2;
	t_sphere	*sphere;
	t_vec		pe_pc;

	sphere = &shape->u_data.sphere;
	pe_pc = diff_vec(ray->start, sphere->center);
	dis.a = innner_product(ray->direction, ray->direction);
	dis.b = 2 * innner_product(pe_pc, ray->direction);
	dis.c = innner_product(pe_pc, pe_pc) - sphere->radius * sphere->radius;
	dis.d = dis.b * dis.b - 4 * dis.a * dis.c;
	dis.t = -1;
	if (dis.d == 0)
	{
		dis.t = -dis.b / (2 * dis.a);
	}
	else if (dis.d > 0)
	{
		t1 = (- 1 * dis.b + sqrtf(dis.d)) / (2 * dis.a);
		t2 = (- 1 * dis.b - sqrtf(dis.d)) / (2 * dis.a);
		if (t1 > 0 && t2 > 0)
			dis.t = ft_min(t1, t2);
		else
			dis.t = ft_max(t1, t2);
	}
	return (dis);
}

int	intersect_sph(t_shape *shape, t_ray *ray, t_intersect_point *out_intp)
{
	t_dis		dis;
	t_sphere	*sphere;

	dis = intersect_discriminant(shape, ray);
	sphere = &shape->u_data.sphere;
	if (0 < dis.t)
	{
		if (out_intp)
		{
			out_intp->distance = dis.t;
			//最も近い物体の構造体のポインタを計算
			out_intp->position = add_vec(ray->start, multiple_vec(dis.t, ray->direction));
			//交点における物体表面の法線ベクトル
			out_intp->normal = diff_vec(out_intp->position, sphere->center);
			out_intp->normal = normalize_vec(out_intp->normal);
		}
		return (1);
	}
	return (0);
}

int	intersect_plane(t_shape *shape, t_ray *ray, t_intersect_point *out_intp)
{
	const t_plane *pln;
	float dn_dot;

	pln = &shape->u_data.plane;
	dn_dot = dot_vec(ray->direction, pln->normal);
	if ( dn_dot != 0 )
	{
		t_vec s_p;
		float t;

		s_p.x = ray->start.x - pln->position.x;
		s_p.y = ray->start.y - pln->position.y;
		s_p.z = ray->start.z - pln->position.z;

		t = -dot_vec(s_p, pln->normal) / dn_dot;

		if ( t > 0 )
		{
			if ( out_intp )
			{
				out_intp->distance = t;

				out_intp->position.x = ray->start.x + t * ray->direction.x;
				out_intp->position.y = ray->start.y + t * ray->direction.y;
				out_intp->position.z = ray->start.z + t * ray->direction.z;

				out_intp->normal = pln->normal;
			}

			return 1;
		}
		else
			return (0);
	}
	return (0);
}

int	intersect(t_shape *shape, t_ray *ray, t_intersect_point *out_intp)
{
	if (shape->type == SPHERE)
		return (intersect_sph(shape, ray, out_intp));
	if (shape->type == PLANE)
		return (intersect_plane(shape, ray, out_intp));
	return (0);
}

int	get_nearest_shape(t_scene *scene, t_ray *ray, float max_dist, int exit_once_found, t_shape **out_shape, t_intersect_point *out_intp)
{
	size_t	i;
	t_shape *nearest_shape = NULL;
	t_intersect_point nearest_intp;
	nearest_intp.distance = max_dist;
	t_intersect_point intp;

	i = 0;
	while (i < scene->num_shapes)
	{
		int res;

		res = intersect(&scene->shapes[i]	, ray, &intp);
		if ( res && intp.distance < nearest_intp.distance )
		{
			nearest_shape = &scene->shapes[i];
			nearest_intp = intp;
			if ( exit_once_found ) break;
		}
		i++;
	}

	if ( nearest_shape )
	{
		if ( out_shape )
			*out_shape = nearest_shape;
		if ( out_intp )
			*out_intp = nearest_intp;

		return 1;
	}
	else
	{
		return 0;
	}
}

int	raytrace(t_scene *scene, t_ray *eye_ray, t_color *out_color)
{
	t_shape				*shape; //交差した物体へのポインタ
	t_intersect_point	int_p; //交点
	int					res;
	size_t				i;
	t_vec				light_dir;
	const t_light		*light;
	float				nl_dot;
	float				vr_dot;
	t_vec				ref_dir;//正反射ベクトル
	t_vec				inv_eye_dir;
	float				vr_dot_pow;

	//tmp
	res = get_nearest_shape(scene, eye_ray, FLT_MAX, 0, &shape, &int_p);

	if (res)
	{
		out_color->r = scene->ambient_illuminance.r * shape->material.ambient_ref.r;
		out_color->g = scene->ambient_illuminance.g * shape->material.ambient_ref.g;
		out_color->b = scene->ambient_illuminance.b * shape->material.ambient_ref.b;
		i = 0;
		while (i < scene->num_lights)
		{
			light = &scene->lights[i];
			if (light->type == POINT)
				light_dir = normalize_vec(diff_vec(scene->lights[i].vec, int_p.position));
			else if (light->type == DIRECTIONAL)
				light_dir = normalize_vec(multiple_vec(-1, scene->lights[i].vec));
			nl_dot = innner_product(int_p.normal, light_dir);
			nl_dot = ft_min(ft_max(nl_dot, 0), 1);
			out_color->r += shape->material.diffuse_ref.r * scene->lights[i].illuminance.r * nl_dot;
			out_color->g += shape->material.diffuse_ref.g * scene->lights[i].illuminance.g * nl_dot;
			out_color->b += shape->material.diffuse_ref.b * scene->lights[i].illuminance.b * nl_dot;
			if (nl_dot > 0)
			{
				//正反射ベクトル
				ref_dir = normalize_vec(diff_vec(multiple_vec(2 * nl_dot, int_p.normal), light_dir));
				//視線ベクトルの逆ベクトルの計算
				inv_eye_dir = normalize_vec(multiple_vec(-1, eye_ray->direction));
				//上二つの内積
				vr_dot = innner_product(ref_dir, inv_eye_dir);
				vr_dot = ft_min(ft_max(vr_dot, 0), 1);
				vr_dot_pow = powf(vr_dot, scene->shapes->material.shininess);
				//鏡面反射光の計算
				out_color->r += shape->material.specular_ref.r * scene->lights[i].illuminance.r * vr_dot_pow;
				out_color->g += shape->material.specular_ref.g * scene->lights[i].illuminance.g * vr_dot_pow;
				out_color->b += shape->material.specular_ref.b * scene->lights[i].illuminance.b * vr_dot_pow;
			}
			i++;
		}

		out_color->r = 255 * ft_min(ft_max(out_color->r, 0), 1);
		out_color->g = 255 * ft_min(ft_max(out_color->g, 0), 1);
		out_color->b = 255 * ft_min(ft_max(out_color->b, 0), 1);

		return (1);
	}
	else
		{
			return (0);
		}
}
