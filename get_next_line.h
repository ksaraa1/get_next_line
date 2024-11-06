/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:16:34 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/05 12:03:59 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

char	*get_next_line(int fd);
size_t	get_strlen(const char *str);
char	*get_free(char **str);
char	*find_newline(char **str);
char	*get_strdup(char **str);
char	*get_strjoin(char **dest, char *src);
char	*read_file(int fd, char **stash);
char	*extract_line(char **stash);
char	*save_remainder(char **stash);

#endif
