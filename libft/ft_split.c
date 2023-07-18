/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:03:49 by lbaron            #+#    #+#             */
/*   Updated: 2022/12/06 12:03:50 by lbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

typedef struct s_data
{
	int		i;
	int		j;
	int		k;
	int		wc;
	char	**out;
}t_data;

static char	*ft_strncpy(char *s1, char *s2, int n)
{
	int	i;

	i = -1;
	while (++i < n && s2[i])
		s1[i] = s2[i];
	s1[i] = '\0';
	return (s1);
}

static int	word_count(char *str, char c)
{
	t_data	v;

	v.i = 0;
	v.wc = 0;
	while (str[v.i])
	{
		while (str[v.i] && str[v.i] == c)
			v.i++;
		if (str[v.i])
			v.wc++;
		while (str[v.i] && str[v.i] != c)
			v.i++;
	}
	return (v.wc);
}

char	**ft_split(char *str, char c)
{
	t_data	v;

	v.j = 0;
	v.k = 0;
	v.wc = word_count(str, c);
	v.out = (char **)malloc(sizeof(char *) * (v.wc + 1));
	v.i = 0;
	while (str[v.i])
	{
		while (str[v.i] && str[v.i] == c)
			v.i++;
		v.j = v.i;
		while (str[v.i] && str[v.i] != c)
			v.i++;
		if (v.i > v.j)
		{
			v.out[v.k] = (char *)malloc(sizeof(char) * ((v.i - v.j) + 1));
			ft_strncpy(v.out[v.k++], &str[v.j], v.i - v.j);
		}
	}
	v.out[v.k] = NULL;
	return (v.out);
}
