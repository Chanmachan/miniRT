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

int draw_win(t_info *info, t_scene *scene)
{
	int				x, y;
	const t_vec		eye_pos = {0, 0, -100};//始点位置
	t_ray			eye_ray;
	t_color			color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			init_color(&color, 100, 149, 237);
			eye_ray.start = eye_pos;
			eye_ray.direction = diff_vec(screen_to_coord(x, y), eye_pos);

			raytrace(scene, &eye_ray, &color);
			put_pixel(info, x, y, create_rgb(color));
			x++;
		}
		y++;
	}
	return (0);
}

int	loop_handler(t_info *info)
{
	draw_win(info, info->scene);
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
	//free
}
