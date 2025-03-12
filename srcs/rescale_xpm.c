/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rescale_xpm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcossett <rcossett@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 20:41:25 by rcossett          #+#    #+#             */
/*   Updated: 2025/03/12 19:37:16 by rcossett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	mlx_get_pixel(void *img_ptr, int x, int y)
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		pixel;

	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	pixel = *(int *)(data + (y * size_line + x * (bpp / 8)));
	return (pixel);
}

static void	mlx_pixel_put_image(void *img_ptr, int x, int y, int color)
{
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	data = mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
	*(int *)(data + (y * size_line + x * (bpp / 8))) = color;
}

void	*rescale_xpm(void *mlx, char *path, int new_w, int new_h)
{
	void	*original;
	void	*scaled;
	t_vec2	pos;
	t_vec2	old_size;

	original = mlx_xpm_file_to_image(mlx, path, &old_size.x, &old_size.y);
	scaled = mlx_new_image(mlx, new_w, new_h);
	if (!original || !scaled)
		return (printf("unable to load texture at %s\n", path), NULL);
	pos.y = 0;
	while (pos.y < new_h)
	{
		pos.x = 0;
		while (pos.x < new_w)
		{
			mlx_pixel_put_image(scaled, pos.x, pos.y, \
				mlx_get_pixel(original, pos.x * \
				(double)old_size.x / new_w, pos.y * \
					(double)old_size.y / new_h));
			pos.x++;
		}
		pos.y++;
	}
	mlx_destroy_image(mlx, original);
	return (scaled);
}
