/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsugimot <fsugimot@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 22:57:14 by fsugimot          #+#    #+#             */
/*   Updated: 2020/07/14 22:57:29 by fsugimot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_strlen(const char *dst)
{
	int	ret;

	ret = 0;
	if (dst)
		while (*dst++)
			ret++;
	return (ret);
}

void	ft_memcpy(void *dst, void *src, size_t size)
{
	unsigned char	*dst_p;
	unsigned char	*src_p;

	dst_p = dst;
	src_p = src;
	while (size--)
	{
		*dst_p = *src_p;
		dst_p++;
		src_p++;
	}
}
