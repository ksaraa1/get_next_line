/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:16:24 by skabouss          #+#    #+#             */
/*   Updated: 2024/10/31 16:03:12 by skabouss         ###   ########.fr       */
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

	copy = malloc(sizeof(char) * get_strlen(*str) + 1);
	if (!copy)
		return (get_free(str));
	str_ptr = *str;
	copy_ptr = copy;
	while (*str_ptr)
		*copy_ptr++ = *str_ptr++;
	*copy_ptr = '\0';
	get_free(str);
	return (copy);
}

char	*get_strjoin(char **dest, char *src)
{
	char	*dest_ptr;
	char	*new_str;
	char	*new_str_ptr;

	if (!dest || !src)
		return (NULL);
	new_str = malloc(get_strlen(*dest) + get_strlen(src) + 1);
	if (!new_str)
		return (get_free(dest));
	new_str_ptr = new_str;
	dest_ptr = *dest;
	while (*dest_ptr)
		*new_str_ptr++ = *dest_ptr++;
	while (*src)
		*new_str_ptr++ = *src++;
	*new_str_ptr = '\0';
	get_free(dest);
	return (new_str);
}

char	*find_newline(char **str)
{
	char	*str_ptr;

	if (!*str)
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
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
