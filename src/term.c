/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/08 14:51:56 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/09 19:28:10 by ncoden           ###   ########.fr       */
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