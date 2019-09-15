/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/15 16:00:48 by koparker         ###   ########.fr       */
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

void    draw_line_low(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
    double diff;
    int dx;
    int dy;
    int y_i;
    int y;
    int x;

    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    y_i = 1;
    if (dy < 0)
    {
        y_i = -1;
        dy = -dy;
    }
    diff = 2 * dy - dx;
    y = p1->y;
    x = p1->x;
    while (x < p2->x)
    {
        printf("x %d | y %d\n" , x, y); //delete
        printf("x + y %d\n", x + y); //delete
        (*img_arr)[y * DW + x] = 0xFFFFFF;
        if (diff > 0)
        {
            y = y + y_i;
            diff = diff - 2 * dx;
        }
        diff = diff + 2 * dy;
        x++;
    }
}

void    draw_line_high(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
    double diff;
    int dx;
    int dy;
    int x_i;
    int y;
    int x;

    dx = p2->x - p1->x;
    dy = p2->y - p1->y;
    x_i = 1;
    if (dx < 0)
    {
        x_i = -1;
        dx = -dx;
    }
    diff = 2 * dx - dy;
    x = p1->x;
    y = p1->y;
    // printf("p1->y %d and p2->y %d\n", p1->y, p2->y); //delete
    while (y < p2->y)
    {
        // printf("x %d | y %d\n" , x, y); //delete
        printf("x + y * DW %d\n", x + y * DW); //delete
        (*img_arr)[x + y * DW] = 0xFFFFFF;
        if (diff > 0)
        {
            x = x + x_i;
            diff = diff - 2 * dy;
        }
        diff = diff + 2 * dx;
        //printf("%f diff and x %d\n", diff, x); //delete
        y++;
    }
     printf("Nastya\n"); //delete
}

void		plot(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
	if (abs(p2->y - p1->y) < abs(p2->x - p1->x))
	{
		printf("draw_line_low\n"); //delete
		if (p1->x > p2->x)
		{
			draw_line_low(p2, p1, img_arr, data);
		}
		else
		{
			draw_line_low(p1, p2, img_arr, data);
		}
	}
    else
    {
    	printf("draw_line_high\n"); //delete
		if (p1->y > p2->y)
		{
			draw_line_high(p2, p1, img_arr, data);
		}
		else
		{
			draw_line_high(p1, p2, img_arr, data);
		}
	}
}

void		draw_plane(t_point ***head, t_data *data, int **img_arr)
{
	size_t	i;
	size_t	j;

	j = 0;
	while (j < data->size_y)
	{
		i = 0;
		while (i < data->size_x)
		{
			if (i < data->size_x - 1)
			{
				plot(&((*head)[j][i]), &((*head)[j][i + 1]), img_arr, data);
			}
			if (j < data->size_y - 1)
			{
				plot(&((*head)[j][i]), &((*head)[j + 1][i]), img_arr, data);
			}
			i++;
		}
		j++;
	}
}

void		find_open(t_point ***head, t_data *data)
{
	t_window	win;

	win.bits_per_pixel = 0;
	win.size_line = 0;
	win.endian = 0;
	win.mlx_ptr = mlx_init();
	win.win_ptr = mlx_new_window(win.mlx_ptr, DW * 2, DH * 2, "Koperker");
	win.img_ptr = mlx_new_image(win.mlx_ptr, DW, DH);
	win.img_arr = (int *)mlx_get_data_addr(win.img_ptr,
			&win.bits_per_pixel, &win.size_line, &win.endian);
	draw_plane(head, data, &win.img_arr);
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr,
			win.img_ptr, DW / 4, DH / 4);
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
		print(head, &data);
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
