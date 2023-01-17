#include "../includes/minirt.h"

void init_shape(t_shape* shape, t_shape_type st, ...)
{
	va_list		args;
	t_sphere 	*sph;
	t_plane		*plane;

	va_start(args, st);
	shape->type = st;
	if ( st == SPHERE )
	{
		sph = &shape->u_data.sphere;
		sph->center.x = va_arg(args, double);
		sph->center.y = va_arg(args, double);
		sph->center.z = va_arg(args, double);
		sph->radius   = va_arg(args, double);
	}
	else if ( st == PLANE )
	{
		plane = &shape->u_data.plane;

		plane->position.x = va_arg(args, double);
		plane->position.y = va_arg(args, double);
		plane->position.z = va_arg(args, double);

		plane->normal.x = va_arg(args, double);
		plane->normal.y = va_arg(args, double);
		plane->normal.z = va_arg(args, double);
	}
	else
	{
		fprintf(stderr, "init_shape : unknown shape type.\n");
		abort();
	}

	va_end(args);
}

void init_light(t_light* light, t_light_type lt,
				float vx, float vy, float vz,
				float illR, float illG, float illB)
{
	light->type = lt;
	light->vec = init_vec(vx, vy, vz);
	init_color(&light->illuminance, illR, illG, illB);
}

void init_material(t_material *mat,
				   float ambR, float ambG, float ambB,
				   float difR, float difG, float difB,
				   float speR, float speG, float speB,
				   float shns)
{
	init_color(&mat->ambient_ref, ambR, ambG, ambB);
	init_color(&mat->diffuse_ref, difR, difG, difB);
	init_color(&mat->specular_ref, speR, speG, speB);
	mat->shininess = shns;
}

void scene_setting(t_scene *scene)
{
	/* ************************************************** */
	/* 物体の設定                                         */
	/* ************************************************** */
	scene->num_shapes_capa = 20; /* 物体リストの最大格納数(自由に変更して良い) */

	scene->shapes = malloc(sizeof(t_shape) * scene->num_shapes_capa); /* メモリ確保 */


	/* 物体の初期化 ... init_shape()関数を使う．第一引数は初期化するshape_t構造体のポインタ．*/
	/* 球の場合：第二引数にST_SHAPEを渡す．この場合，追加で4つの実数を渡す． */
	/*           (※ 以下のようにして必ず実数を渡すこと．間違って整数を渡すとうまく動かない．)*/
//	init_shape(&scene->shapes[0], SPHERE,
//			   0.0, 0.0, 5.0, /* 球の中心位置 */
//			   1.0);          /* 球の半径 */

	/* 平面の場合：第二引数にST_PLANEを渡す．この場合，追加で6つの実数を渡す． */

	init_shape(&scene->shapes[0], PLANE,
		   0.0, -0.5, 0.0, //平面が通る点の位置
		   0.0, 1.0, 0.0); //平面の法線ベクトル

	/* 補足：vector_t構造体に値を設定する場合は以下のように，SET_VECTORマクロを使うことができる． */
	/* SET_VECTOR(scene->shapes[0].data.sphere.center, 0, 5, 5); */



	/* マテリアルの初期化 ... init_material()関数を使う．*/
	/* 第一引数は初期化するmaterial_t構造体のポインタ． */
//	init_material(&scene->shapes[0].material,
//				  0.01, 0.01, 0.01,  /* 環境光係数(RGB)   */
//				  0.69, 0.00, 0.00,  /* 拡散反射係数(RGB) */
//				  0.30, 0.30, 0.30,  /* 鏡面反射率(RGB)   */
//				  8.0); /* 光沢度 */
	init_material(&scene->shapes[0].material,
				  0.01, 0.01, 0.01,  /* 環境光係数(RGB)   */
				  0.69, 0.69, 0.69,  /* 拡散反射係数(RGB) */
				  0.30, 0.30, 0.30,  /* 鏡面反射率(RGB)   */
				  8.0); /* 光沢度 */
	scene->num_shapes = 20; /* 物体リストに，実際に格納した物体の数 */
	/* 物体数を変えた場合はそれに合わせて書き換えること． */
	/* 物体リストの先頭 num_shapes 個は初期化されている必要がある． */
	size_t	i;

	i = 1;
	while (i < scene->num_shapes)
	{
		init_material(&scene->shapes[i].material,
					  0.1, 0.1, 0.1,
					  rand_restricted(0.5, 1.0), rand_restricted(0.5, 1.0), rand_restricted(0.5, 1.0),
					  rand_restricted(0.3, 0.5), rand_restricted(0.3, 0.5), rand_restricted(0.3, 0.5),
					  8.0);
		init_shape(&scene->shapes[i], SPHERE,
				   rand_restricted(-2.5, 2.5), rand_restricted(0.0, 2.0), rand_restricted(0.0, 20.0),
				   rand_restricted(0.25, 0.5));
		i++;
	}
	/* ************************************************** */

	/* ************************************************** */
	/* 光源の設定                                         */
	/* ************************************************** */
	/* 環境光の強さ */
	/* colorf_t構造体に値を設定する場合は，このように SET_COLORマクロを使うことができる． */
	init_color(&scene->ambient_illuminance, 0.1, 0.1, 0.1);

	scene->num_lights_capa = 20; /* 光源リストの最大格納数(自由に変更して良い) */
	scene->lights = malloc(sizeof(t_light) * scene->num_lights_capa); /* メモリ確保 */

	/* 光源の初期化 ... init_light()関数を使う． 第一引数は初期化するlight_t構造体のポインタ．*/

	/* 点光源の場合 */
	init_light(&scene->lights[0], POINT,
			   -5.0, 5.0, -5.0, /* 点光源の位置 */
			   1.0, 1.0, 1.0);   /* 点光源の照度(色) */

	/* 平行光源の場合 */
	/*
	init_light(&scene->lights[0], LT_DIRECTIONAL,
		   0.0, -1.0, 0.0,  平行光源の方向ベクトル
		   1.0, 1.0, 1.0);  平行光源の照度(色)
	*/

	scene->num_lights = 1; /* 光源リストに，実際に格納した光源の数 */
	/* 光源数を変えた場合はそれに合わせて書き換えること． */
	/* 光源リストの先頭 num_lights 個は初期化されている必要がある． */
	/* ************************************************** */
	scene->eye_pos = init_vec(0, 0, -5);
}


void	init(t_info *info)
{
	info->mlx_ptr = mlx_init();
	info->img_ptr = mlx_new_image(info->mlx_ptr, WIDTH, HEIGHT);
	info->win_ptr = mlx_new_window(info->mlx_ptr, WIDTH, HEIGHT, "miniRT");
	info->img_data = mlx_get_data_addr(info->img_ptr, &info->bits_per_pixel, &info->line_length, &info->endian);
	info->bytes_per_pixel = info->bits_per_pixel / 8;
	info->scene = malloc(sizeof(t_scene));
	scene_setting(info->scene);
	srand((unsigned int)time(NULL));
}

void	init_color(t_color *color, float r, float g, float b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
