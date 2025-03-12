/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 18:33:35 by rcossett          #+#    #+#             */
/*   Updated: 2025/02/27 15:58:08 by rcossett         ###   ########.fr       */
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

//		returns a random value between min and max
int	r_range(int min, int max)
{
	if (min > max)
		return (-1);
	return (get_urandom(min, max));
}

//return 1 automatiquement si la condition est 
// reunis cad que les deux position x et y matchent
int	cmp_vec2(t_vec2 a, t_vec2 b)
{
	return (a.x == b.x && a.y == b.y);
}

char	*ft_strmegajoin(char *a, char *b, char *c, char *d)
{
	char	*a_b;
	char	*a_b_c;
	char	*a_b_c_d;

	if (!a && !b)
		return (NULL);
	if (!b)
		return (a);
	a_b = ft_strjoin(a, b);
	if (!c)
		return (a_b);
	a_b_c = ft_strjoin(a_b, c);
	free(a_b);
	if (!d)
		return (a_b_c);
	a_b_c_d = ft_strjoin(a_b_c, d);
	free(a_b_c);
	return (a_b_c_d);
}

int	get_urandom(int min, int max)
{
	static int		fd = -1;
	static int		initialized = 0;
	unsigned int	random_value;

	if (!initialized)
	{
		fd = open("/dev/urandom", O_RDONLY);
		if (fd == -1)
			return (min);
		initialized = 1;
	}
	if (read(fd, &random_value, sizeof(unsigned int)) != sizeof(unsigned int))
		return (min);
	return ((min) + (random_value % (max - min + 1)));
}
