/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:21:33 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/25 10:10:10 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	process_value(char *arg, t_stack **a)
{
	long	value;

	if (!is_valid_number(arg))
		ft_error(a);
	value = ft_atol(arg);
	if (value > INT_MAX || value < INT_MIN || value == LONG_MAX)
		ft_error(a);
	if (duplicate(*a, (int)value))
		ft_error(a);
	add_back(a, new_node((int)(value)));
}

static void	parse_split(char **split, t_stack **a)
{
	int	i;

	i = 0;
	while (split[i])
	{
		process_value(split[i], a);
		i++;
	}
}

static void	parse_arguments(int argc, char **argv, t_stack **a)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		process_value(argv[i], a);
		i++;
	}
}

void	parse_arguments_split(int argc, char **argv, t_stack **a)
{
	char	**split;

	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		if (!split || !split[0])
			ft_error(a);
		parse_split(split, a);
		free_arg(split);
	}
	else
		parse_arguments(argc, argv, a);
}
