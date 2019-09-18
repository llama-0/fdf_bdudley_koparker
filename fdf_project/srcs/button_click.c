/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_click.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 16:55:14 by bdudley           #+#    #+#             */
/*   Updated: 2019/09/18 20:16:04 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int  key_release(int keycode, void *param)
{
    t_data *data;

    data = (t_data *)param;
  //  printf("keycode = %d, data->size_x = %p\n", keycode, data->size_x);
    if (keycode == 7 || keycode == 6 || keycode == 16) {
        apply_rotation(data, keycode);
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
}

int mlx_close(void)
{

    //leaks
    exit(0);
}
