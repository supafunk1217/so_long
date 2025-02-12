/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:33:35 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/12 22:02:29 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

t_vec2	get_v2(int x, int y)
{
	t_vec2	vector;

	vector.x = x;
	vector.y = y;
	return (vector);
}

//		returns a random value betwewen min and max
int	r_range(int min, int max)
{
	if (min > max)
		return (-1);
	return (rand() % (max - min + 1) + min);
}

//return 1 auomatiquement si la condition est 
// reunis cad que les deux position x et y matchent
int	cmp_vec2(t_vec2 a, t_vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}
