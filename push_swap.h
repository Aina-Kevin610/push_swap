/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 17:42:13 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/28 20:22:28 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include "ft_printf.h"
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	struct s_stack	*next;
}	t_stack;

typedef struct s_operations
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_operations;

typedef struct s_bench
{
	t_operations	ops;
	float			disorder;
	char			*strategy;
	char			*complexity;
	int				total;
}	t_bench;

typedef struct s_options
{
	char	*selector;
	int		bench;
}	t_options;

void	sa(t_stack **a, t_bench *bench);
void	sb(t_stack **b, t_bench *bench);
void	ss(t_stack **a, t_stack **b, t_bench *bench);
void	pa(t_stack **a, t_stack **b, t_bench *bench);
void	pb(t_stack **a, t_stack **b, t_bench *bench);
void	ra(t_stack **a, t_bench *bench);
void	rb(t_stack **b, t_bench *bench);
void	rr(t_stack **a, t_stack **b, t_bench *bench);
void	rra(t_stack **a, t_bench *bench);
void	rrb(t_stack **b, t_bench *bench);
void	rrr(t_stack **a, t_stack **b, t_bench *bench);
void	sort_three(t_stack **a, t_bench *bench);
void	put_min_top(t_stack **a, t_bench *bench);
void	handle_min(t_stack	**a, t_stack **b, t_bench *bench);
void	decision(t_stack **a, t_stack **b, char *selector, t_bench *bench);
void	selection_sort(t_stack **a, t_stack **b, t_bench *bench);
void	chunk_sort(t_stack **a, t_stack **b, t_bench *bench);
void	radix_sort(t_stack **a, t_stack **b, t_bench *bench);

void	print_stack(t_stack *stack);
t_stack	*new_node(int value);
void	add_back(t_stack **stack, t_stack *node);
int		ft_lst_size(t_stack *stack);
void	free_stack(t_stack **stack);
int		is_valid_number(char *str);
int		is_sorted(t_stack *a);
int		duplicate(t_stack *stack, int value);
long	ft_atol(const char *str);
void	ft_error(t_stack **stack);
void	free_arg(char **split);
void	process_value(char *arg, t_stack **a);
void	parse_arguments_split(int argc, char **argv, t_stack **a);
char	**ft_split(char const *s, char c);
void	index_stack(t_stack *stack);
int		get_max(t_stack *a);
float	disorder(t_stack *a);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putfloat_fd(float n, int fd);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_isspace(int c);
int		ft_str_is_space(char *str);
void	benchmark(t_bench *c);
void	benchmark_ops(t_operations *d);

#endif
