/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcosta-d <gcosta-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:04:10 by gcosta-d          #+#    #+#             */
/*   Updated: 2022/01/18 22:04:34 by gcosta-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes_bonus/pipex_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	string_len;
	size_t	i;
	char	*substr;

	if (s == NULL)
		return (NULL);
	string_len = ft_strlen(s);
	if (start > string_len)
		return (ft_strdup(""));
	if (start + len > string_len)
		len = string_len - start;
	substr = malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
