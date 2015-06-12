/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/10 15:49:30 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 16:21:04 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		distance_to_last_column(t_lst_col *col, int index)
{
	int			i;

	i = 0;
	while (col->next && col->next->height > index)
	{
		i += col->height;
		col = col->next;
	}
	return (i);
}

void			cursor_go_next(t_select_list *list)
{
	if (list->cursor < ft_lstlen((t_lst *)list->items) - 1)
		list->cursor++;
	else
		list->cursor = 0;
	list_print(list);
}

void			cursor_go_prev(t_select_list *list)
{
	if (list->cursor > 0)
		list->cursor--;
	else
		list->cursor = ft_lstlen((t_lst *)list->items) - 1;
	list_print(list);
}

void			cursor_go_left(t_select_list *list)
{
	if (list->cursor > list->cols->height - 1)
		list->cursor -= list->cols->height;
	else
		list->cursor += distance_to_last_column(list->cols, list->cursor);
	list_print(list);
}

void			cursor_go_right(t_select_list *list)
{
	list->cursor += list->cols->height;
	if (list->cursor >= ft_lstlen((t_lst *)list->items))
		list->cursor %= list->cols->height;
	list_print(list);
}
