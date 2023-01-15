//
// Created by 本間優之介 on 2023/01/14.
//

#ifndef MINIRT_MINIRT_H
# define MINIRT_MINIRT_H

# define ESC 65307
# define WIDTH 400
# define HEIGHT 400

# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# include "../gnl/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_dis
{
	float	a;
	float	b;
	float	c;
}				t_dis;

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct s_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		bytes_per_pixel;
}				t_info;

//vec
t_vec	init_vec(float x, float y, float z);
t_vec	get_vec_diff(int x, int y, t_vec eye_dir);
float	vec_equ(t_vec v);
// utils
int	create_rgb(int r, int g, int b);
float	innner_product(t_vec v1, t_vec v2);
int	close_window(t_info *info);

#endif //MINIRT_MINIRT_H
