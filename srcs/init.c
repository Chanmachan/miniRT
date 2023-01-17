#include "../includes/minirt.h"

void	init(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->img_ptr = mlx_new_image(info->mlx_ptr, WIDTH, HEIGHT);
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	info->img_data = mlx_get_data_addr(info->img_ptr, &info->bits_per_pixel, &info->line_length, &info->endian);
	info->bytes_per_pixel = info->bits_per_pixel / 8;
}

void	init_color(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
