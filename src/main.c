/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 13:39:59 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/09 20:08:39 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"
	#include <stdio.h>

int				main(int argc, char **argv)
{
	t_trm		*trm;
	t_lst_col	*args;

	g_stdout_dev = open("/dev/ttys000", O_WRONLY);
	if (!(trm = term_init()))
		return (0);
	if (!(args = args_init(argc, argv)))
		return (0);
	args_print(args);
	ft_trmsignalhook(trm, SIGWINCH, (void (*)(void *))&args_resize, args);
	ft_trmstart(trm);
	return(0);
}
