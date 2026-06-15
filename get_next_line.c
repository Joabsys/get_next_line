/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesequie <jesequie@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-15 17:48:30 by jesequie          #+#    #+#             */
/*   Updated: 2026-06-15 17:48:30 by jesequie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		stash[BUFFER_SIZE + 1];
	int				r;
	char			*chunk;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	chunk = malloc(BUFFER_SIZE + 1);
	if (!chunk)
		return (NULL);
	while (1)
	{
		if (stash[find_char(stash, '\n')] == '\n')
		{
			line = extract_line (stash);
			update_stash (stash);
			free (chunk);
			return (line);
		}
		r = read (fd, chunk, BUFFER_SIZE);
		if (r < 0)
		{
			free (chunk);
			return (NULL);
		}
		if (r == 0)
			break ;
		chunk[r] = '\0';
		add_chunk (stash, chunk, BUFFER_SIZE);
	}
	free (chunk);
	line = extract_line (stash);
	update_stash (stash);
	return (line);
}
#include<fcntl.h>
#include <stdio.h>
int main(void)
{
	int fd;
	char *line;
	fd = open("texto.txt", O_RDONLY);
	if(fd < 0)
		return(1);
	while((line = get_next_line(fd)))
	{
		printf("%s",line);
		free(line);
	}
	close(fd);
	return(0);
}
