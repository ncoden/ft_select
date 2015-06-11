/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:58:07 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 16:20:15 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			list_print(t_select_list *list)
{
	int			i;
	int			width;
	t_lst_col	*col;

	ft_trmclr();
	width = ft_trmwidth();
	col = list->cols;
	while (col)
	{
		width -= col->width;
		col = col->next;
	}
	if (width > 0)
	{
		i = 0;
		while (list_print_line(list, i))
			i++;
	}
	else
		ft_putstr("Window is too small to display the select list");
}

t_bool			list_print_line(t_select_list *list, int index)
{
	int			count;
	int			found;
	t_lst_item	*item;
	t_lst_col	*col;

	found = FALSE;
	count = 0;
	col = list->cols;
	while (col)
	{
		if (index < col->height
			&& (item = (t_lst_item *)ft_lstget((t_lst *)col->items, index)))
		{
			found = TRUE;
			if (count + index == list->cursor)
				ft_putchr('O');
			ft_putstrleft(item->name, col->width);
		}
		count += col->height;
		col = col->next;
	}
	if (found)
		ft_putchr('\n');
	return (found);
}

void			list_resize(t_select_list *list)
{
	list->cols = list_calc_cols(list->cols->items, list->cols);
	list_print(list);
}
