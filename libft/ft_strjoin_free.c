/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earruaba <earruaba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 22:46:54 by earruaba          #+#    #+#             */
/*   Updated: 2021/11/11 22:47:23 by earruaba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s, char *buff)
{
	char	*join;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s)
		return (ft_strdup(buff));
	if (!buff)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(buff) + ft_strlen(s)) + 1);
	if (!join)
		return (0);
	while (s[++i])
		join[i] = s[i];
	free_line(&s);
	while (buff[++j])
		join[i + j] = buff[j];
	join[i + j] = '\0';
	return (join);
}
