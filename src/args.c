/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:58:07 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/09 20:26:56 by ncoden           ###   ########.fr       */
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
			ft_lstdel((t_lst **)&col->next, (void (*)(void *, size_t))&free);
			col->next = NULL;
		}
		col = col->next;
	}
	return (cols);
}

void			args_print(t_lst_col *args)
{
	int			i;
	int			width_term;

	ft_trmclr();
	width_term = ft_trmwidth();
	i = 0;
	while (args_print_line(args, i, width_term))
		i++;
}

t_bool			args_print_line(t_lst_col *args, int index, int width_term)
{
	t_lst_item	*item;
	int			found;
	int			width_line;

	found = FALSE;
	width_line = 0;
	while (args)
	{
		if (index < args->height
			&& (item = (t_lst_item *)ft_lstget((t_lst *)args->items, index)))
		{
			ft_putchr_fd('A', g_stdout_dev);
			dprintf(g_stdout_dev, "%p\n", item->name);
			ft_putchr_fd('B', g_stdout_dev);
			found = TRUE;
			ft_putstrleft(item->name, args->width);
		}
		width_line += args->width;
		args = args->next;
	}
	if (found)
	{
		ft_putnchr('\0', width_term - width_line);
		ft_putchr('\n');
	}
	return (found);
}

void			args_resize(t_lst_col *args)
{
	args = args_calc_cols(args->items, args);
	args_print(args);
}
