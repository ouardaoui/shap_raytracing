/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 15:40:07 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/17 02:56:22 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/minirt.h"

void	*ft_memset(void *b, int c, size_t len)
{
	char	*p;

	p = (char *)b;
	while (len)
		p[len-- - 1] = (unsigned char)c;
	return (b);
}
