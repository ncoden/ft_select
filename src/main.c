/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/05/18 01:35:52 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
	#include <stdio.h>
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
	ft_trmkeyhook(trm, "c", (void (*)(void *))&ft_putstr, "PRESS1");
	ft_trmkeycmd(trm, "e", "cl");
	ft_trmkeyhook(trm, "n", (void (*)(void *))&ft_trmloop, trm2);
	ft_trmsignalhook(trm, SIGWINCH, (void (*)(void *))&ft_putstr, "RESIZE1");
	ft_trmkeyhook(trm, "s", (void (*)(void *))&ft_trmstop, trm);

	ft_trmkeyhook(trm2, "c", (void (*)(void *))&ft_putstr, "PRESS2");
	ft_trmkeycmd(trm2, "e", "cl");
	ft_trmkeyhook(trm2, "n", (void (*)(void *))&ft_trmloop, trm);
	ft_trmsignalhook(trm2, SIGWINCH, (void (*)(void *))&ft_putstr, "RESIZE2");
	ft_trmkeyhook(trm2, "s", (void (*)(void *))&ft_trmstop, trm2);
	ft_trmloop(trm);
	return(0);
}
