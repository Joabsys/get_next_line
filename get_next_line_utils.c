/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesequie <jesequie@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-15 20:03:38 by jesequie          #+#    #+#             */
/*   Updated: 2026-06-15 20:03:38 by jesequie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

unsigned int	find_char(char *s, char c)
{
	unsigned int	n;

	n = 0;
	while (s[n])
	{
		if (s[n] == c)
			return (n);
		n++;
	}
	return (n);
}

int	ft_strlen(char *s)
{
	int	n;

	n = 0;
	if (!s)
		return (0);
	while (s[n])
		n++;
	return (n);
}

char	*add_chunk(char *stash, char *chunk)
{
	char	*new_stash;
	int		i;
	int		j;

	new_stash = malloc(ft_strlen(stash) + ft_strlen(chunk) + 1);
	if (!new_stash)
		return (NULL);
	i = 0;
	while (stash && stash[i])
	{
		new_stash[i] = stash[i];
		i++;
	}
	j = 0;
	while (chunk[j])
		new_stash[i++] = chunk[j++];
	new_stash[i] = '\0';
	free(stash);
	return (new_stash);
}
