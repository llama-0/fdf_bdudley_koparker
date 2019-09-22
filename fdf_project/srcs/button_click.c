/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/22 15:59:30 by koparker         ###   ########.fr       */
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

		data->rotate_y = (data->rotate_y >= 360) ? 0 : data->rotate_y;
		data->rotate_x = (data->rotate_x >= 360) ? 0 : data->rotate_x;
		data->rotate_z = (data->rotate_z >= 360) ? 0 : data->rotate_z;

		coord_to_pixel(data);
        apply_rotation(data);
        new_image(data);
    }
    else if (keycode == 34)
	{
		coord_to_pixel(data);
		apply_projection(data, keycode);
		new_image(data);
	}
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
