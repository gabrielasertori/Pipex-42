/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:02:42 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 22:03:05 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

void	*ft_calloc(size_t nbr, size_t size)
{
	char	*p;
	char	*pointer;
	size_t	amount;
	size_t	i;

	amount = nbr * size;
	p = (char *) malloc(amount);
	if (!p)
		return (NULL);
	pointer = p;
	i = 0;
	while (i < amount)
	{
		*p = 0;
		i++;
		p++;
	}
	return ((void *) pointer);
}
