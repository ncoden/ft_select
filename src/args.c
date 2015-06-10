/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:58:07 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/10 16:38:14 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_lst_col		*args_init(int argc, char **argv)
{
	t_lst_item	*item;
	t_lst_item	*items;

	items = NULL;
	while (argc > 1)
	{
		argc--;
		if (!(item = (t_lst_item *)ft_lstpushfront__(sizeof(t_lst_item),
			(t_lst **)&items)))
		{
			ft_lstdel((t_lst **)&items, (void (*)(void *, size_t))&free);
			return (NULL);
		}
		item->name = argv[argc];
		item->selected = 0;
	}
	return (args_calc_cols(items, NULL));
}

t_lst_col		*args_calc_cols(t_lst_item *items, t_lst_col *cols)
{
	t_lst_col	*col;
	int			i;
	int			height;
	int			width;
	int			width_max;

	col = cols;
	height = ft_trmheight() - 1;
	while (items)
	{
		if (!col && (!(col = (t_lst_col *)ft_lstpushback__(sizeof(t_lst_col),
				(t_lst **)&cols))))
			return (NULL);
		i = 0;
		width_max = 0;
		col->items = items;
		while (items && i < height)
		{
			if ((width = ft_strlen(items->name)) > width_max)
				width_max = width;
			items = items->next;
			i++;
		}
		col->height = i;
		col->width = width_max + 1;
		if (!items && col->next)
		{
			ft_lstdel((t_lst **)&col->next, NULL);
			col->next = NULL;
		}
		col = col->next;
	}
	return (cols);
}

void			args_print(t_select_list *list)
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
		while (args_print_line(list, i))
			i++;
	}
	else
		ft_putstr("Window is too small to display the select list");
}

t_bool			args_print_line(t_select_list *list, int index)
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

void			args_resize(t_select_list *list)
{
	list->cols = args_calc_cols(list->cols->items, list->cols);
	args_print(list);
}
