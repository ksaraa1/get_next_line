/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:16:24 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/07 11:49:41 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	get_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*get_strdup(char **str)
{
	char	*str_ptr;
	char	*copy;
	char	*copy_ptr;

	if (!str || !*str)
		return (NULL);
	copy = malloc(get_strlen(*str) + 1);
	if (!copy)
		return (NULL);
	str_ptr = *str;
	copy_ptr = copy;
	while (*str_ptr)
		*copy_ptr++ = *str_ptr++;
	*copy_ptr = '\0';
	get_free(str);
	return (copy);
}

char	*get_strjoin(char **stash, char *buffer)
{
	char	*stash_ptr;
	char	*new_str;
	char	*new_str_ptr;

	if (!stash || !*stash || !buffer)
		return (NULL);
	new_str = malloc(get_strlen(*stash) + get_strlen(buffer) + 1);
	if (!new_str)
		return (get_free(stash));
	new_str_ptr = new_str;
	stash_ptr = *stash;
	while (*stash_ptr)
		*new_str_ptr++ = *stash_ptr++;
	while (*buffer)
		*new_str_ptr++ = *buffer++;
	*new_str_ptr = '\0';
	get_free(stash);
	return (new_str);
}

char	*find_newline(char **str)
{
	char	*str_ptr;

	if (!str || !*str)
		return (NULL);
	str_ptr = *str;
	while (*str_ptr)
	{
		if (*str_ptr == '\n')
			return (str_ptr);
		str_ptr++;
	}
	return (NULL);
}

char	*get_free(char **str)
{
	if (!str || !*str)
		return (NULL);
	while (*str)
	{
		free(*str);
		*str = NULL;
	}
	str = NULL;
	return (NULL);
}
