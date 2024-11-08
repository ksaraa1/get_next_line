/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:28:21 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/08 17:04:18 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

// # ifndef buffer_size
// #  define buffer_size 10000
// # endif

typedef struct s_gnl
{
	char			*stash;
	int				fd;
	int				buffer_size;
}				t_gnl;

char	*get_next_line(int fd);
char	*read_file(t_gnl *gnl);
char	*get_strdup(const char *str);
char	*get_strjoin(t_gnl *gnl, char *buffer);
int		find_newline(char **stash);
void	get_free(char **str);
size_t	get_strlen(const char *str);
char	*save_remainder(char **stash);
char	*extract_line(char **stash);
int		allocate_stash(t_gnl *gnl, int read_bytes);


#endif
