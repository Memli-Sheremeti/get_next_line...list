/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:57:54 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/10 12:05:39 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/* 3. */ // clean all data before and save data after the '\n'
void	ft_clean_used(t_list **lst)
{
	t_list	*last_node;
	t_list	*clean_node;
	char	*buf;
	size_t	i;
	size_t	j;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	clean_node = malloc(sizeof(t_list));
	if (!clean_node || !buf)
		return ;
	last_node = ft_lstlast(*lst);
	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	while (last_node->content[i] && last_node->content[++i])
		buf[j++] = last_node->content[i];
	buf[j] = '\0';
	clean_node->content = buf;
	clean_node->next = NULL;
	ft_free_lst(lst, clean_node, buf);
}

/* 2. */ // Creat the line too '\n'
char	*ft_creat_line(t_list *lst)
{
	char	*line;
	size_t	len;

	if (!lst)
		return (NULL);
	len = ft_len_line(lst);
	line = malloc((len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	ft_lst_copy(lst, line);
	return (line);
}

/* 1. */ //join the buf to the content of the list
void	ft_subjoin(t_list **lst, char *buf)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	last_node = ft_lstlast(*lst);
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buf;
	new_node->next = NULL;
}

// loop looking always the nb_bytes_read if not '\n' in some content
void	ft_creat_list(t_list **lst, int fd)
{
	char	*buf;
	ssize_t	nb_bytes_read;

	if (!lst)
		return ;
	while (!ft_found_new_line(*lst))
	{
		buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buf)
			return ;
		nb_bytes_read = read(fd, buf, BUFFER_SIZE);
		if (!nb_bytes_read)
		{
			free(buf);
			return ;
		}
		buf[nb_bytes_read] = '\0';
		ft_subjoin(lst, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	ft_creat_list(&list, fd);
	if (list == NULL)
		return (NULL);
	line = ft_creat_line(list);
	ft_clean_used(&list);
	return (line);
}

/*#include <stdio.h>

int	main()
{
	char	*str;
	int	fd;
	
	fd = open("text", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	free(str);
}
*/
