/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   threads.c										  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: dorange- <dorange-@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/10/25 13:27:18 by tjuana			#+#	#+#			 */
/*   Updated: 2019/12/28 21:31:36 by dorange-		 ###   ########.fr	   */
/*																			*/
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

// Проверяем, лежит ли точка на отрезке (?!)
int			ft_check_point_in_line_segment(t_vector3 p, t_vector3 p1, t_vector3 p2)
{
	double	d;
	int		p_d;

	d = (p.x - p1.x) * (p2.y - p1.y) - (p.y - p1.y) * (p2.x - p1.x);
	if (
		(p1.x < p.x && p.x < p2.x) || (p2.x < p.x && p.x < p1.x) ||
		(p1.y < p.y && p.y < p2.y) || (p2.y < p.y && p.y < p1.y)
	)
	{
		p_d = abs((int)(d * 100));
		if (p_d < 1)
			return (1);
		else
			return (0);
	}
	else
		return (0);
	return (0);
}

int			ft_check_point(t_vector3 p, t_vector3 p1, t_vector3 p2, t_vector3 p1_pl, t_vector3 p2_pl)
{
	// Определяем, в верном ли направлении лежит точка
	double l1;
	double l2;

	l1 = sqrt(pow((p.x - p1_pl.x), 2) + pow((p.y - p1_pl.y), 2));
	l2 = sqrt(pow((p.x - p2_pl.x), 2) + pow((p.y - p2_pl.y), 2));

	if (l1 < l2 && l2 - l1 > 0.999999)
		return (0);

	// Определить, лежит ли точка на отрезке
	if (ft_check_point_in_line_segment(p, p1, p2))
		return (1);
	return (0);
}

/*
 * vxs: Vector cross product
 */
double		ft_math_vxs(double x0, double y0, double x1, double y1)
{
	return ((x0)*(y1) - (x1)*(y0));
}

int			ft_check_div(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4)
{
	double		d;

	d = ft_math_vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
	if (d == 0.0)
		return (0);
	return 1;
}

t_vector3		ft_find_intersect(double x1, double y1, double x2, double y2,double x3, double y3, double x4, double y4)
{
	t_vector3		xy;
	double		d;

	d = ft_math_vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4));
	xy.x = ft_math_vxs(ft_math_vxs(x1,y1, x2,y2), (x1)-(x2), ft_math_vxs(x3,y3, x4,y4), (x3)-(x4)) / d;
	xy.y = ft_math_vxs(ft_math_vxs(x1,y1, x2,y2), (y1)-(y2), ft_math_vxs(x3,y3, x4,y4), (y3)-(y4)) / d;
	return (xy);
}

// ray casting (simple math)
void		ft_new_ray_dir(t_threads *a)
{
	t_list	*ptr_list;
	t_line	*ptr_line;
	t_line	*own_line;
	double	l;
	double	temp_l;
	double	p_d;
	t_vector3	p;
	t_vector3	i_vertex;

	t_vector3	p1_pl;
	t_vector3	p2_pl;

	ptr_list = a->w.line; // List of lines
	own_line = NULL;

	/*
	    NDC:
				  1.0
				   |
				   |
		-1.0 -----0.0----- 1.0  (cameraX)
				   |
				   |
				 -1.0
	*/
	a->w.pl.cameraX = a->t1 * a->w.camera_x_cnst - 1;
	l = 0; // Расстояние от стены до игрока

	// Вместо dir должен быть некий коэффициент -- fc_dir (направление и отклонение) [туда, куда пустим луч]
	// Угол смещения -- половина fov, помноженная на отклонение
	// fc_dir -- вектор камеры

	// cos(α+β)=cosα⋅cosβ−sinα⋅sinβ
	a->w.fc_dir.x = a->w.pl.dir.x * cos(a->w.pl.cameraX * (a->w.fov / 2)) - a->w.pl.dir.y * sin(a->w.pl.cameraX * (a->w.fov / 2));
	// sin(α±β)=sinα⋅cosβ±cosα⋅sinβ 
	a->w.fc_dir.y = a->w.pl.dir.y * cos(a->w.pl.cameraX * (a->w.fov / 2)) + a->w.pl.dir.x * sin(a->w.pl.cameraX * (a->w.fov / 2));

	// Необходимо связать это с FOV.
	while (ptr_list)
	{
		ptr_line = (t_line*)ptr_list->content;

		// Проверка, что делитель не 0
		if (!ft_check_div(
			a->w.pl.pos.x,
			a->w.pl.pos.y,
			(a->w.pl.pos.x + a->w.fc_dir.x),
			(a->w.pl.pos.y + a->w.fc_dir.y), 
			ptr_line->p1.x,
			ptr_line->p1.y,
			ptr_line->p2.x,
			ptr_line->p2.y
		))
		{
			ptr_list = ptr_list->next;
			continue;
		}

		p = ft_find_intersect(
			a->w.pl.pos.x,
			a->w.pl.pos.y,
			(a->w.pl.pos.x + a->w.fc_dir.x),
			(a->w.pl.pos.y + a->w.fc_dir.y), 
			ptr_line->p1.x,
			ptr_line->p1.y,
			ptr_line->p2.x,
			ptr_line->p2.y
		);

		// Вектор 
		p1_pl.x = a->w.pl.pos.x;
		p1_pl.y = a->w.pl.pos.y;
		p2_pl.x = (a->w.pl.pos.x + a->w.fc_dir.x);
		p2_pl.y = (a->w.pl.pos.y + a->w.fc_dir.y);

		if (!ft_check_point(p, ptr_line->p1, ptr_line->p2, p1_pl, p2_pl))
		{
			ptr_list = ptr_list->next;
			continue;
		}
		
		// Расстояние от точки пересечения до позиции игрока
		temp_l = sqrt(pow((p.x - a->w.pl.pos.x), 2) + pow((p.y - a->w.pl.pos.y), 2));

		if (temp_l < l || l == 0)
		{
			l = temp_l;
			own_line = ptr_line;
		}

		// Переход к следующей линии
		ptr_list = ptr_list->next;
	}

	// Длина пути до нашей стены
	//a->w.l = l * (a->w.pl.cameraX + 1);// * atan2(a->w.pl.cameraX, a->w.l_p);
	a->w.l = l; // * atan2(a->w.pl.cameraX, a->w.l_p);

	// Убираем эффект рыбьего глаза
	a->w.l *= (a->w.fc_dir.x * a->w.pl.dir.x + a->w.fc_dir.y * a->w.pl.dir.y);

	// cos(α-β)=cosα⋅cosβ+sinα⋅sinβ
	// α -- a->w.fc_dir
	// β -- a->w.pl.dir


	// Увеличение/уменьшение -- проблема a->w.l_p
	if (a->w.l != 0 && own_line != NULL)
		a->w.line_height = own_line->height * a->w.l_p / (a->w.l * (WIN_HEIGHT));
	else
	{
		a->w.line_height = 0;
	}

	if (own_line != NULL)
		a->w.texture_num = own_line->txtr; // -1
	else
		a->w.texture_num = 0;

	// printf("%f\t%d\t%f\t%f\n", a->w.l, a->w.line_height, own_line->height, a->w.l_p);

	// Переменные:
	// x1 = a->w.pl.pos.x;
	// y1 = a->w.pl.pos.y;
	// x2 = a->w.pl.pos.x + a->w.fc_dir.x; // Учтено
	// y2 = a->w.pl.pos.y + a->w.fc_dir.y; // Учтено
	// x3 = ptr_line->p1.x;
	// y3 = ptr_line->p1.y;
	// x4 = ptr_line->p2.x;
	// y4 = ptr_line->p2.y;
}

void				ft_new_wall_draw_start(t_threads *a)
{
	a->w.draw_end = (int)(a->w.pl.cameraH * WIN_HEIGHT) * a->w.l_p / (a->w.l * (WIN_HEIGHT)) + WIN_HEIGHT * a->w.pl.camera_tilt;
	a->w.draw_start = a->w.draw_end - a->w.line_height;
	a->w.draw_end >= WIN_HEIGHT ? a->w.draw_end = WIN_HEIGHT - 1 : 0;
	a->w.draw_start < 0 ? a->w.draw_start = 0 : 0;
}

void				ft_new_draw_walls(t_threads *a)
{
	Uint32	i;
	a->w.y = a->w.draw_start;
	while (a->w.y < a->w.draw_end)
	{
		a->w.sdl->pixels[a->t1 + (a->w.y * WIN_WIDTH)] = 0x120a8f;
		a->w.y++;
	}
	a->w.z_buffer[a->t1] = a->w.pl.wall_dist;
}

void		*begin_game(void *w)
{
	t_threads *p;

	p = (t_threads *)w;
	while (p->t1 < p->t2)
	{
		ft_new_ray_dir(p); // Пускаем луч, рассчитываем высоту стены
		ft_new_wall_draw_start(p); // Рассчитываем стартовые координаты стены
		ft_new_draw_walls(p); // Отрисовываем стену
		p->t1++;
	}
	return (NULL);
}
