/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:13:17 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/13 13:22:13 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_found_new_line(t_list *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	while (lst)
	{
		i = 0;
		while (lst->content[i] && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lst_copy(t_list *lst, char *line)
{
	size_t	i;
	size_t	j;

	if (!lst)
		return ;
	j = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				line[j++] = '\n';
				line[j] = '\0';
				return ;
			}
			line[j++] = lst->content[i++];
		}
		lst = lst->next;
	}
	line[j] = '\0';
}

size_t	ft_len_line(t_list *lst)
{
	size_t	i;
	size_t	len;

	len = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i] != '\0')
		{
			if (lst->content[i] == '\n')
			{
				len++;
				return (len);
			}
			len++;
			i++;
		}
		lst = lst->next;
	}
	return (len);
}

void	ft_free_lst(t_list **lst, t_list *clean_node, char *buf)
{
	t_list	*temp;

	if (!(*lst))
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	if (clean_node->content[0])
		*lst = clean_node;
	else
	{
		free(buf);
		free(clean_node);
	}
}
