/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rivandri <rivandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:22:03 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/25 12:20:35 by rivandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <string.h>

static void	handle_flag(char *arg, t_options *opts)
{
	if (strcmp(arg, "--simple") == 0)
		opts->selector = "--simple";
	else if (strcmp(arg, "--medium") == 0)
		opts->selector = "--medium";
	else if (strcmp(arg, "--complex") == 0)
		opts->selector = "--complex";
	else if (strcmp(arg, "--adaptive") == 0)
		opts->selector = "--adaptive";
	else if (strcmp(arg, "--bench") == 0)
		opts->bench = 1;
}

static void	process_arg(char *arg, t_stack **a)
{
	char	**split;
	int		j;

	if (!ft_strchr(arg, ' '))
	{
		if (!is_valid_number(arg))
			ft_error(a);
		process_value(arg, a);
		return ;
	}
	split = ft_split(arg, ' ');
	j = 0;
	while (split[j])
	{
		if (!ft_str_is_space(split[j]))
		{
			if (!is_valid_number(split[j]))
				ft_error(a);
			process_value(split[j], a);
			j++;
		}
	}
	if (j == 0)
		ft_error(a);
	free_arg(split);
}

static void	fill_stack_and_opts(int argc, char **argv,
	t_options *opts, t_stack **a)
{
	int	i;

	opts->selector = NULL;
	opts->bench = 0;
	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			handle_flag(argv[i], opts);
		else
			process_arg(argv[i], a);
		i++;
	}
}

static t_stack	*parse_input(int argc, char **argv, t_options *opts)
{
	t_stack	*a;

	a = NULL;
	fill_stack_and_opts(argc, argv, opts, &a);
	return (a);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_options	opts;
	t_bench		bench;

	b = NULL;
	if (argc < 2)
		return (0);
	a = parse_input(argc, argv, &opts);
	index_stack(a);
	if (!a || ft_lst_size(a) <= 1 || is_sorted(a))
	{
		free_stack(&a);
		return (0);
	}
	ft_memset(&bench, 0, sizeof(t_bench));
	decision(&a, &b, opts.selector, &bench);
	if (opts.bench)
	{
		benchmark(&bench);
		benchmark_ops(&bench.ops);
	}
	free_stack(&a);
	free_stack(&b);
	return (0);
}
