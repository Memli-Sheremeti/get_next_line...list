/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:25:47 by mshereme          #+#    #+#             */
/*   Updated: 2023/11/10 11:10:40 by mshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}				t_list;
/* utility */
int		ft_found_new_line(t_list *lst);
size_t	ft_len_line(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_free_lst(t_list **lst, t_list *clean_node, char *buf);
void	ft_lst_copy(t_list *lst, char *line);
/* 3. */
void	ft_clean_usded(t_list **lst);
/* 2. */
char	*ft_creat_line(t_list *lst);
/*1.*/
void	ft_creat_list(t_list **lst, int fd);
void	ft_subjoin(t_list **lst, char *buf);
char	*get_next_line(int fd);

#endif
