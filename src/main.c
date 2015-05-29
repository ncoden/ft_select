/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/05/30 00:12:29 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
	#include <stdio.h>

static void		trm_start(t_mt_tps *tps)
{
	ft_putstr("\nNew terminal (");
	ft_putullonghex((unsigned long long)tps);
	ft_putstr(") > ");
}

int				main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_trm		*trm;
	t_trm		*trm2;

	trm = ft_trmnew();
	trm->opts.c_lflag &= ~(ICANON);
	trm->opts.c_lflag &= ~(ECHO);
	trm->opts.c_cc[VMIN] = 1;
	trm->opts.c_cc[VTIME] = 0;
	trm2 = ft_trmnew();
	trm2->opts.c_lflag &= ~(ICANON);
	trm2->opts.c_lflag &= ~(ECHO);
	trm2->opts.c_cc[VMIN] = 1;
	trm2->opts.c_cc[VTIME] = 0;

	trm->on_start = &trm_start;
	ft_trmkeyhook(trm, "c", (void (*)(void *))&ft_putstr_trm, "PRESS1");
	ft_trmkeyhook(trm, "n", (void (*)(void *))&ft_trmstart, trm2);
	ft_trmsignalhook(trm, SIGWINCH, (void (*)(void *))&ft_trmstop, NULL);
	ft_trmkeyhook(trm, "s", (void (*)(void *))&ft_trmstop, NULL);

	trm2->on_start = &trm_start;
	ft_trmkeyhook(trm2, "c", (void (*)(void *))&ft_putstr_trm, "PRESS2");
	ft_trmkeyhook(trm2, "n", (void (*)(void *))&ft_trmstart, trm);
	ft_trmsignalhook(trm2, SIGWINCH, (void (*)(void *))&ft_putstr_trm, "RESIZE2");
	ft_trmkeyhook(trm2, "s", (void (*)(void *))&ft_trmstop, NULL);

	ft_putstr("[ lanched ]");
	ft_trmstart(trm);
	ft_trmcloseout();
	return(0);
}
