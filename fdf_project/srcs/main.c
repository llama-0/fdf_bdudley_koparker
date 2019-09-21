/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/21 17:27:51 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


void	print(t_data *data)
{
	for (size_t j = 0; j < data->size_y; j++)
	{
		for (size_t i = 0; i < data->size_x; i++)
		{
			printf("(%d,", (data->arr)[j][i].x);
			printf("%d) ", (data->arr)[j][i].y);
		}
		printf("\n");
	}
}

void        find_open(t_data *data)
{

 //   void *param;
  //  int (*ptr)(int keycode, t_point ***arr, t_data *data);

   // ptr = key_release;
 //  param = (void *)data;
	data->win.mlx_ptr = mlx_init();
    data->win.win_ptr = mlx_new_window(data->win.mlx_ptr, DW_IM, DH_IM, "Koperker");
    data->win.img_ptr = mlx_new_image(data->win.mlx_ptr, DW_IM, DH_IM);
    data->win.img_arr = (int *)mlx_get_data_addr(data->win.img_ptr,
                                          &data->win.bits_per_pixel, &data->win.size_line, &data->win.endian);
new_image(data);
   mlx_hook(data->win.win_ptr, 17, 0, mlx_close, NULL);
   mlx_hook(data->win.win_ptr, 2, 0, key_release, data);
   mlx_loop(data->win.mlx_ptr);
}

void        new_image(t_data *data)
{
	mlx_clear_window(data->win.mlx_ptr, data->win.win_ptr);
    int i = -1;
    while (++i < DW_IM * DH_IM)
        (data->win.img_arr)[i] = BLACK;
    draw_plane(data, &data->win.img_arr);
    mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
                            data->win.img_ptr, 0, 0);
}

int			main(int ac, char **av)
{
	int		fd;
	t_data	data;
	size_t	step_x;
	size_t	step_y;

	(void)ac;
	data.size_x = 0;
	data.size_y = 0;
	data.capacity_y = 0;
	data.arr = NULL;
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		data.arr = read_file(fd, &data);
		step_x = (data.size_x > 1) ? (DW - 1) / (data.size_x - 1) : DW - 1;
		step_y = (data.size_y > 1) ? (DH - 1) / (data.size_y - 1) : DH - 1;
		data.step = step_x > step_y ? step_y : step_x;
		coord_to_pixel(&data);
	//	print(&data);
		close(fd);
	}
	else
	{
		perror("open: couldn't open the file\n");
		return (0);
	}
	find_open(&data);
	return (0);
}
