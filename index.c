/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: airandri <airandri@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 19:01:37 by rivandri          #+#    #+#             */
/*   Updated: 2026/03/08 05:30:43 by airandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*ft_copy_array(t_stack *a, int size)
{
	int		*tab;
	int		i;
	t_stack	*tmp;

	tab = malloc(sizeof(int) * size);
	if (!tab)
		return (NULL);
	i = 0;
	tmp = a;
	while (i < size)
	{
		tab[i] = tmp->value;
		i++;
		tmp = tmp->next;
	}
	return (tab);
}

static void	ft_sort_tab(int *tab, int size)
{
	int	i;
	int	temp;

	i = 0;
	while (i < (size - 1))
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = 0;
		}
		else
		{
			i++;
		}
	}
}

static int	find_index(int *tab, int size, int value)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == value)
			return (i);
		i++;
	}
	return (-1);
}

void	index_stack(t_stack *stack)
{
	int		size;
	int		*tab;
	t_stack	*tmp;

	size = ft_lst_size(stack);
	tab = ft_copy_array(stack, size);
	if (!tab)
		return ;
	ft_sort_tab(tab, size);
	tmp = stack;
	while (tmp)
	{
		tmp->index = find_index(tab, size, tmp->value);
		tmp = tmp->next;
	}
	free(tab);
}
