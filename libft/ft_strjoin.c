/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:03:15 by lbaron            #+#    #+#             */
/*   Updated: 2022/12/06 12:03:16 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	buf_len;

	ret = 0;
	if (s1 && s2)
	{
		buf_len = ft_strlen(s1) + ft_strlen(s2) + 1;
		ret = malloc(buf_len);
		if (!ret)
			return (ret);
		ret[0] = 0;
		ft_strlcpy(ret, s1, buf_len);
		ft_strlcat(ret, s2, buf_len);
	}
	return (ret);
}
