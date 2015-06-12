/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/12 20:14:17 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int				main(int argc, char **argv)
{
	t_trm			*trm;
	t_select_list	list;

	if (!(trm = term_init()))
		return (0);
	if (!(list_init(&list, argc, argv)))
		return (0);
	trm->on_start = ft_evntnew((void (*)(void *))&list_print, &list);
	trm->on_restore = ft_evntnew((void (*)(void *))&list_update, &list);
	ft_trmkeyhook(trm, TRM_KEY_ESC, (void (*)(void *))&ft_trmstop, NULL);
	ft_trmkeyhook(trm, TRM_KEY_BKSP, (void (*)(void *))&item_delete, &list);
	ft_trmkeyhook(trm, TRM_KEY_DEL, (void (*)(void *))&item_delete, &list);
	ft_trmkeyhook(trm, " ", (void (*)(void *))&item_select, &list);
	ft_trmkeyhook(trm, TRM_KEY_ENTER, (void (*)(void *))&list_submit, &list);
	ft_trmkeyhook(trm, TRM_KEY_UP, (void (*)(void *))&cursor_go_prev, &list);
	ft_trmkeyhook(trm, TRM_KEY_DOWN, (void (*)(void *))&cursor_go_next, &list);
	ft_trmkeyhook(trm, TRM_KEY_LEFT, (void (*)(void *))&cursor_go_left, &list);
	ft_trmkeyhook(trm, TRM_KEY_RIGHT, (void (*)(void *))&cursor_go_right,
		&list);
	ft_trmsignalhook(trm, SIGWINCH, (void (*)(void *))&list_update, &list);
	ft_trmsignalhook(trm, SIGINT, (void (*)(void *))&ft_trmstop, NULL);
	ft_trmstart(trm);
	return (0);
}
