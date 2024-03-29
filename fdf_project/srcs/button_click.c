/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/25 19:46:27 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void		button_rotation(t_data *data, int keycode)
{
	data->projection = NO_PROJECTION;
	data->rotate_z += (keycode == 6) ? ALPHA : 0;
	data->rotate_x += (keycode == 7) ? ALPHA : 0;
	data->rotate_y += (keycode == 16) ? ALPHA : 0;
	data->rotate_y = (data->rotate_y >= 360) ? 0 : data->rotate_y;
	data->rotate_x = (data->rotate_x >= 360) ? 0 : data->rotate_x;
	data->rotate_z = (data->rotate_z >= 360) ? 0 : data->rotate_z;
	coord_to_pixel(data);
	apply_rotation(data);
	new_image(data);
}

static void		button_projection(t_data *data, int keycode)
{
	coord_to_pixel(data);
	data->projection = (keycode == 34) ? ISO : CONIC;
	apply_projection(data);
	new_image(data);
}

static void		button_scale(t_data *data, int keycode)
{
	coord_to_pixel(data);
	if ((data->scale > -1 && data->scale < 20) ||
		(data->scale <= -1 && keycode == 24) ||
		(data->scale >= 20 && keycode == 27))
		data->scale += keycode == 27 ? -SCALE : SCALE;
	if (data->projection == NO_PROJECTION)
		apply_rotation(data);
	else
		apply_projection(data);
	new_image(data);
}

int				key_release(int keycode, void *param)
{
	t_data *data;

	data = (t_data *)param;
	if (keycode == 7 || keycode == 6 || keycode == 16)
		button_rotation(data, keycode);
	else if (keycode == 34 || keycode == 35)
		button_projection(data, keycode);
	else if (keycode == 49)
	{
		coord_to_pixel(data);
		data->scale = 0;
		data->rotate_z = 0;
		data->rotate_y = 0;
		data->rotate_x = 0;
		data->projection = NO_PROJECTION;
		new_image(data);
	}
	else if (keycode == 27 || keycode == 24)
		button_scale(data, keycode);
	else if (keycode == 53)
		mlx_close(data);
	return (0);
}

int				mlx_close(void *param)
{
	t_data *data;

	data = (t_data *)param;
	delete_array(data);
	exit(0);
}
