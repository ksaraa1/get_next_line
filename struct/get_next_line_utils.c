/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:53:00 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/08 16:42:45 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_strlen(const char *str)
{
	size_t	length;

	length = 0;
	if (!str)
		return (0);
	while (str[length])
		length++;
	return (length);
}

char	*get_strjoin(t_gnl *gnl, char *buffer)
{
	char	*new_str;
	char	*stash_ptr;
	char	*new_str_ptr;

	if (!gnl->stash || !buffer)
		return (NULL);

	new_str = malloc(get_strlen(gnl->stash) + get_strlen(buffer) + 1);
	if (!new_str)
		return (get_free(&gnl->stash), NULL);
	stash_ptr = gnl->stash;
	new_str_ptr = new_str;
	while (*stash_ptr)
		*new_str_ptr++ = *stash_ptr++;
	while (*buffer)
		*new_str_ptr++ = *buffer++;
	*new_str_ptr = '\0';

	get_free(&gnl->stash);
	return (new_str);
}

char	*get_strdup(const char *str)
{
	const char	*str_ptr;
	char		*copy;
	char		*copy_ptr;

	if (!str)
		return (NULL);
	copy = malloc(get_strlen(str) + 1);
	if (!copy)
		return (NULL);
	str_ptr = str;
	copy_ptr = copy;
	while (*str_ptr)
		*copy_ptr++ = *str_ptr++;
	*copy_ptr = '\0';
	return (copy);
}

int	find_newline(char **str)
{
	char	*str_ptr;

	if (!str || !*str)
		return (0);
	str_ptr = *str;
	while (*str_ptr)
	{
		if (*str_ptr == '\n')
			return (1);
		str_ptr++;
	}
	return (0);
}

void	get_free(char **str)
{
	if (str || *str)
	{
		free(*str);
		*str = NULL;
	}
}
