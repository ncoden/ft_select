/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncoden <ncoden@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 17:59:44 by ncoden            #+#    #+#             */
/*   Updated: 2015/06/09 20:08:46 by ncoden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"

int					g_stdout_dev;

typedef struct		s_lst_item
{
	EXTEND_LST		(s_lst_item);
	char			*name;
	t_bool			selected;
}					t_lst_item;

typedef struct		s_lst_col
{
	EXTEND_LST		(s_lst_col);
	t_lst_item		*items;
	int				height;
	int				width;
}					t_lst_col;

t_trm				*term_init(void);

t_lst_col			*args_init(int argc, char **argv);
t_lst_col			*args_calc_cols(t_lst_item *items, t_lst_col *cols);
void				args_print(t_lst_col *args);
t_bool				args_print_line(t_lst_col *args, int index, int width_term);
void				args_resize(t_lst_col *args);

#endif
