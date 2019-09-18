/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 17:44:35 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


void	print(t_point **points, t_data *data)
{
	for (size_t j = 0; j < data->size_y; j++)
	{
		for (size_t i = 0; i < data->size_x; i++)
		{
			printf("(%d,", points[j][i].x);
			printf("%d) ", points[j][i].y);
		}
		printf("\n");
	}
}

int mlx_close(void)
{
   exit(0);
}

void        find_open(t_point ***head, t_data *data)
{
   t_window    win;
//    void *p;

   win.mlx_ptr = mlx_init();
   win.win_ptr = mlx_new_window(win.mlx_ptr, DW_IM, DH_IM, "Koperker");
   win.img_ptr = mlx_new_image(win.mlx_ptr, DW_IM, DH_IM);
   win.img_arr = (int *)mlx_get_data_addr(win.img_ptr,
                                          &win.bits_per_pixel, &win.size_line, &win.endian);
   draw_plane(head, data, &win.img_arr);
   mlx_put_image_to_window(win.mlx_ptr, win.win_ptr,
                           win.img_ptr, 0, 0);
   mlx_hook(win.win_ptr, 17, 0, &mlx_close, NULL);
   mlx_loop(win.mlx_ptr);
}

int			main(int ac, char **av)
{
	int		fd;
	t_point	**head;
	t_data	data;

	(void)ac;
	data.size_x = 0;
	data.size_y = 0;
	data.capacity_y = 0;
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		head = read_file(fd, &data);
		coord_to_pixel(&head, &data);
		// print(head, &data);
		close(fd);
	}
	else
	{
		perror("open: couldn't open the file\n");
		return (0);
	}
	find_open(&head, &data);
	return (0);
}
