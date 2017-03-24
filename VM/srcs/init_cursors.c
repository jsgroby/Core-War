/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewallner <ewallner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/17 14:16:11 by ewallner          #+#    #+#             */
/*   Updated: 2017/03/20 17:08:18 by nsabbah          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_cursor		*ft_create_cursor(int i, t_env *e)
{
	t_cursor	*newcursor;

	newcursor = malloc(sizeof(t_cursor));
	if (newcursor == NULL)
		return (NULL);
	newcursor->counter = 0;
	newcursor->player = i;
	newcursor->id = 0;
	newcursor->carry = 0;
	newcursor->cycle = 0;
	newcursor->color = (i + 1 % 6) + 6;
	newcursor->running = 0;
	newcursor->comnd_len = 5;
	newcursor->index = e->player[i].index_start;
	newcursor->next = NULL;
	return (newcursor);
}


t_cursor		*ft_add_cursor_to_stack(t_env *e, t_cursor *stack, int i)
{
	while (stack && stack->next)
		stack = stack->next;
	stack->next = ft_create_cursor(i, e);
	return (stack);
}

t_cursor		*ft_create_cursor_list(t_env *e)
{
	int		i;
	t_cursor	*stack;
	t_cursor	*head;

	stack = NULL;
	i = 0;
	while(i < e->player_amount)
	{
		if(!stack)
		{
			stack = ft_create_cursor(i, e);
			head = stack;
		}
		else
			stack = ft_add_cursor_to_stack(e, stack, i);
		i++;
	}
	return(head);
}

void init_color_cursor(t_env *e)
{
	t_cursor *cursor;

	cursor = e->head;
	while(!cursor->counter)
	{
		ft_update_cursor(e, cursor, 0);
		cursor = cursor->next;
	}
}

void		ft_init_cursor(t_env *e)
{
	t_cursor	*stack;

	stack = ft_create_cursor_list(e);
	e->head = stack;
	while (stack && stack->next)
		stack = stack->next;
	stack->next = ft_create_cursor(0, e);
	stack = stack->next;
	stack->counter = 1;
	stack->next = e->head;
	init_color_cursor(e);
}