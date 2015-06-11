/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:51:56 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 16:20:10 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_trm			*term_init(void)
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

t_lst_col		*list_init(int argc, char **argv)
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
	return (list_calc_cols(items, NULL));
}

t_lst_col		*list_calc_cols(t_lst_item *items, t_lst_col *cols)
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
