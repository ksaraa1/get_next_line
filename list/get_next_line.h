/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:02:34 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/06 14:30:58 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000000
# endif

typedef struct s_gnl_list
{
	int                 fd;
	char                *stash;
	struct s_gnl_list   *next;
}	t_gnl_list;

char	*get_next_line(int fd);
t_gnl_list	*get_node(t_gnl_list **list, int fd);
void	remove_node(t_gnl_list **list, int fd);
char	*read_file(int fd, char *stash);
char	*extract_line(char *stash);
char	*save_remainder(char *stash);
size_t	get_strlen(const char *str);
char	*get_strjoin(char *s1, const char *s2);
char	*get_strdup(const char *s);
char	*find_newline(char *stash);
void	*get_free(char **ptr);


#endif
