/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cheker.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 10:19:26 by airandri          #+#    #+#             */
/*   Updated: 2026/04/16 10:19:27 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHEKER_H
# define CHEKER_H
# include "get_next_line/get_next_line.h"
# include "../push_swap.h"

typedef struct s_moves
{
  char *move;
  t_moves *next;
} t_moves;

void  write_moves();

#endif
