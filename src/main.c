/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/11 17:08:43 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
	#include <stdio.h>

int				main(int argc, char **argv)
{
	t_trm			*trm;
	t_select_list	list;

	g_stdout_dev = open("/dev/ttys001", O_WRONLY);
	if (!(trm = term_init()))
		return (0);
	if (!(list.cols = list_init(argc, argv)))
		return (0);
	list_print(&list);
	ft_trmkeyhook(trm, TRM_KEY_ESC, (void (*)(void *))&ft_trmstop, NULL);
	ft_trmkeyhook(trm, TRM_KEY_BKSP, (void (*)(void *))&item_delete, &list);
	ft_trmkeyhook(trm, " ", (void (*)(void *))&item_select, &list);
	ft_trmkeyhook(trm, TRM_KEY_UP, (void (*)(void *))&cursor_go_prev, &list);
	ft_trmkeyhook(trm, TRM_KEY_DOWN, (void (*)(void *))&cursor_go_next, &list);
	ft_trmkeyhook(trm, TRM_KEY_LEFT, (void (*)(void *))&cursor_go_left, &list);
	ft_trmkeyhook(trm, TRM_KEY_RIGHT, (void (*)(void *))&cursor_go_right, &list);
	ft_trmsignalhook(trm, SIGWINCH, (void (*)(void *))&list_update, &list);
	ft_trmstart(trm);
	return(0);
}
