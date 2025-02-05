/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_merge.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 23:43:49 by rcossett          #+#    #+#             */
/*   Updated: 2025/01/22 23:48:15 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

#include <stdio.h>

int main(int argc, char *argv[])
{
    int	i;

	i = 0;
	while (argv[1][i] && argv[2][i])
	{
		if (argv[1][i] != ' ')
		{
			printf("%c", argv[1][i]);
		}
		else
		{
			printf("%c", argv[2][i]);
		}
		i++;
	}
    return 0;
}
