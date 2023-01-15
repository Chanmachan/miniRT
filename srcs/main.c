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

void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	dst = info->img_data + (y * info->line_length + x * info->bytes_per_pixel);
	*(int *)dst = color;
}

float	is_crossed_with_sph(t_dis dis)
{
	return (dis.b * dis.b - 4 * dis.a * dis.c);
}

//coefficient = 係数
float	get_coef(t_vec eye_dir, t_vec eye_to_sph, float r)
{
	t_dis	dis;
	float	t;
	float	t1;
	float	t2;
	float	d;

	dis.a = vec_equ(eye_to_sph);
	dis.b = 2 * innner_product(eye_dir, eye_to_sph);
	dis.c = vec_equ(eye_dir) - r * r;
	d = is_crossed_with_sph(dis);
	t = -1;
	if (d == 0)
	{
		printf("piyo\n");
		t = - dis.b / (2 * dis.a);
	}
	else if (d > 0)
	{
		printf("hoge\n");
		t1 = (- 1 * dis.b - sqrtf(d)) / (2 * dis.a);
		t2 = (- 1 * dis.b + sqrtf(d)) / (2 * dis.a);
		if (t1 > 0 && t2 > 0)
			t = ft_min(t1, t2);
		else
			t = ft_max(t1, t2);
	}
	return (t);
}

float	crossed_sphere_process(t_vec eye_dir, t_vec eye_to_sph, float t)
{
	t_vec	int_pos;//レイと球の交点位置
	t_vec	light_dir;//入射ベクトル
	t_vec	sphere_n;//球面の法線
	t_vec	pl;//光源位置

	float	nl_dot;//内積

	int_pos.x = eye_dir.x + t * eye_to_sph.x;
	int_pos.y = eye_dir.y + t * eye_to_sph.y;
	int_pos.z = eye_dir.z + t * eye_to_sph.z;

	pl = init_vec(-5, 5, -5);
	light_dir = init_vec(pl.x - int_pos.x, pl.y - int_pos.y, pl.z - int_pos.z);
	light_dir = normalize_vec(light_dir);

	sphere_n = init_vec(int_pos.x, int_pos.y, int_pos.z);
	sphere_n = normalize_vec(sphere_n);

	nl_dot = innner_product(light_dir, sphere_n);
	if (nl_dot < 0)
		nl_dot = 0;
	return (nl_dot);
}

void	draw_win(t_info *info)
{
	int		x;
	int		y;
	t_vec	eye_dir;
	t_vec	eye_to_sph;
	float	r;
	float	t;
	float	nl_dot;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			eye_dir = init_vec(0, 0, -5);
			eye_to_sph = get_vec_diff(x, y, eye_dir);
			r = (float )0.5;
			//
			t = get_coef(eye_dir, eye_to_sph, r);
			if (t > 0)
			{
				nl_dot = crossed_sphere_process(eye_dir, eye_to_sph, t);
				put_pixel(info, x, y, create_rgb(255 * (int)nl_dot, 0, 255 * (int)nl_dot));
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

void	init(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->img_ptr = mlx_new_image(info->mlx_ptr, WIDTH, HEIGHT);
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	info->img_data = mlx_get_data_addr(info->img_ptr, &info->bits_per_pixel, &info->line_length, &info->endian);
	info->bytes_per_pixel = info->bits_per_pixel / 8;
}

int main()
{
	t_info	info;

	init(&info);
	hook(&info);
}
