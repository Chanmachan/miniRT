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

bool	is_crossed_with_sph(t_vec eye_dir, t_vec eye_to_sph, float r)
{
	float	a;
	float	b;
	float	c;

	a = vec_equ(eye_to_sph);
	b = 2 * innner_product(eye_dir, eye_to_sph);
	c = vec_equ(eye_dir) - r * r;
	return (b * b - 4 * a * c >= 0);
}

void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	dst = info->img_data + (y * info->line_length + x * info->bytes_per_pixel);
	*(int *)dst = color;
}

void	draw_win(t_info *info)
{
	int		x;
	int		y;
	t_vec	eye_dir;
	t_vec	eye_to_sph;
	float	r;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			eye_dir = init_vec(0, 0, 1000);
			eye_to_sph = get_vec_diff(x, y, eye_dir);
			r = (float )0.5;
			if (is_crossed_with_sph(eye_dir, eye_to_sph, r))
				put_pixel(info, x, y, create_rgb(255, 0, 0));
			else
				put_pixel(info, x, y, create_rgb(100, 149, 237));
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
