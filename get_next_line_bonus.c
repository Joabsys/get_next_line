/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesequie <jesequie@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-24 12:44:41 by jesequie          #+#    #+#             */
/*   Updated: 2026-06-24 12:44:41 by jesequie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*extract_line(char *stash)
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

static int	fill_stash(int fd, char **stash)
{
	char	*chunk;
	int		r;

	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (-1);
	r = 1;
	while (r > 0 && !(*stash && (*stash)[find_char(*stash, '\n')] == '\n'))
	{
		r = read(fd, chunk, BUFFER_SIZE);
		if (r > 0)
		{
			chunk[r] = '\0';
			*stash = add_chunk(*stash, chunk);
		}
	}
	free(chunk);
	return (r);
}

static char	*update_stash(char *s)
{
	unsigned int	i;
	unsigned int	len;
	char			*new;

	i = find_char(s, '\n');
	if (s[i] == '\n')
		i++;
	len = 0;
	while (s[i + len])
		len++;
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	len = 0;
	while (s[i])
	{
		new[len] = s[i];
		len++;
		i++;
	}
	new[len] = '\0';
	free(s);
	return (new);
}

char	*get_next_line(int fd)
{
	static char		*stash[FD_SIZE_MAX];	
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1 || fd >= FD_SIZE_MAX)
		return (NULL);
	if ((fill_stash(fd, &stash[fd])) < 0)
		return (NULL);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	if (!line)
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
