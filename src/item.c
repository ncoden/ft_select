/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   item.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/11 16:38:36 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 16:50:33 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			item_delete(t_select_list *list)
{
	int			i;
	t_lst_item	*prev;
	t_lst_item	*next;

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
		next = prev->next->next;
		free(prev->next);
		prev->next = next;
		if (!next)
			list->cursor--;
	}
	list_update(list);
}

void			item_select(t_select_list *list)
{
	t_lst_item	*item;

	item = (t_lst_item *)ft_lstget((t_lst *)list->cols->items, list->cursor);
	if (item->selected)
		item->selected = FALSE;
	else
		item->selected = TRUE;
	list_print(list);
}
