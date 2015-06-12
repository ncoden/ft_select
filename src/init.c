/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:51:56 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/12 19:45:24 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_trm				*term_init(void)
{
	t_trm		*trm;

	if (!(trm = ft_trmnew()))
		return (FALSE);
	trm->opts.c_lflag &= ~(ICANON);
	trm->opts.c_lflag &= ~(ECHO);
	trm->opts.c_cc[VMIN] = 1;
	trm->opts.c_cc[VTIME] = 0;
	return (trm);
}

t_bool				list_init(t_select_list *list, int argc, char **argv)
{
	t_lst_item	*item;

	list->items = NULL;
	while (argc > 1)
	{
		argc--;
		if (!(item = (t_lst_item *)ft_lstpushfront__(sizeof(t_lst_item),
			(t_lst **)&list->items)))
		{
			ft_lstdel((t_lst **)&list->items, (void (*)(void *, size_t))&free);
			return (FALSE);
		}
		item->name = argv[argc];
		item->selected = 0;
	}
	list->cols = list_calc_cols(list->items, NULL);
	return (TRUE);
}

static t_lst_item	*calc_col(t_lst_col *col, t_lst_item *items, int height)
{
	int			i;
	int			width;
	int			width_max;

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
	return (items);
}

t_lst_col			*list_calc_cols(t_lst_item *items, t_lst_col *cols)
{
	t_lst_col	*col;
	int			height;

	if ((height = ft_trmheight() - 1) <= 0)
	{
		ft_lstdel((t_lst **)&cols, NULL);
		return (NULL);
	}
	col = cols;
	while (items)
	{
		if (!col && (!(col = (t_lst_col *)ft_lstpushback__(sizeof(t_lst_col),
				(t_lst **)&cols))))
			return (NULL);
		items = calc_col(col, items, height);
		if (!items && col->next)
		{
			ft_lstdel((t_lst **)&col->next, NULL);
			col->next = NULL;
		}
		col = col->next;
	}
	return (cols);
}
