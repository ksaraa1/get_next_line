/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skabouss <skabouss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:02:13 by skabouss          #+#    #+#             */
/*   Updated: 2024/11/06 14:33:00 by skabouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_gnl_list	*list = NULL;
	t_gnl_list			*node;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	node = get_node(&list, fd);
	if (!node)
		return (NULL);

	node->stash = read_file(fd, node->stash);
	if (!node->stash || !*node->stash)
	{
		remove_node(&list, fd);
		return (NULL);
	}

	line = extract_line(node->stash);
	node->stash = save_remainder(node->stash);
	if (!node->stash)
		remove_node(&list, fd);

	return (line);
}


void	remove_node(t_gnl_list **list, int fd)
{
	t_gnl_list *current = *list;
	t_gnl_list *previous = NULL;

	while (current)
	{
		if (current->fd == fd)
		{
			if (previous)
				previous->next = current->next;
			else
				*list = current->next;
			free(current->stash);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

t_gnl_list	*get_node(t_gnl_list **list, int fd)
{
	t_gnl_list *current = *list;

	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}

	// Création d'un nouveau nœud si fd non trouvé
	t_gnl_list *new_node = malloc(sizeof(t_gnl_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = NULL;
	new_node->next = *list;
	*list = new_node;
	return (new_node);
}
char	*read_file(int fd, char *stash)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_bytes;

	while (1)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		stash = get_strjoin(stash, buffer); // Ajoute buffer au stash
		if (find_newline(stash)) // Si une ligne complète est trouvée
			break ;
	}
	return (stash);
}

char	*extract_line(char *stash)
{
	char	*line;
	int		len = 0;

	// Calculer la longueur de la ligne
	while (stash[len] && stash[len] != '\n')
		len++;
	line = malloc(len + 2); // Inclure '\n' et '\0'
	if (!line)
		return (NULL);
	len = 0;
	while (*stash && *stash != '\n')
		line[len++] = *stash++;
	if (*stash == '\n')
		line[len++] = '\n';
	line[len] = '\0';
	return (line);
}

