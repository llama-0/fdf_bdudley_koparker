/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 17:43:46 by koparker          #+#    #+#             */
/*   Updated: 2019/09/20 22:27:16 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * COS(30);
    *y = -z + (previous_x + previous_y) * SIN(30);
}

void	apply_projection(t_data *data, int keycode)
{
	size_t	i;
	size_t	j;

	j = 0;
   	while (j < data->size_y)
   	{
       	i = 0;
       	while (i < data->size_x)
		{
			if (keycode == 34)
				iso(&(data->arr)[j][i].x, &(data->arr)[j][i].y, (data->arr)[j][i].alt);
			i++;
      	}
       	j++;
   	}
}