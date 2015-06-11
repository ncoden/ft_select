/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 16:38:36 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 18:07:54 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			item_delete(t_select_list *list)
{
	int			i;
	t_lst_item	*prev;

	i = list->cursor;
	if (i == 0)
		ft_lstdelone((t_lst **)&list->cols->items, NULL);
	else
	{
		prev = list->cols->items;
		while (i > 1)
		{
			prev = prev->next;
			i--;
		}
		ft_lstdelone((t_lst **)&prev->next, NULL);
		if (!prev->next)
			list->cursor--;
	}
	if (list->cols->items)
		list_update(list);
	else
		list_submit(list);
}

void			item_select(t_select_list *list)
{
	t_lst_item	*item;

	item = (t_lst_item *)ft_lstget((t_lst *)list->cols->items, list->cursor);
	if (item->selected)
		item->selected = FALSE;
	else
		item->selected = TRUE;
	cursor_go_next(list);
}
