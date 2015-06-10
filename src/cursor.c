/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 15:49:30 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/10 17:40:50 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		list_last_col(t_lst_col *cols, int y)
{
	int			i;

	i = y;
	while (cols->next && cols->next->height > y)
	{
		i += cols->height;
		cols = cols->next;
	}
	return (i);
}

void			cursor_go_next(t_select_list *list)
{
	if (list->cursor < ft_lstlen((t_lst *)list->cols->items) - 1)
		list->cursor++;
	else
		list->cursor = 0;
	args_print(list);
}

void			cursor_go_prev(t_select_list *list)
{
	if (list->cursor > 0)
		list->cursor--;
	else
		list->cursor = ft_lstlen((t_lst *)list->cols->items) - 1;
	args_print(list);
}

void			cursor_go_left(t_select_list *list)
{
	if (list->cursor > list->cols->height - 1)
		list->cursor -= list->cols->height;
	else
		list->cursor = list_last_col(list->cols, list->cursor.y);
	args_print(list);
}

void			cursor_go_right(t_select_list *list)
{
	if (list->cursor < list_last_col(list->cols, list->cursor.y))
		list->cursor += list->cols->height;
	else
		list->cursor = list->cursor % list->cols->height;
	args_print(list);
}
