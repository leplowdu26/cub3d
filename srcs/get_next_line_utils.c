/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaefourn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:36:56 by gaefourn          #+#    #+#             */
/*   Updated: 2020/01/22 05:35:23 by gaefourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		len_s1;
	int		len_s2;
	int		i;

	len_s1 = 0;
	while (*(s1 + len_s1))
		++len_s1;
	len_s2 = 0;
	while (*(s2 + len_s2))
		++len_s2;
	if (!(tmp = malloc((len_s1 + len_s2 + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (++i < len_s1)
		tmp[i] = s1[i];
	i = -1;
	while (++i < len_s2)
		tmp[len_s1 + i] = s2[i];
	tmp[len_s1 + len_s2] = '\0';
	return (tmp);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*tmp;
	unsigned int	size;

	size = 0;
	while (*(s + size))
		++size;
	if (start > size)
	{
		if (!(tmp = malloc(sizeof(*tmp))))
			return (0);
		*tmp = '\0';
		return (tmp);
	}
	if (!s || !(tmp = malloc(sizeof(*tmp) * (len + 1))))
		return (0);
	*(tmp + len) = 0;
	while (len--)
		*(tmp + len) = *(s + start + len);
	return (tmp);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*tmp;

	i = 0;
	while (*(s1 + i))
		++i;
	if (!(tmp = malloc(sizeof(*tmp) * (i + 1))))
		return (NULL);
	i = -1;
	while (*(s1 + ++i))
		*(tmp + i) = *(s1 + i);
	*(tmp + i) = '\0';
	return (tmp);
}
