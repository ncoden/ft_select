/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:58:07 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 17:04:41 by ncoden           ###   ########.fr       */
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
			if (item->selected && count + index == list->cursor)
				ft_putstr("\033[4;7m");
			else if (item->selected)
				ft_putstr("\033[7m");
			else if (count + index == list->cursor)
				ft_putstr("\033[4m");
			ft_putstr(item->name);
			if (count + index == list->cursor || item->selected)
				ft_putstr("\033[0m");
			if (col->next)
				ft_putspace(col->width - ft_strlen(item->name));
		}
		count += col->height;
		col = col->next;
	}
	if (found)
		ft_putchr('\n');
	return (found);
}

void			list_update(t_select_list *list)
{
	list->cols = list_calc_cols(list->cols->items, list->cols);
	list_print(list);
}
