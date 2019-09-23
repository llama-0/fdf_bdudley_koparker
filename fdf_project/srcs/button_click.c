/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/22 19:58:22 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int  key_release(int keycode, void *param)
{
    t_data *data;

    data = (t_data *)param;
    if (keycode == 7 || keycode == 6 || keycode == 16)
    {
    	data->camera = NO_PROJECTION;
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
    else if (keycode == 34 || keycode == 35)
	{
		coord_to_pixel(data);
		data->camera = (keycode == 34) ? ISO : CONIC;
		apply_projection(data);
		new_image(data);
	}
    else if (keycode == 49)
    {
		coord_to_pixel(data);
		data->scale = 0;
		data->rotate_z = 0;
		data->rotate_y = 0;
		data->rotate_x = 0;
		new_image(data);
    }
    else if (keycode == 27 || keycode == 24)
	{
		coord_to_pixel(data);
		if ((data->scale > -1 + SCALE && data->scale < 20 - SCALE) ||
		(data->scale < -1 + SCALE && keycode == 24) ||
		(data->scale > 20 - SCALE && keycode == 27))
			data->scale += keycode == 27 ? -SCALE : SCALE;
		if (data->camera == NO_PROJECTION)
			apply_rotation(data);
		else
			apply_projection(data);
		new_image(data);
	}
    else if (keycode == 53)
    	mlx_close(data);
    return (0);
}

//int		mouse_move(int x, int y, void *param)
//{
//	t_data *data;
//
//	data = (t_data *)param;
//
//}

int		mlx_close(void *param)
{
    delete_array((t_data *)param);
    exit(0);
}
