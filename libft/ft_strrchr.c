/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 17:25:48 by lbaron            #+#    #+#             */
/*   Updated: 2022/11/29 17:25:50 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	index;

	index = (int) ft_strlen(str);
	while (index >= 0)
	{
		if (str[index] == (unsigned char) c)
		{
			return ((char *)str + index);
		}
		index--;
	}
	return (NULL);
}
