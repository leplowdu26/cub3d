/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:13:24 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 00:36:27 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			*crt_img(t_data *data)
{
	int	x;

	x = -1;
	while (++x < data->parse.width)
	{
		raycasting(data, x);
		crt_column(data, x);
	}
	return (data->img.buffer);
}

static	void	norme(t_img *dst, int width, int height)
{
	dst->height = height;
	dst->width = width;
}

t_img			resize_image(t_data *data, t_img *src, int width, int height)
{
	t_img	dst;
	double	size_x;
	double	size_y;
	int		x;
	int		y;

	size_x = (src->width / (double)width);
	size_y = (src->height / (double)height);
	dst.ptr = mlx_new_image(data->mlx.ptr, width, height);
	src->buffer = (int*)mlx_get_data_addr(src->ptr, &src->bpp, &src->size,
			&src->endian);
	dst.buffer = (int*)mlx_get_data_addr(dst.ptr, &(dst.bpp), &(dst.size),
			&(dst.endian));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			dst.buffer[x + (y * dst.size / 4)] =
src->buffer[(int)(((int)(x * size_x) + ((int)(y * size_y) * (src->size / 4))))];
		}
	}
	norme(&dst, width, height);
	return (dst);
}
