#include "../includes/minirt.h"

t_dis	intersect_discriminant(t_shape *shape, t_ray *ray)
{
	t_dis		dis;
	float		r;
	float		t1;
	float		t2;
	t_sphere	sphere;

	sphere = shape->u_data.sphere;
	dis.a = vec_equ(ray->direction);
	dis.b = 2 * innner_product(ray->start, ray->direction);
	dis.c = vec_equ(ray->start) - sphere.radius * sphere.radius;
	dis.d = dis.b * dis.b - 4 * dis.a * dis.c;
	if (dis.d >= 0)
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
	t_sphere	sphere;

	sphere = shape->u_data.sphere;
	dis = intersect_discriminant(shape, ray);
	if (0 <= dis.d)
	{
		//最も近い物体の構造体のポインタを計算
		out_intp->position = add_vec(ray->start, multiple_vec(dis.t, ray->direction));
		//交点が存在する物体の情報を色々詰める
		out_intp->distance = dis.t;
		//交点における物体表面の法線ベクトル
		out_intp->normal = diff_vec(out_intp->position, sphere.center);
		out_intp->normal = normalize_vec(out_intp->normal);
	}
}

int	intersect(t_shape *shape, t_ray *ray, t_intersect_point *out_intp)
{
	if (shape->type == SPHERE)
		return (intersect_sph(shape, ray, out_intp));
	return (0);
}

int	get_nearest_shape(t_scene *scene, t_ray *ray, float max_dist, int exit_once_found, t_shape **out_shape, t_intersect_point *out_intp)
{
	/*size_t	i = 0;

	while (i < scene->num_shapes)
	{
		if (intersect(&scene->shapes[i], ray, out_intp))
		{
			return (1);
		}
		i++;
	}
	return (0);*/
	(void)max_dist;
	(void)exit_once_found;
	if (intersect(scene->shapes, ray, out_intp))
		return (1);
	return (0);
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
	res = get_nearest_shape(scene, eye_ray, FLT_MAX, 1, &shape, &int_p);
	if (res)
	{
		init_color(out_color, 0, 0, 0);
		i = 0;
		while (i < scene->num_lights)
		{
			light = &scene->lights[i];
			if (light->type == POINT)
				light_dir = normalize_vec(diff_vec(scene->lights[i].vec, int_p.position));
			else if (light->type == DIRECTIONAL)
				light_dir = normalize_vec(multiple_vec(-1, scene->lights[i].vec));
			nl_dot = innner_product(int_p.normal, light_dir);
			if (nl_dot < 0)
				nl_dot = 0;
			out_color->r += scene->shapes->material.diffuse_ref.r * scene->lights[i].illuminance.r * nl_dot;
			out_color->g += scene->shapes->material.diffuse_ref.g * scene->lights[i].illuminance.g * nl_dot;
			out_color->b += scene->shapes->material.diffuse_ref.b * scene->lights[i].illuminance.b * nl_dot;
			if (nl_dot > 0)
			{
				//正反射ベクトル
				ref_dir = diff_vec(multiple_vec(2 * nl_dot, int_p.normal), light_dir);
				//視線ベクトルの逆ベクトルの計算
				inv_eye_dir = normalize_vec(multiple_vec(-1, eye_ray->direction));
				//上二つの内積
				vr_dot = innner_product(ref_dir, inv_eye_dir);
				vr_dot = ft_min(ft_max(vr_dot, 0), 1);
				vr_dot_pow = powf(vr_dot, scene->shapes->material.shininess);
				//鏡面反射光の計算
				out_color->r += scene->shapes->material.specular_ref.r * scene->lights[i].illuminance.r * vr_dot_pow;
				out_color->g += scene->shapes->material.specular_ref.g * scene->lights[i].illuminance.g * vr_dot_pow;
				out_color->b += scene->shapes->material.specular_ref.b * scene->lights[i].illuminance.b * vr_dot_pow;
			}
			i++;
		}
		return (1);
	}
	else
		return (0);
}
