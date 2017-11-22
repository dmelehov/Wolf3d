/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/21 16:38:39 by dmelehov          #+#    #+#             */
/*   Updated: 2017/10/27 13:18:42 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	void	free_array(t_data *data, char s)
{
	int i;

	i = 0;
	if (s == 'd')
	{
		while ((MAP)[i])
			ft_memdel(((void *)(MAP)[i++]));
		free(MAP);
		MAP = NULL;
	}
	else if (s == 'c')
	{
		while (CMAP[i])
			ft_strdel(&(CMAP[i++]));
		free(CMAP);
		CMAP = NULL;
	}
}

int				ft_color(t_data *data, int i)
{
	int		color;

	if (data->side)
	{
		if (RAY->stepy < 0)
			color = PINK;
		else
			color = GREEN;
	}
	else
	{
		if (RAY->stepx < 0)
			color = YELLOW;
		else
			color = BLUE;
	}
	if (i < RAY->start)
		color = CYAN;
	else if (i > RAY->end)
		color = BROWN;
	else if (CURPOS == 2)
		color /= 2;
	return (color);
}

void			error_manager(int error_num)
{
	if (error_num == 1)
		write(1, "error: invalid map\n", 27);
	else if (error_num == 2)
		write(1, "error: malloc failed\n", 21);
	exit(-1);
}

int				mouse_exit(t_data *data)
{
	data->hit = 0;
	exit(0);
}

int				main(void)
{
	t_data	*data;

	if (!(data = (t_data *)malloc(sizeof(t_data))))
		error_manager(2);
	if (!(CAM = (t_cam *)malloc(sizeof(t_cam))))
		error_manager(2);
	if (!(RAY = (t_ray *)malloc(sizeof(t_ray))))
		error_manager(2);
	init_struct(data);
	mlx_hook(data->win, 17, 1, mouse_exit, data);
	mlx_hook(data->win, 2, (1L << 0), ft_my_keys, data);
	mlx_loop_hook(data->mlx, ft_draw_image, data);
	mlx_loop(data->mlx);
	free_array(data, 'd');
	free_array(data, 'c');
	return (0);
}
