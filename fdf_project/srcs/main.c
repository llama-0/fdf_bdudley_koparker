/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 22:58:07 by koparker         ###   ########.fr       */
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

void		print_usage(t_data *data)
{
	int	str;
	int	step;
	int	x;
	int	y;

	step = 20;
	x = DW_IM * 5 / 8;
	y = DH_IM * 3 / 4;
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y, COLOR_TABLE, "          Usage");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step, COLOR_TABLE, "     Press key to:");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 2, COLOR_TABLE, " show isometric projection  --  i");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 3, COLOR_TABLE, " show conic projection  --  p");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 4, COLOR_TABLE, " rotate around OX  --  x");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 5, COLOR_TABLE, " rotate around OY  --  y");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 6, COLOR_TABLE, " rotate around OZ  --  z");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 7, COLOR_TABLE, " zoom in  --  +");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 8, COLOR_TABLE, " zoom out  --  -");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 9, COLOR_TABLE, " reset all  --  space");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, x, y + step * 10, COLOR_TABLE, " exit  --  esc");
}

void        find_open(t_data *data)
{
	int height;
	int weight;

	data->win.mlx_ptr = mlx_init();
    data->win.win_ptr = mlx_new_window(data->win.mlx_ptr, DW_IM, DH_IM, "Koperker");
	data->win.img_ptr = mlx_new_image(data->win.mlx_ptr, DW_IM, DH_IM);
    data->win.img_arr = (int *)mlx_get_data_addr(data->win.img_ptr,
                                          &data->win.bits_per_pixel, &data->win.size_line, &data->win.endian);
	height = 1;
	weight = 1;
	data->ptr = mlx_xpm_file_to_image(data->win.mlx_ptr, "Photo.xpm", &height, &weight);
	new_image(data);
	mlx_hook(data->win.win_ptr, 17, 0, mlx_close, data);
	mlx_hook(data->win.win_ptr, 2, 0, key_release, data);
	mlx_loop(data->win.mlx_ptr);
}

void        new_image(t_data *data)
{
	int	str;
	
	mlx_clear_window(data->win.mlx_ptr, data->win.win_ptr);
    int i = -1;
    while (++i < DW_IM * DH_IM)
        (data->win.img_arr)[i] = BLACK;
    draw_plane(data, &data->win.img_arr);
    mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
                            data->win.img_ptr, 0, 0);
	print_usage(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr, data->ptr , 5, DH_IM - 150);
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, 5, DH_IM - 50, COLOR_TABLE, "This project is made by super girl's");
	str = mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, 5, DH_IM - 25, COLOR_TABLE, "Koparker and Bdudley");
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
	data.scale = 0;
	data.rotate_x = 0;
	data.rotate_y = 0;
	data.rotate_z = 0;
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		data.arr = read_file(fd, &data);
		step_x = (data.size_x > 1) ? (DW - 1) / (data.size_x - 1) : DW - 1;
		step_y = (data.size_y > 1) ? (DH - 1) / (data.size_y - 1) : DH - 1;
		data.step = step_x > step_y ? step_y : step_x;
		coord_to_pixel(&data);
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
