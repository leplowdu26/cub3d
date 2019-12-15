/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 17:46:11 by gaefourn          #+#    #+#             */
/*   Updated: 2019/12/15 17:49:50 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_textures(t_data *data)
{
	data->ntext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/ntext.xpm",
						&(data->ntext.width), &(data->ntext.height));
	data->stext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/stext.xpm",
						&(data->stext.width), &(data->stext.height));
	data->etext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/etext.xpm",
						&(data->etext.width), &(data->etext.height));
	data->wtext.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/wtext.xpm",
						&(data->wtext.width), &(data->wtext.height));
	data->tmp_ntext = resize_image(data, &data->ntext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->ntext.ptr);
	data->ntext = data->tmp_ntext;
	data->tmp_stext = resize_image(data, &data->stext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->stext.ptr);
	data->stext = data->tmp_stext;
	data->tmp_etext = resize_image(data, &data->etext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->etext.ptr);
	data->etext = data->tmp_etext;
	data->tmp_wtext = resize_image(data, &data->wtext, 750, 750);
	mlx_destroy_image(data->mlx.ptr, data->wtext.ptr);
	data->wtext = data->tmp_wtext;
}

void	load_background(t_data *data)
{
	data->ciel.ptr = mlx_xpm_file_to_image(data->mlx.ptr,
			"./textures/ciel.xpm",
						&(data->ciel.width), &(data->ciel.height));
	data->sol.ptr = mlx_xpm_file_to_image(data->mlx.ptr, "./textures/sol.xpm",
						&(data->sol.width), &(data->sol.height));
	data->tmp_ciel = resize_image(data, &data->ciel, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->ciel.ptr);
	data->ciel = data->tmp_ciel;
	data->tmp_sol = resize_image(data, &data->sol, WIDTH, HEIGHT / 2);
	mlx_destroy_image(data->mlx.ptr, data->sol.ptr);
	data->sol = data->tmp_sol;
}

void	crt_window(t_data *data)
{
	data->mlx.ptr = mlx_init();
	data->mlx.win = mlx_new_window(data->mlx.ptr, WIDTH, HEIGHT, "Cub3d");
	data->img.ptr = mlx_new_image(data->mlx.ptr, WIDTH, HEIGHT);
	data->img.buffer = (int*)mlx_get_data_addr(data->img.ptr, &data->img.bpp,
										&data->img.size, &data->img.endian);
}