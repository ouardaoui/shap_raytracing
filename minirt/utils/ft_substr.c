/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:13:53 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/17 02:57:15 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	char			*str;

	i = -1;
	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		return (ft_calloc(1, 1));
	}
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	while (++i < len)
		str[i] = s[start + i];
	str[i] = '\0';
	return (str);
}
