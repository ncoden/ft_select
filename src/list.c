/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:58:07 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/12 19:48:19 by ncoden           ###   ########.fr       */
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
			list_print_item(item, (count + index == list->cursor));
			if (col->next)
				ft_putnchr_fd(' ', col->width - ft_strlen(item->name),
					ft_trmgetout());
		}
		count += col->height;
		col = col->next;
	}
	if (found)
		ft_putchr_trm('\n');
	return (found);
}

void			list_print_item(t_lst_item *item, t_bool hover)
{
	if (item->selected && hover)
		ft_putstr_trm("\033[4;7m");
	else if (item->selected)
		ft_putstr_trm("\033[7m");
	else if (hover)
		ft_putstr_trm("\033[4m");
	ft_putstr_trm(item->name);
	if (item->selected || hover)
		ft_putstr_trm("\033[0m");
}

void			list_update(t_select_list *list)
{
	list->cols = list_calc_cols(list->items, list->cols);
	list_print(list);
}

void			list_submit(t_select_list *list)
{
	t_bool		sent;
	t_lst_item	*item;

	sent = FALSE;
	item = list->items;
	while (item)
	{
		if (item->selected)
		{
			if (sent)
				ft_putchr(' ');
			ft_putstr(item->name);
			sent = TRUE;
		}
		item = item->next;
	}
	ft_trmstop(NULL);
}
