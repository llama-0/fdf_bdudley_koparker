/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/25 19:57:42 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void			print_usage(t_data *data)
{
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y,
			COLOR_TABLE, "          Usage");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP,
			COLOR_TABLE, "     Press key to:");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 2,
			COLOR_TABLE, " show isometric projection  --  i");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 3,
			COLOR_TABLE, " show conic projection  --  p");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 4,
			COLOR_TABLE, " rotate around OX  --  x");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 5,
			COLOR_TABLE, " rotate around OY  --  y");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 6,
			COLOR_TABLE, " rotate around OZ  --  z");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 7,
			COLOR_TABLE, " zoom in  --  +");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 8,
			COLOR_TABLE, " zoom out  --  -");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 9,
			COLOR_TABLE, " reset all  --  space");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, M_X, M_Y + M_STEP * 10,
			COLOR_TABLE, " exit  --  esc");
}

void			find_open(t_data *data)
{
	int height;
	int weight;

	height = 1;
	weight = 1;
	data->win.mlx_ptr = mlx_init();
	data->win.win_ptr = mlx_new_window(data->win.mlx_ptr,
			DW_IM, DH_IM, "Koperker");
	data->win.img_ptr = mlx_new_image(data->win.mlx_ptr,
			DW_IM, DH_IM);
	data->win.img_arr = (int *)mlx_get_data_addr(data->win.img_ptr,
			&data->win.bits_per_pixel, &data->win.size_line, &data->win.endian);
	data->ptr = mlx_xpm_file_to_image(data->win.mlx_ptr,
			"Photo.xpm", &height, &weight);
	new_image(data);
	mlx_hook(data->win.win_ptr, 17, 0, mlx_close, data);
	mlx_hook(data->win.win_ptr, 2, 0, key_release, data);
	mlx_loop(data->win.mlx_ptr);
}

void			new_image(t_data *data)
{
	int	i;

	i = -1;
	while (++i < DW_IM * DH_IM)
		(data->win.img_arr)[i] = BLACK;
	mlx_clear_window(data->win.mlx_ptr, data->win.win_ptr);
	draw_plane(data, &data->win.img_arr);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
							data->win.img_ptr, 0, 0);
	print_usage(data);
	mlx_put_image_to_window(data->win.mlx_ptr, data->win.win_ptr,
			data->ptr, 5, DH_IM - 150);
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, 5, DH_IM - 50,
			COLOR_TABLE, "This project is made by super girls");
	mlx_string_put(data->win.mlx_ptr, data->win.win_ptr, 5, DH_IM - 25,
			COLOR_TABLE, "Koparker and Bdudley");
}

void			init_data(t_data *data)
{
	data->size_x = 0;
	data->size_y = 0;
	data->capacity_y = 0;
	data->arr = NULL;
	data->scale = 0;
	data->rotate_x = 0;
	data->rotate_y = 0;
	data->rotate_z = 0;
	data->projection = NO_PROJECTION;
}

int				main(int ac, char **av)
{
	int		fd;
	t_data	data;
	size_t	step_x;
	size_t	step_y;

	(void)ac;
	init_data(&data);
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		data.arr = read_file(fd, &data);
		step_x = (data.size_x > 1) ? (DW - 1) / (data.size_x - 1) : DW - 1;
		step_y = (data.size_y > 1) ? (DH - 1) / (data.size_y - 1) : DH - 1;
		data.step = step_x > step_y ? step_y : step_x;
		coord_to_pixel(&data);
		close(fd);
		data.camera = get_max_z(&data);
		data.camera += (data.size_x * data.size_y < 100000) ? 50 : 500;
		find_open(&data);
	}
	else
		perror("open: couldn't open the file\n");
	return (0);
}
