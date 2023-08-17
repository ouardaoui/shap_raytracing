/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 17:56:38 by hahadiou          #+#    #+#             */
/*   Updated: 2023/08/17 02:56:14 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*b;

	b = (char *)malloc(size * count);
	if (!b)
		return (NULL);
	ft_bzero(b, size * count);
	return (b);
}
