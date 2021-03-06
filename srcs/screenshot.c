/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 21:01:51 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/24 04:12:43 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		int_in_char(unsigned char *str, int value)
{
	int i;

	i = -1;
	while (++i < 4)
		str[i] = (unsigned char)(value >> (i * 8));
}

int			write_header(int fd, unsigned int fd_size, t_data *data)
{
	unsigned char	header[54];
	int				i;

	i = -1;
	while (++i < 54)
		header[i] = (unsigned char)(0);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	int_in_char(header + 2, fd_size);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	int_in_char(header + 18, data->parse.width);
	int_in_char(header + 22, -data->parse.height);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(24);
	return (write(fd, header, 54));
}

int			write_screen(t_data *data, int fd, unsigned int pad_byte_row)
{
	const unsigned char	zeroes[3] = {0, 0, 0};
	int					y;
	int					x;

	y = -1;
	while (++y < data->parse.height)
	{
		x = -1;
		while (++x < data->parse.width)
			if (write(fd, &data->img.buffer[y * data->parse.width + x], 3) < 0)
				return (0);
		if (write(fd, &zeroes, pad_byte_row) < 0)
			return (0);
	}
	return (1);
}

void		screenshot(t_data *data)
{
	int				fd;
	unsigned int	fd_size;
	unsigned int	pxl_byte_row;
	unsigned int	pad_byte_row;

	pxl_byte_row = data->parse.width * 3;
	pad_byte_row = (4 - (pxl_byte_row % 4)) % 4;
	fd_size = 54 + (pxl_byte_row + pad_byte_row) * data->parse.height;
	if ((fd = open("./screenshot/screenshot.bmp", O_WRONLY | O_CREAT
		| O_TRUNC, S_IRUSR |
		S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		write(2, "error\n", 6);
	if (write_header(fd, fd_size, data) < 0)
		write(2, "error\n", 6);
	if (!write_screen(data, fd, pad_byte_row))
		write(2, "error\n", 6);
	close(fd);
}

void		check_save(t_data *data, char *str)
{
	int	i;

	i = 0;
	if (str)
		if (str[i] == '-')
			if (str[i + 1] == 's')
				if (str[i + 2] == 'a')
					if (str[i + 3] == 'v')
						if (str[i + 4] == 'e')
							if (str[i + 5] == '\0')
								data->check_screen = 1;
}
