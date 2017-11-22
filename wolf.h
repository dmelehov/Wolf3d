/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmelehov <dmelehov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 13:37:35 by dmelehov          #+#    #+#             */
/*   Updated: 2017/10/27 13:26:15 by dmelehov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "mlx.h"
# include "libft/includes/libft.h"
# include <math.h>
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define SPACE 49
# define ESC 53
# define GREEN 0x41d441
# define BROWN 0x905000
# define GRAY 0x191919
# define YELLOW 0xfa9f1c
# define BLUE 0x003366
# define CYAN 0x29c2fd
# define RED 0xfd0c1f
# define PINK 0xd402b6
# define CAM data->cam
# define RAY data->ray
# define MAP data->map
# define CMAP data->cmap
# define CURPOS data->map[data->mapy][data->mapx]
# define DX (int)(CAM->posx + CAM->dirx)
# define DY (int)(CAM->posy + CAM->diry)
# define LENGHT 800
# define HEIGHT 600
# define MOVESPEED 0.85

typedef struct	s_ray
{
	double		diffx;
	double		diffy;
	double		distx;
	double		disty;
	double		dirx;
	double		diry;
	double		posx;
	double		posy;
	int			stepx;
	int			stepy;
	int			start;
	int			end;
	int			len;
}				t_ray;

typedef struct	s_cam
{
	double		relx;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		plx;
	double		ply;
	double		dist;
	double		move;
	double		rot;
}				t_cam;

typedef struct	s_data
{
	t_cam		*cam;
	t_ray		*ray;
	void		*mlx;
	void		*win;
	void		*img;
	char		*img_addr;
	char		**cmap;
	int			**map;
	int			bpp;
	int			size;
	int			endian;
	int			mapx;
	int			mapy;
	int			side;
	int			hit;
}				t_data;

void			init_struct(t_data *data);
int				ft_draw_image(t_data *data);
int				ft_my_keys(int key, t_data *data);
void			ft_update_data(t_data *data);
void			ft_calc_ray(t_data *data, int i);
void			ft_draw_to_image(t_data *data, int i);
void			ft_get_ray(t_data *data, int n);
void			ft_get_diff(t_data *data);
int				ft_color(t_data *data, int n);
void			error_manager(int error_num);

#endif
