/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:04:45 by lbaron            #+#    #+#             */
/*   Updated: 2022/12/06 12:04:46 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	int		i;

	ret = 0;
	if (s)
	{
		i = 0;
		ret = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!ret)
			return (ret);
		while (s[i])
		{
			ret[i] = f(i, s[i]);
			++i;
		}
		ret[i] = 0;
	}
	return (ret);
}
