/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 21:07:22 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 00:36:13 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_objs(t_data *data, int x)
{
	if (data->map[data->ray.mapx][data->ray.mapy] == '1' ||
			data->map[data->ray.mapx][data->ray.mapy] == '3')
		data->ray.hit = 1;
	wall_dist(data);
	data->zbuffer[x] = data->ray.walldist;
	if (data->map[data->ray.mapx][data->ray.mapy] == '2' ||
		data->map[data->ray.mapx][data->ray.mapy] == '4' ||
		data->map[data->ray.mapx][data->ray.mapy] == '5' ||
		data->map[data->ray.mapx][data->ray.mapy] == '6')
		create_obj(data, &data->obj, x,
		data->map[data->ray.mapx][data->ray.mapy]);
}

void	raycasting(t_data *data, int x)
{
	raycast_value(data, x);
	while (data->ray.hit == 0)
	{
		if (data->ray.sidedistx < data->ray.sidedisty)
		{
			data->ray.sidedistx += data->ray.deltax;
			data->ray.mapx += data->ray.stepx;
			data->ray.side = 0;
		}
		else
		{
			data->ray.sidedisty += data->ray.deltay;
			data->ray.mapy += data->ray.stepy;
			data->ray.side = 1;
		}
		if (data->map[data->ray.mapx][data->ray.mapy] > '0')
			check_objs(data, x);
	}
}

void	raycast_value(t_data *data, int x)
{
	init_ray(data, x);
	if (data->ray.dirx < 0)
	{
		data->ray.stepx = -1;
		data->ray.sidedistx = (
				data->perso.pos.x - data->ray.mapx) * data->ray.deltax;
	}
	else
	{
		data->ray.stepx = 1;
		data->ray.sidedistx = (
				data->ray.mapx + 1.0 - data->perso.pos.x) * data->ray.deltax;
	}
	if (data->ray.diry < 0)
	{
		data->ray.stepy = -1;
		data->ray.sidedisty = (
				data->perso.pos.y - data->ray.mapy) * data->ray.deltay;
	}
	else
	{
		data->ray.stepy = 1;
		data->ray.sidedisty = (
				data->ray.mapy + 1.0 - data->perso.pos.y) * data->ray.deltay;
	}
}

void	wall_dist(t_data *data)
{
	if (data->ray.side == 0)
		data->ray.walldist = ft_abs(((int)data->ray.mapx - data->perso.pos.x +
					(1 - data->ray.stepx) / 2) / data->ray.dirx);
	else
		data->ray.walldist = ft_abs(((int)data->ray.mapy - data->perso.pos.y + (
						1 - data->ray.stepy) / 2) / data->ray.diry);
	data->ray.heightline = data->parse.height / data->ray.walldist;
	data->ray.start = (int)(-(data->ray.heightline / 2) +
			data->parse.height / 2);
	data->ray.end = (int)((data->ray.heightline / 2) + data->parse.height / 2);
	data->ray.truestart = (int)(-(data->ray.heightline / 2) +
			data->parse.height / 2);
	data->ray.trueend = (int)((data->ray.heightline / 2) +
			data->parse.height / 2);
	if (data->ray.start < 0)
		data->ray.start = 0;
	if (data->ray.end >= data->parse.height)
		data->ray.end = data->parse.height - 1;
}
