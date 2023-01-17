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
# include <float.h>
# include <stdarg.h>
# include <stdlib.h>
# include <time.h>
# include "../gnl/includes/get_next_line.h"
# include "../libft/includes/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct	s_color
{
	float	r;
	float	g;
	float	b;
}				t_color;

typedef struct	s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

typedef struct	s_ray
{
	t_vec	start;//始点
	t_vec	direction;//方向ベクトル
}				t_ray;

//物体表面の質感
typedef struct	s_material
{
	t_color	ambient_ref;//環境光反射率(RGB)
	t_color	diffuse_ref;//拡散反射率(RGB)
	t_color	specular_ref;//鏡面反射率(RGB)
	float	shininess;//光沢度
}				t_material;

//形状
typedef struct	s_sphere
{
	t_vec	center;//球の中心
	float	radius;//球の半径
}				t_sphere;

typedef struct	s_plane
{
	t_vec	normal;//法線ベクトル
	t_vec	position;//面が通る点の位置ベクトル
}				t_plane;

typedef enum	e_shape_type
{
	SPHERE,
	PLANE,
}				t_shape_type;

typedef struct	s_shape
{
	t_shape_type	type;
	union
	{
		t_sphere	sphere;//球かか平面のどちらかの情報を持つ
		t_plane		plane;//どっちかは常にNULL?
	}	u_data;
	t_material	material;
}				t_shape;

//光源
typedef enum	e_light_type
{
	POINT,//点光源
	DIRECTIONAL,//平行光源
}				t_light_type;

typedef struct	s_light
{
	t_light_type	type;
	t_vec			vec;//光源位置or光源方向
	t_color			illuminance;//照度(RGB)
}				t_light;

//空中に存在する物体や光源のセットを保持する
typedef struct	s_scene
{
	t_shape	*shapes;//物体リストへのポインタ
	size_t	num_shapes_capa;//物体リストの最大格納数
	size_t	num_shapes;//物体リストに実際に格納されている数
	t_light	*lights;//光源リストへのポインタ
	size_t	num_lights_capa;//光源リストへの最大格納数
	size_t	num_lights;//光源リストに実際格納されている数
	t_color	ambient_illuminance;//環境光の強さ
	t_vec	eye_pos;//始点位
}				t_scene;

typedef struct	s_intersect_point
{
	float	distance;//交点までの距離
	t_vec	position;//交点の位置ベクトル
	t_vec	normal;//交点における物体表面の法線ベクトル
}				t_intersect_point;

typedef struct	s_dis
{
	float	a;
	float	b;
	float	c;
	float	d;
	float	t;
}				t_dis;

typedef struct	s_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		bytes_per_pixel;
	t_scene	*scene;
}				t_info;

// init
void	init(t_info *info);
void	init_color(t_color *color, float r, float g, float b);
// vec
t_vec	init_vec(float x, float y, float z);
t_vec	get_vec_diff(int x, int y, t_vec eye_dir);
float	dot_vec(t_vec v1, t_vec v2);
t_vec	add_vec(t_vec v1, t_vec v2);
t_vec	multiple_vec(float m, t_vec v);
// utils
int		create_rgb(t_color color);
float	innner_product(t_vec v1, t_vec v2);
int		close_window(t_info *info);
t_vec	normalize_vec(t_vec bef);
t_vec	screen_to_coord(int x, int y);
t_vec	diff_vec(t_vec v1, t_vec v2);
void	put_pixel(t_info *info, int x, int y, int color);
float	rand_restricted(float min, float max);
// raytrace
int		raytrace(t_scene *scene, t_ray *eye_ray, t_color *out_color);

#endif //MINIRT_MINIRT_H
