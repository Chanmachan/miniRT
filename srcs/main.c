//
// Created by 本間優之介 on 2023/01/12.
//
#include "../includes/minirt.h"

int	key_handler(int keycode, t_info *info)
{
	if (keycode == ESC)
		close_window(info);
	return (0);
}

/*
float	is_crossed_with_sph(t_dis dis)
{
	return (dis.b * dis.b - 4 * dis.a * dis.c);
}
 */

//coefficient = 係数
float	get_coef(t_vec eye_dir, t_vec eye_to_sph, float r)
{
	t_dis	dis;
	float	t1;
	float	t2;
	float	d;

	dis.a = vec_equ(eye_to_sph);
	dis.b = 2 * innner_product(eye_dir, eye_to_sph);
	dis.c = vec_equ(eye_dir) - r * r;
	d = is_crossed_with_sph(dis);
	if (d == 0)
	{
		return (- dis.b / (2 * dis.a));
	}
	if (d > 0)
	{
		t1 = (- 1 * dis.b + sqrtf(d)) / (2 * dis.a);
		t2 = (- 1 * dis.b - sqrtf(d)) / (2 * dis.a);
		if (t1 > 0 && t2 > 0)
			return (ft_min(t1, t2));
		else
			return (ft_max(t1, t2));
	}
	return (-1);
}

float	crossed_sphere_process(t_vec eye_dir, t_vec eye_to_sph, float t)
{
	t_vec	int_pos;//レイと球の交点位置
	t_vec	light_dir;//入射ベクトル
	t_vec	sphere_n;//球面の法線ベクトル
	t_vec	pl;//光源位置
	float	Ra, Rd, Rs, Rr;
	t_vec	r;
	t_vec	v;

	float	nl_dot, vr_dot;//内積

	//交点位置を計算
	int_pos.x = eye_dir.x + t * eye_to_sph.x;
	int_pos.y = eye_dir.y + t * eye_to_sph.y;
	int_pos.z = eye_dir.z + t * eye_to_sph.z;
	//入射ベクトルを計算、正規化
	pl = init_vec(-5, 5, -5);
	light_dir = init_vec(pl.x - int_pos.x, pl.y - int_pos.y, pl.z - int_pos.z);
	light_dir = normalize_vec(light_dir);

	//法線ベクトルを計算、正規化
	sphere_n = init_vec(int_pos.x, int_pos.y, int_pos.z);
	sphere_n = normalize_vec(sphere_n);
	//環境光の反射光の放射輝度Raを計算
	Ra = 0.01 * 0.1;

	nl_dot = innner_product(light_dir, sphere_n);
	if (nl_dot < 0)
		nl_dot = 0;

	Rd = 0.69 * 1.0 * nl_dot;
	//正反射ベクトルrを計算(2-2)
	if (nl_dot > 0)
	{
		r.x = 2 * nl_dot * sphere_n.x - light_dir.x;
		r.y = 2 * nl_dot * sphere_n.y - light_dir.y;
		r.z = 2 * nl_dot * sphere_n.z - light_dir.z;
		//視線ベクトルの逆
		v = init_vec(- 1 * eye_dir.x, - 1 * eye_dir.y, - 1 * eye_dir.z);
		v = normalize_vec(v);
		//内積
		vr_dot = innner_product(v, r);
		//直接光の鏡面反射光の放射輝度Rsを計算
		Rs = 0.3 * 1.0 * powf(vr_dot, 8);
	}
	else
		Rs = 0;
	Rr = Ra + Rd + Rs;
	return (Rr);
}

/*
void	draw_win(t_info *info)
{
	int		x;
	int		y;
	t_vec	eye_dir;
	t_vec	eye_to_sph;
	float	r;
	float	t;
	float	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			eye_dir = init_vec(0, 0, -5);
			eye_to_sph = diff_vec(screen_to_coord(x, y),eye_dir);
			r = (float )0.5;
			//
			t = get_coef(eye_dir, eye_to_sph, r);
			if (t > 0)
			{
				color = crossed_sphere_process(eye_dir, eye_to_sph, t);
				put_pixel(info, x, y, create_rgb(255 * color, 255 * color, 255 * color));
			}
			else
			{
				put_pixel(info, x, y, create_rgb(100, 149, 237));
			}
			x++;
		}
		y++;
	}
}
*/

int draw_win(t_info *info)
{
	int				x, y;
	t_scene			scene;
	const t_vec		eye_pos = {0, 0, -5};//始点位置
	t_ray			eye_ray;
	t_color			color;


	// とりあえずmalloc???
	scene.lights = malloc(sizeof(t_light));
	scene.shapes = malloc(sizeof(t_shape));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color = init_color(100, 149, 237);
			eye_ray.start = eye_pos;
			eye_ray.direction = diff_vec(screen_to_coord(x, y), eye_pos);

			raytrace(&scene, &eye_ray, &color);

			put_pixel(info, x, y, create_rgb(color));
			x++;
		}
		y++;
	}
	free(scene.lights);
	free(scene.shapes);
	return (0);
}

int	loop_handler(t_info *info)
{
	draw_win(info);
	mlx_put_image_to_window(info->mlx_ptr, info->win_ptr, info->img_ptr, 0, 0);
	return (0);
}

void	hook(t_info *info)
{
	mlx_loop_hook(info->mlx_ptr, loop_handler, info);
	mlx_hook(info->win_ptr, 17, 1L << 0, close_window, info);
	mlx_hook(info->win_ptr, 2, 1L << 0, key_handler, info);
	mlx_loop(info->mlx_ptr);
}

int main()
{
	t_info	info;

	init(&info);
	hook(&info);
}
