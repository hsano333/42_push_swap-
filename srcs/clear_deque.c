/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_deque.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 11:47:10 by hsano             #+#    #+#             */
/*   Updated: 2022/09/22 02:18:58 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "stdio.h"

int	delete(t_deque *node, void *content)
{
	t_deque	*nil_node;
	t_deque	*tmp_node;

	nil_node = search_nil(node);
	tmp_node = nil_node;
	while (tmp_node->next != nil_node)
	{
		if (tmp_node->content == content)
		{
			((t_deque *)tmp_node->prev)->next = tmp_node->next;
			((t_deque *)tmp_node->next)->prev = tmp_node->prev;
			free(tmp_node->content);
			free(tmp_node);
			return (true);
		}
		tmp_node = tmp_node->next;
	}
	return (false);
}

void	clear_deque(t_deque *node)
{
	t_deque	*nil_node;
	t_deque	*tmp_node;
	t_deque	*next_node;

	if (node == NULL)
		return ;
	nil_node = search_nil(node);
	next_node = nil_node->next;
	while (next_node != nil_node)
	{
		tmp_node = next_node;
		next_node = next_node->next;
		free(tmp_node->content);
		free(tmp_node);
	}
	free(nil_node);
}
