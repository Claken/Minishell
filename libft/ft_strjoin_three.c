/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:51:15 by sachouam          #+#    #+#             */
/*   Updated: 2021/11/13 19:55:42 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char
	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*firstjoin;
	char	*secondjoin;

	firstjoin = ft_strjoin(s1, s2);
	if (!firstjoin)
		return (NULL);
	secondjoin = ft_strjoin(firstjoin, s3);
	free_line(&firstjoin);
	if (!secondjoin)
		return (NULL);
	return (secondjoin);
}
