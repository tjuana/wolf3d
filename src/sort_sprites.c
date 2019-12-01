
#include "wolf3d.h"

void			ft_swap_double(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void			ft_swap_int_here(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void			ft_sort_combo(t_wolf3d *w)
{
	t_sort_util s;

	s.count = w->map.s_count;
	s.swap = 0;
	while (s.count > 1 || s.swap)
	{
		s.count = (s.count * 10) / 13;
		if (s.count == 9 || s.count == 10)
			s.count = 11;
		s.count < 1 ? s.count = 1 : 0;
		s.swap = 0;
		s.i = -1;
		s.j = 0;
		while (++s.i < w->map.s_count - s.count)
		{
			s.j = s.i + s.count;
			if (w->map.s_dst[s.i] < w->map.s_dst[s.j])
			{
				ft_swap_double(&w->map.s_dst[s.i], &w->map.s_dst[s.j]);
				ft_swap_int_here(&w->map.s_ord[s.i],
				&w->map.s_ord[s.j]);
				s.swap = 1;
			}
		}
	}
}
