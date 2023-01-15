//
// Created by 本間優之介 on 2023/01/15.
//
#include "../includes/minirt.h"

int	create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

float	innner_product(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

int	close_window(t_info *info)
{
	mlx_destroy_image(info->mlx_ptr, info->img_ptr);
	mlx_destroy_window(info->mlx_ptr, info->win_ptr);
	mlx_destroy_display(info->mlx_ptr);
	exit(EXIT_SUCCESS);
}