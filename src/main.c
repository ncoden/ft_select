/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/05/17 22:09:17 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
	#include <stdio.h>
int				main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	t_trm		*trm;

	trm = ft_trmnew();
	trm->opts.c_lflag &= ~(ICANON);
	trm->opts.c_lflag &= ~(ECHO);
	trm->opts.c_cc[VMIN] = 1;
	trm->opts.c_cc[VTIME] = 0;
	ft_trmkeyhook(trm, "c", (void (*)(void *))&ft_putstr, "Hello");
	ft_trmkeycmd(trm, "e", "cl");
	ft_trmloop(trm);
	return(0);
}
