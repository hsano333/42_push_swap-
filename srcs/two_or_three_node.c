/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   two_or_three_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsano <hsano@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 02:57:45 by hsano             #+#    #+#             */
/*   Updated: 2022/09/24 23:59:40 by hsano            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "two_or_three_node.h"
#include "libft_str.h"
#include "push_swap_util.h"
#include "deque_util.h"

static int	check_difference_id(t_deque *node)
{
	t_deque	*nil_node;
	size_t	i;
	size_t	id[5];	

	i = 0;
	while (i < 4)
		id[i++] = 0;
	nil_node = search_nil(node);
	node = nil_node->next;
	i = 0;
	while (node->content != NULL)
	{
		id[i] = node->content->id;
		node = node->next;
		if (i >= 4)
			break ;
		i++;
	}
	if ((id[3] != id[2]) || (id[2] != id[1]))
		return (true);
	return (false);
}

int	is_two_or_three_node(t_abtable *table)
{
	t_deque	*a_node;
	t_deque	*b_node;
	size_t	a_id;
	size_t	b_id;
	size_t	cnt;

	a_node = search_nil(table->a)->next;
	b_node = search_nil(table->b)->next;
	a_id = 0;
	b_id = 0;
	cnt = 0;
	//if (a_node->content != NULL)
		//a_id = a_node->content->id;
	//if (b_node->content != NULL)
		//b_id = b_node->content->id;
	//while ((a_node->content != NULL) && (a_node->content->id == a_id) && ++cnt)
		//a_node = a_node->next;
	cnt = count_node(a_node, 0);
	if ((2 <= cnt && cnt <= 3) || check_difference_id(a_node))
		return (true);
	//if (can_sort(ab_table, A_TABLE))
		//return (false);

	//cnt = 0;
	//while ((b_node->content != NULL) && (b_node->content->id == b_id) && ++cnt)
		//b_node = b_node->next;
	cnt = count_node(b_node, 0);
	if (can_sort(table, A_TABLE) == false &&  (cnt == 2 || check_difference_id(b_node)))
		return (true);
	return (false);
}

static void	loop_execute_inst(t_abtable *table, char **split_c, char **split_i, char target)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (split_i[i])
	{
		if (split_c[c] && !ft_strncmp(split_i[i], split_c[c], ft_strlen(split_c[c])))
		{
			execute_str_both_instruction_wrapper(table, split_i[i]);
			c++;
		}
		else
			execute_str_instruction_wrapper(table, split_i[i], target);
		i++;
	}
}

#include <stdio.h>
void	execute_inst(t_abtable *table, char *common, char *independence, char target)
{
	char	**split_c;
	char	**split_i;

	//printf("execute_inst No.1 \n");
	//printf("common=%p\n", common);
	//printf("independence=%s\n", independence);
	//printf("execute_inst No.2 \n");
	//
	split_c = ft_split(common, ' ');
	split_i = ft_split(independence, ' ');

	if (!split_c || !split_i)
	{
		ft_free_split(split_c);
		ft_free_split(split_i);
		kill_process(table);
	}
	loop_execute_inst(table, split_c, split_i, target);
	ft_free_split(split_c);
	ft_free_split(split_i);
}

void	two_or_three_node(t_abtable *table)
{
	int		len_a;
	int		len_b;
	char	*inst_a;
	char	*inst_b;
	//char	*common;

	//ft_printf("test No.1\n");
	inst_a = two_or_three_node_a(table);
	inst_b = two_or_three_node_b(table);
	//printf("test No.2 inst_a=%s, inst_b=%s\n", inst_a, inst_b);
	len_a = (int)ft_strlen(inst_a);
	len_b = (int)ft_strlen(inst_b);
	//printf("test No.3 inst_a=%d, inst_b=%d\n", len_a, len_b);
	//common = get_common_instruction(inst_a, inst_b, len_a, len_b);
	//printf("test No.4 common=%s\n", common);
	//if (common == NULL)
		//return ;
	//printf("test No.5 common=%s\n", common);
	if (len_a > len_b)
		execute_inst(table, inst_b, inst_a, A_TABLE);
	else
		execute_inst(table, inst_a, inst_b, B_TABLE);

}
