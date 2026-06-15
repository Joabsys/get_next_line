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

void	zero_stash(char *s)
{
	unsigned int	n;

	n = 0;
	while (n < BUFFER_SIZE)
		*(s + n++) = '\0';
}

char	*extract_line(char *stash)
{
	unsigned int	i;
	unsigned int	n;
	char			*line;

	i = find_char(stash, '\n');
	if (stash[i] == '\0' && i == 0)
		return (NULL);
	if (stash[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	n = 0;
	while (n < i)
	{
		line[n] = stash[n];
		n++;
	}
	if (stash[i] == '\n')
		line[n++] = '\n';
	line[n] = '\0';
	return (line);
}

void	add_chunk(char *stash, char *chunk, int size)
{
	int	i;
	int	j;

	i = 0;
	while (stash[i])
		i++;
	j = 0;
	while (chunk[j] && i < size - 1)
	{
		stash[i] = chunk[j];
		i++;
		j++;
	}
	stash[i] = '\0';
}

void	update_stash(char *s)
{
	unsigned int	i;
	unsigned int	n;

	i = find_char(s, '\n');
	if (s[i] == '\n')
		i++;
	n = 0;
	while (s[i])
	{
		s[n] = s[i];
		n++;
		i++;
	}
	while (n < BUFFER_SIZE)
	{
		s[n] = '\0';
		n++;
	}
}
