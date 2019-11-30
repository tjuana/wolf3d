/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dorange- <dorange-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 13:27:18 by tjuana            #+#    #+#             */
/*   Updated: 2019/11/29 14:59:53 by dorange-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		threading(t_wolf3d *w)
{
	int			x;
	int			xx;
	pthread_t	threads[THREADS];
	t_threads	args[THREADS];

	x = -1;
	xx = 0;
	while (++x < THREADS)
	{
		args[x].t1 = xx;
		args[x].t2 = xx + ((WIN_WIDTH / THREADS));
		ft_init_multi_wolf(&args[x].w, w);
		pthread_create(&threads[x], NULL, begin_game, (void*)&args[x]);
		xx += (WIN_WIDTH / THREADS);
	}
	x = -1;
	while (++x < THREADS)
		pthread_join(threads[x], NULL);
	w->pl.pos.x = args[x - 1].w.pl.pos.x;
	w->pl.pos.y = args[x - 1].w.pl.pos.y;
	w->pl.plane.x = args[x - 1].w.pl.plane.x;
	w->pl.plane.y = args[x - 1].w.pl.plane.y;
	w->pl.dir.x = args[x - 1].w.pl.dir.x;
	w->pl.dir.y = args[x - 1].w.pl.dir.y;
	//ft_draw_sprites(w);
}

// new function for drawing

// Проверяем, лежит ли точка на отрезке (?!)
int			ft_check_point_in_line(t_coord p, t_coord p1, t_coord p2)
{
	double	d;
	int		p_d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if ((p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x))
	{
		p_d = abs((int)(d * 100));
		//printf("p.x%.6f\tp.y%.6f\tp1.x%.6f\tp1.y%.6f\tp2.x%.6f\tp2.y%.6f\t\n", p.x, p.y, p1.x, p1.y, p2.x, p2.y);
		//printf("%i\t%.10f\n", p_d, d);
		if (p_d < 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
//	double a = p2.y - p1.y;
//	double b = p1.x - p2.x;
//	double c = - a * p1.x - b * p1.y;
//	if (abs(a * t.x + b * t.y + c) > eps) return false;

//	return point_in_box (t, p1, p2);
}

// Рассчитываем, куда направить луч
void		ft_new_ray_dir(t_threads *a)
{
	t_list	*ptr_list;
	t_line	*ptr_line;
	t_line	*own_line;
	double	l;
	double	temp_l;
	double	p_y;
	double	p_x;
	double	p_d;
	t_coord	p;

	//double	old_fc_dir_x;
	//double	old_fc_dir_y;

	ptr_list = a->w.line; // Кошмарищеее!
	own_line = NULL;

	// Отклонение для определения угла? Допустим...
	a->w.pl.cameraX = a->t1 * a->w.camera_x_cnst - 1;
	l = 0;

	// Вместо dir должен быть некий коэффициент -- fc_dir (направление и отклонение) [туда, куда пустим луч]
	// Угол смещения -- половина fov, помноженная на отклонение

	// cos(α+β)=cosα⋅cosβ−sinα⋅sinβ
	a->w.fc_dir.x = a->w.pl.dir.x * cos(a->w.pl.cameraX * (a->w.fov / 2)) - a->w.pl.dir.y * sin(a->w.pl.cameraX * (a->w.fov / 2));
	// sin(α±β)=sinα⋅cosβ±cosα⋅sinβ 
	a->w.fc_dir.y = a->w.pl.dir.y * cos(a->w.pl.cameraX * (a->w.fov / 2)) + a->w.pl.dir.x * sin(a->w.pl.cameraX * (a->w.fov / 2));

	// Необходимо связать это с FOV.
	while (ptr_list)
	{
		ptr_line = (t_line*)ptr_list->content;

		//printf("@\tcameraX:\t%f\tdir_x:\t%f\tdir_y:\t%f\n", a->w.pl.cameraX, a->w.fc_dir.x, a->w.fc_dir.y);

		p_d = ((a->w.pl.pos.x) - (a->w.pl.pos.x + a->w.fc_dir.x)) *
				((ptr_line->p1.y) - (ptr_line->p2.y)) -
				((a->w.pl.pos.y) - (a->w.pl.pos.y + a->w.fc_dir.y)) *
				((ptr_line->p1.x) - (ptr_line->p2.x));

		// Если прямые параллельны или совпадают
		if (p_d == 0.0)
		{
			ptr_list = ptr_list->next;
			continue;
		}

		// Упростить формулы
		p_y =	((a->w.pl.pos.x) * (a->w.pl.pos.y + a->w.fc_dir.y) - (a->w.pl.pos.y) * (a->w.pl.pos.x + a->w.fc_dir.x)) *
				((ptr_line->p1.y) - (ptr_line->p2.y)) -
				((a->w.pl.pos.y) - (a->w.pl.pos.y + a->w.fc_dir.y)) *
				((ptr_line->p1.x) * (ptr_line->p2.y) - (ptr_line->p1.y) * (ptr_line->p2.x));

		//printf("@%f\t", p_y);

		p_y /= p_d;
		
		//if ((p_y >= 0 && a->w.pl.dir.y >= 0) || (p_y <= 0 && a->w.pl.dir.y <= 0))
		//{
		p_x =	((a->w.pl.pos.x) * (a->w.pl.pos.y + a->w.fc_dir.y) - (a->w.pl.pos.y) * (a->w.pl.pos.x + a->w.fc_dir.x)) *
				((ptr_line->p1.x) - (ptr_line->p2.x)) -
				((a->w.pl.pos.x) - (a->w.pl.pos.x + a->w.fc_dir.x)) *
				((ptr_line->p1.x) * (ptr_line->p2.y) - (ptr_line->p1.y) * (ptr_line->p2.x));


			//printf("@%f\t", p_x);

		p_x /= p_d;

			// Важно проверить, лежит ли точка пересечения на стене (!!!)

		p.x = p_x;
		p.y = p_y;
		
		if (ft_check_point_in_line(p, ptr_line->p1, ptr_line->p2))
		{
			ptr_list = ptr_list->next;
			continue;
		}
		//else
		//{
		//}


		// Проверка на то, находится ли точка в секторе (неудачная попытка)

		// 1. Находим радиус-вектор, определяющий нахождение точки
		// Смещаем координаты
		a->w.ln_dir.x = p_x - a->w.pl.pos.x;
		a->w.ln_dir.y = p_y - a->w.pl.pos.y;
		// Рассчитываем модуль вектора
		a->w.ln_l = sqrt(pow((a->w.ln_dir.x), 2) + pow((a->w.ln_dir.y), 2));
		// Устанавливаем единичный вектор
		a->w.ln_dir.x /= a->w.ln_l;
		a->w.ln_dir.y /= a->w.ln_l;
		// 2. Проверка угла // a->w.fov
		// Проверка по cos

		// cos(α-β)=cosα⋅cosβ+sinα⋅sinβ
		if (fabs(acos(a->w.pl.dir.x * a->w.ln_dir.x + a->w.pl.dir.y * a->w.ln_dir.y)) > (a->w.fov / 2))
		{
			ptr_list = ptr_list->next;
			continue;
		}

		// sin(α-β)=sinα⋅cosβ-cosα⋅sinβ 
		if (fabs(asin(a->w.pl.dir.y * a->w.ln_dir.x - a->w.pl.dir.x * a->w.ln_dir.y)) > (a->w.fov / 2))
		{
			ptr_list = ptr_list->next;
			continue;
		}

		// Проверка явно не удалась

		// Ааа, вот в чём дело...
		//temp_l = sqrt(pow((p_x - a->w.pl.pos.x), 2) + pow((p_y - a->w.pl.pos.y), 2));
		// Некорректно: нахожу не то! (де-факто: расстояние до начала координат)
		//temp_l = sqrt(pow((p_x - a->w.pl.pos.x), 2) + pow((p_y - a->w.pl.pos.y), 2));


		// Наше расстояние:
		//temp_l = sqrt(pow((p_x - a->w.pl.pos.x), 2) + pow((p_y - a->w.pl.pos.y), 2));

		//temp_l = sqrt(pow((p_x - a->w.pl.pos.x), 2) + pow((p_y - a->w.pl.pos.y), 2));
		temp_l = sqrt(pow((p_x - a->w.pl.pos.x), 2) + pow((p_y - a->w.pl.pos.y), 2));

		// Определяем


		//printf("p_x:%f\tp_y:%f\tl_:%f\n", p_x, p_y, temp_l);
		//printf("p_x%f\tp_y%f\tp_d%f\n", p_x, p_y, p_d);
		//sleep(1);

		if (temp_l < l || l == 0)
		{
			l = temp_l;
			own_line = ptr_line;

			if (a->w.pl.cameraX == 0.0)
				printf("%f\t%f\t%f\t%f\tp1.x%f\tp1.y%f\tp2.x%f\tp2.y%f\n", a->w.pl.pos.x, a->w.pl.pos.y, p_x, p_y, ptr_line->p1.x, ptr_line->p1.y, ptr_line->p2.x, ptr_line->p2.y);
			//printf("@%f\t", temp_l);
			//a->w.texture_num = ptr_l
		}
		//}

		// Выводим информацию:
		//printf("@\tcameraX:\t%f\tl_:\t%f\tp_x:\t%f\tp_y:\t%f\n", a->w.pl.cameraX, temp_l, p_x, p_y);
		//sleep(1);
		//printf("p_x:%f\tp_y:%f\tl_:%f\n", p_x, p_y, temp_l);

		// Переход к следующей линии
		ptr_list = ptr_list->next;
	}

	// Расстояние до стены (почему бы и нет?!)
	// printf("@\tl_%.10f\n", temp_l);



	// Длина пути до нашей стены
	//a->w.l = l * (a->w.pl.cameraX + 1);// * atan2(a->w.pl.cameraX, a->w.l_p);
	a->w.l = l;// * atan2(a->w.pl.cameraX, a->w.l_p);

	// cos(α-β)=cosα⋅cosβ+sinα⋅sinβ
	// α -- a->w.fc_dir
	// β -- a->w.pl.dir

	// Исправляем эффект рыбьего глаза
	a->w.l *= (a->w.fc_dir.x * a->w.pl.dir.x + a->w.fc_dir.y * a->w.pl.dir.y);
	

	//printf("%.100f\n", a->w.l);

	//if (own_line != NULL)
	//	printf("%f\n", a->w.l_p);

	// Увеличение/уменьшение -- проблема a->w.l_p
	if (a->w.l != 0 && own_line != NULL)
		a->w.line_height = own_line->height * a->w.l_p / (a->w.l * (1080 * 20/* * 100 / 2*/)); // 1080 -- квадратный параметр (?!?!?!?!)
	else
		a->w.line_height = 0;
	if (own_line != NULL)
		a->w.texture_num = own_line->txtr; // -1
	else
		a->w.texture_num = 0;


	// no (!), нужно рассчитать угол относительно стены
	//a->w.line_height *= a->w.pl.dir.y;

	//printf("@\ttxtr:\t%d\tLINE:\t%f\tH:\t%f\tp1x_%f\tp1y_%f\tp2x_%f\tp2y_%f\n", own_line->txtr, a->w.l, own_line->height, own_line->p1.x, own_line->p1.y, own_line->p2.x, own_line->p2.y);

	//printf("@\tcX:%f\tang:%f\n", a->w.pl.cameraX, a->w.fc_dir.x);


	// // cos(α-β)=cosα⋅cosβ+sinα⋅sinβ


	//a->w.fc_dir.x = a->w.pl.dir.x * cos(a->w.pl.cameraX * a->w.fov) - a->w.pl.dir.y * sin(a->w.pl.cameraX * a->w.fov);
	// sin(α±β)=sinα⋅cosβ±cosα⋅sinβ 
	//a->w.fc_dir.y = a->w.pl.dir.y * cos(a->w.pl.cameraX * a->w.fov) + a->w.pl.dir.x * sin(a->w.pl.cameraX * a->w.fov);





	// Переменные:
	// x1 = a->w.pl.pos.x;
	// y1 = a->w.pl.pos.y;
	// x2 = a->w.pl.pos.x + a->w.fc_dir.x; // Учтено
	// y2 = a->w.pl.pos.y + a->w.fc_dir.y; // Учтено
	// x3 = ptr_line->p1.x;
	// y3 = ptr_line->p1.y;
	// x4 = ptr_line->p2.x;
	// y4 = ptr_line->p2.y;

	// Знаменатель
	// (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4)

	// Числитель для p_x:
	// (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)

	// Числитель для p_y:
	// (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)

	// p_y = ((x1) * (y2) - (y1) * (x2)) * ((y3) - (y4))-((y1) - (y2)) * ((x3) * (y4) - (y3) * (x4));
	// p_x = ((x1) * (y2) - (y1) * (x2)) * ((y3) - (y4)) - ((y1) - (y2)) * ((x3) * (y4) - (y3) * (x4));
}










void				ft_new_wall_draw_start(t_threads *a)
{
	a->w.draw_start = a->w.half_height - (a->w.line_height >> 1);
	a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
	a->w.draw_end = (a->w.line_height >> 1) + a->w.half_height;
	a->w.draw_end >= WIN_HEIGHT ? a->w.draw_end = WIN_HEIGHT - 1 : 0;
	//a->w.texture_num =\
	//a->w.map.map[a->w.map.x + a->w.map.y * a->w.map.m_wid] - 1;
	if (a->w.pl.side == 0)
		a->w.wall_hit = a->w.pl.pos.y + a->w.pl.wall_dist * a->w.pl.raydir.y;
	else
		a->w.wall_hit = a->w.pl.pos.x + a->w.pl.wall_dist * a->w.pl.raydir.x;
	a->w.wall_hit -= floor(a->w.wall_hit);
	a->w.text_x = (int)(a->w.wall_hit * (double)(TEX_W));
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
	if (a->w.pl.side == 1 && a->w.pl.raydir.y < 0)
		a->w.text_x = TEX_W - a->w.text_x - 1;
}

void				ft_new_draw_walls(t_threads *a)
{
	Uint32	i;
	a->w.y = a->w.draw_start;
	while (a->w.y < a->w.draw_end)
	{
		a->w.temp = (a->w.y << 8) - (WIN_HEIGHT << 7) + (a->w.line_height << 7);
		a->w.text_y = (((a->w.temp * TEX_H) / a->w.line_height) >> 8);
		
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures\
		[a->w.texture_num]->pixels))[TEX_H * 3 * a->w.text_y + a->w.text_x * 3];
		//i = 0xff00ff;
		a->w.color = *(Uint32*)(a->w.tex_col);
		//a->w.color = &i;
		//a->w.color = *(Uint32*)8352370;
		if (a->w.pl.side == 1)
			a->w.color = (a->w.color >> 1) & 8352370;
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = 0xff;//a->w.color;
		a->w.y++;
	}
	a->w.z_buffer[a->t1] = a->w.pl.wall_dist;
}

/*
** 4 different wall directions possible
*/

void	ft_new_get_floor_coordinates(t_threads *a)
{
	if (a->w.pl.side == 0 && a->w.pl.raydir.x > 0)
	{
		a->w.flr.xwall = a->w.map.x;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 0 && a->w.pl.raydir.x < 0)
	{
		a->w.flr.xwall = a->w.map.x + 1.0;
		a->w.flr.ywall = a->w.map.y + a->w.wall_hit;
	}
	else if (a->w.pl.side == 1 && a->w.pl.raydir.y > 0)
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y;
	}
	else
	{
		a->w.flr.xwall = a->w.map.x + a->w.wall_hit;
		a->w.flr.ywall = a->w.map.y + 1.0;
	}
	if (a->w.draw_end < 0)
		a->w.draw_end = WIN_HEIGHT;
}

/*
** draw the floor from draw_end to the bottom of the screen
*/

void	ft_new_draw_floor(t_threads *a)
{
	a->w.y = a->w.draw_end;
	while (a->w.y < WIN_HEIGHT)
	{
		a->w.flr.cur_dst = WIN_HEIGHT / (2.0 * a->w.y - WIN_HEIGHT);
		a->w.flr.weight = a->w.flr.cur_dst / a->w.pl.wall_dist;
		a->w.flr.cur_x = a->w.flr.weight * a->w.flr.xwall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.x;
		a->w.flr.cur_y = a->w.flr.weight * a->w.flr.ywall +
		(1.0 - a->w.flr.weight) * a->w.pl.pos.y;
		a->w.flr.text_x = (int)(a->w.flr.cur_x * TEX_W) % TEX_W;
		a->w.flr.text_y = (int)(a->w.flr.cur_y * TEX_H) % TEX_H;
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures[15]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.color = (a->w.color >> 2) & 8355711;
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = a->w.color;
		a->w.tex_col = &((Uint8*)(a->w.sdl->textures[7]->pixels))[TEX_W * 3 *
		a->w.flr.text_y + a->w.flr.text_x * 3];
		a->w.color = *(Uint32*)(a->w.tex_col);
		a->w.sdl->pixels[a->t1 + ((WIN_HEIGHT - a->w.y) \
		* WIN_WIDTH)] = a->w.color;
		a->w.y++;
	}
}










void		*begin_game(void *w)
{
	t_threads *p;

	p = (t_threads *)w;
	while (p->t1 < p->t2)
	{
		// ft_ray_dir_calculations(p);
		// ft_wall_hit(p);

		// printf("so good\n");


		ft_new_ray_dir(p); // Ведём подсчёты по-новому!
		// printf("so good11\n");

		ft_new_wall_draw_start(p);
		// printf("so good22\n");
		ft_new_draw_walls(p);
		ft_new_get_floor_coordinates(p);
		ft_new_draw_floor(p);
		p->t1++;
	}
	// Максимальный размер стены (или её отсутствие) -- в случае целого x и y
	//printf("@\tx:%f\ty:%f\n", p->w.pl.pos.x, p->w.pl.pos.y);
	return (NULL);
}
