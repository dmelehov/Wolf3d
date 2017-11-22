/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 10:08:09 by dmelehov          #+#    #+#             */
/*   Updated: 2017/10/27 13:17:02 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static	int		get_char_map_len(char s)
{
	int		i;
	int		fd;

	i = 0;
	fd = open("./map", O_RDONLY);
	while (read(fd, &s, 1))
	{
		if (s == ' ' || s == '\t')
			continue ;
		else if (ft_isdigit(s) || s == '\n')
			i++;
		else
			error_manager(1);
	}
	return (i);
}

static	void	get_char_map(t_data *data)
{
	char	*str;
	int		fd;
	char	s;
	int		i;

	i = 0;
	s = '\0';
	fd = open("./map", O_RDONLY);
	str = ft_strnew(get_char_map_len(s));
	while (read(fd, &s, 1))
	{
		if (s == ' ' || s == '\t')
			continue ;
		else if (ft_isdigit(s) || s == '\n')
			str[i++] = s;
		else
			error_manager(1);
	}
	CMAP = ft_strsplit(str, '\n');
	ft_strdel(&str);
}

static	void	get_int_map(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	get_char_map(data);
	while ((CMAP)[i])
		i++;
	if (!(MAP = (int **)malloc(sizeof(int *) * (i + 1))))
		error_manager(2);
	(MAP)[i] = NULL;
	i = 0;
	while ((CMAP)[i])
	{
		j = ft_strlen((CMAP)[i]);
		if (!((MAP)[i] = (int *)malloc(sizeof(int) * (j + 1))))
			error_manager(2);
		(MAP)[j] = NULL;
		j = 0;
		while ((CMAP)[j])
		{
			(MAP)[i][j] = (CMAP)[i][j] - 48;
			j++;
		}
		i++;
	}
}

void			init_struct(t_data *data)
{
	CAM->posx = 22;
	CAM->posy = 12;
	CAM->dirx = -1;
	CAM->diry = 0;
	CAM->plx = 0;
	CAM->ply = 0.66;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, LENGHT, HEIGHT, "Wolf3d");
	get_int_map(data);
}
