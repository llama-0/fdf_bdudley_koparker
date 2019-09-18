/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/18 22:00:22 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int  key_release(int keycode, void *param)
{
    t_data *data;

    data = (t_data *)param;
  //  printf("keycode = %d, data->size_x = %p\n", keycode, data->size_x);
    if (keycode == 7 || keycode == 6 || keycode == 16)
    {
    	data->rotate_z += (keycode == 6) ? ALPHA : 0;
		data->rotate_x += (keycode == 7) ? ALPHA : 0;
		data->rotate_y += (keycode == 16) ? ALPHA : 0;
		coord_to_pixel(data);
		if (data->rotate_z >= 360 || data->rotate_x >= 360 || data->rotate_y >= 360)
		{
			data->rotate_y = (data->rotate_y >= 360) ? 0 : data->rotate_y;
			data->rotate_x = (data->rotate_x >= 360) ? 0 : data->rotate_x;
			data->rotate_z = (data->rotate_z >= 360) ? 0 : data->rotate_z;
		}
        apply_rotation(data);
        new_image(data);
    }
    else if (keycode == 34)
        apply_projection(data, keycode);
    else if (keycode == 49) //reset
    {

    }
    else if (keycode == 23 || keycode == 24) //scale
    {

    }
    return (0);
}

int mlx_close(void)
{

    //leaks
    exit(0);
}
