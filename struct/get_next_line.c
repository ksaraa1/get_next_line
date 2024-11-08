/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:27:52 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/08 17:04:13 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl	gnl;
	char			*line;

	if (fd < 0 || gnl.buffer_size <= 0)
		return (NULL);
	gnl.stash = read_file(&gnl);
	if (!gnl.stash)
	{
		if (gnl.stash)
			return (get_free(&gnl.stash), NULL);
		return (NULL);
	}
	if (!find_newline(&gnl.stash))
	{
		line = get_strdup(gnl.stash);
		get_free(&gnl.stash);
		return (line);
	}
	line = extract_line(&gnl.stash);
	gnl.stash = save_remainder(&gnl.stash);
	return (line);
}

char	*read_file(t_gnl *gnl)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(gnl->buffer_size + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0)
	{
		read_bytes = read(gnl->fd, buffer, gnl->buffer_size);
		if (read_bytes < 0 || (read_bytes == 0 && !gnl->stash))
		{
			get_free(&buffer);
			get_free(&gnl->stash);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		if (!gnl->stash && read_bytes > 0 && !allocate_stash(gnl, read_bytes))
			return (get_free(&buffer), NULL);
		gnl->stash = get_strjoin(gnl, buffer);
		if (find_newline(&gnl->stash))
			break ;
	}
	get_free(&buffer);
	return (gnl->stash);
}

int	allocate_stash(t_gnl *gnl, int read_bytes)
{
	gnl->stash = malloc(read_bytes + 1);
	if (!gnl->stash)
		return (0);
	gnl->stash[0] = '\0';
	return (1);
}


char	*extract_line(char **stash)
{
	char	*line;
	char	*line_ptr;
	int		line_length;

	line_length = 0;
	while ((*stash)[line_length] && (*stash)[line_length] != '\n')
		line_length++;
	line = malloc(line_length + 2);
	if (!line)
		return (NULL);

	line_ptr = line;
	while (**stash && **stash != '\n')
		*line_ptr++ = *(*stash)++;
	if (**stash == '\n')
		*line_ptr++ = *(*stash)++;
	*line_ptr = '\0';

	return (line);
}

char	*save_remainder(char **stash)
{
	char	*remainder;
	char	*newline_pos;

	newline_pos = *stash;
	while (*newline_pos && *newline_pos != '\n')
		newline_pos++;
	if (!*newline_pos)
		return (NULL);

	remainder = get_strdup(newline_pos + 1);
	get_free(stash);
	return (remainder);
}

// #include <stdio.h>
// #include <fcntl.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("fichier.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		perror("Erreur lors de l'ouverture du fichier");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		if (line)
// 		{
// 			printf("%s", line);
// 			free(line);
// 		}
// 	}
// 	if (line == NULL)
// 	{
// 		printf("Fin du fichier ou erreur de lecture.\n");
// 	}

// 	close(fd);
// 	return (0);
// }