/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:03:32 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/06 14:32:44 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*save_remainder(char *stash)
{
	char	*newline_ptr = find_newline(stash);
	char	*new_stash;

	if (!newline_ptr)
		return (get_free(&stash));
	newline_ptr++;
	new_stash = get_strdup(newline_ptr);
	get_free(&stash);
	return (new_stash);
}

char	*find_newline(char *stash)
{
	if (!stash)
		return (NULL);
	while (*stash)
	{
		if (*stash == '\n')
			return (stash);
		stash++;
	}
	return (NULL);
}

size_t	get_strlen(const char *str)
{
	size_t len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*get_strjoin(char *s1, const char *s2)
{
	size_t	len1 = s1 ? get_strlen(s1) : 0;
	size_t	len2 = get_strlen(s2);
	char	*result = malloc(len1 + len2 + 1);
	size_t	i = 0;

	if (!result)
		return (NULL);
	while (s1 && s1[i])
	{
		result[i] = s1[i];
		i++;
	}
	for (size_t j = 0; j < len2; j++)
		result[i++] = s2[j];
	result[i] = '\0';
	free(s1);
	return (result);
}

char	*get_strdup(const char *s)
{
	size_t	len = get_strlen(s);
	char	*dup = malloc(len + 1);
	size_t	i = 0;

	if (!dup)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	*get_free(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}
