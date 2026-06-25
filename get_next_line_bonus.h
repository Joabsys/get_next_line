/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jesequie <jesequie@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-24 12:44:26 by jesequie          #+#    #+#             */
/*   Updated: 2026-06-24 12:44:26 by jesequie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef FD_SIZE_MAX
#  define FD_SIZE_MAX 1024
# endif

unsigned int	find_char(char *s, char c);
char			*get_next_line(int fd);
char			*add_chunk(char *stash, char *chunk);

#endif
