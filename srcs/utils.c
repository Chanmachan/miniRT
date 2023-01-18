//
// Created by 本間優之介 on 2023/01/15.
//
#include "../includes/minirt.h"

int	create_rgb(t_color color)
{
	return ((int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

float	inner_product(t_vec v1, t_vec v2)
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

t_vec	screen_to_coord(int x, int y)
{
	t_vec	ret;

	ret.x = 2 * (float)x / (WIDTH - 1) - 1;
	ret.y = -2 * (float)y / (HEIGHT - 1) + 1;
	ret.z = 0;
	return (ret);
}

void	put_pixel(t_info *info, int x, int y, int color)
{
	char	*dst;

	dst = info->img_data + (y * info->line_length + x * info->bytes_per_pixel);
	*(int *)dst = color;
}

float	rand_restricted(float min, float max)
{
	return (min + (float)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX)));
}
