/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:16:13 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/08 09:42:26 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, &stash);
	if (!stash || !*stash)
	{
		if (stash)
			return (get_free(&stash));
		return (NULL);
	}
	if (!find_newline(&stash))
	{
		line = get_strdup(&stash);
		get_free(&stash);
		return (line);
	}
	line = extract_line(&stash);
	if (!line)
		return (get_free(&stash));
	stash = save_remainder(&stash);
	return (line);
}

int	allocate_stash(char **stash, int read_bytes)
{
	*stash = malloc(read_bytes + 1);
	if (!*stash)
		return (0);
	**stash = '\0';
	return (1);
}

char	*read_file(int fd, char **stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0 || (read_bytes == 0 && !*stash))
			return (get_free(&buffer), get_free(stash));
		buffer[read_bytes] = '\0';
		if (!*stash && read_bytes > 0 && !allocate_stash(stash, read_bytes))
			return (get_free(&buffer), NULL);
		*stash = get_strjoin(stash, buffer);
		if (find_newline(stash))
			break ;
	}
	get_free(&buffer);
	return (*stash);
}

char	*extract_line(char **stash)
{
	char	*line;
	char	*line_ptr;
	char	*stash_ptr;

	stash_ptr = *stash;
	line_ptr = NULL;
	while (*stash_ptr != '\n' && *stash_ptr)
		stash_ptr++;
	line = malloc((sizeof(char) * (stash_ptr - *stash) + 2));
	if (!line)
		return (get_free(stash));
	stash_ptr = *stash;
	line_ptr = line;
	while (*stash_ptr != '\n' && *stash_ptr)
		*line_ptr++ = *stash_ptr++;
	*line_ptr = '\n';
	*++line_ptr = '\0';
	return (line);
}

char	*save_remainder(char **stash)
{
	char	*remainder;
	char	*newline_ptr;
	char	*remainder_ptr;

	if (!stash || !*stash)
		return (NULL);
	newline_ptr = find_newline(stash);
	if (!newline_ptr)
		return (NULL);
	remainder = malloc((get_strlen(newline_ptr) + 2));
	if (!remainder)
		return (NULL);
	remainder_ptr = remainder;
	newline_ptr++;
	while (*newline_ptr)
		*remainder_ptr++ = *newline_ptr++;
	*remainder_ptr = '\0';
	get_free(stash);
	return (remainder);
}

//  #include <fcntl.h>
//  #include <stdio.h>

//  int	main(void)
//  {
//  	int		fd;
//  	char	*line;

//  	fd = open("fichier.txt", O_RDONLY);
//  	if (fd < 0)
//  	{
//  		perror("Erreur lors de l'ouverture du fichier");
//  		return (1);
//  	}
//  	while ((line = get_next_line(fd)) != NULL)
//  	{
//  		printf("%s", line);
//  		free(line);
//  	}
//  	close(fd);
//  	return (0);
//  }
