/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/15 23:10:26 by koparker         ###   ########.fr       */
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
    y_i = DW_IM;
    if (dy < 0)
    {
        y_i = -y_i;
        dy = -dy;
    }
    diff = 2 * dy - dx;
    y = p1->y;
    x = p1->x;
    while (x < p2->x)
    {
        printf("x %d | y %d\n" , x, y); //delete
        //printf("x + y %d\n", x + y); //delete
        if (x >= 0 && y >= 0 && y < DH_IM * DW_IM && x < DW_IM)
		{	
			printf("Vilena\n");
			(*img_arr)[y + x] = 0xFFFFFF;
		}
        if (diff > 0)
        {
            y = y + y_i;
            diff = diff - 2 * dx;
        }
        diff = diff + 2 * dy;
        x++;
    }
	printf("Buy Vilena\n");
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
	printf("p1->y %d, p2->y %d\n", p1->y, p2->y);
    while (y < p2->y)
    {
        printf("=======x %d | y %d\n" , x, y); //delete
        //printf("x + y * DW %d\n", x + y * DW); //delete
		if (x >= 0 && y >= 0 && y < DH_IM * DW_IM && x < DW_IM)
		{
			printf("x %d | y %d  !! %d\n" , x, y, y);
			// printf("Nastya\n"); 
			(*img_arr)[x + y] = 0xFFFFFF;
		}
        if (diff > 0)
        {
            x = x + x_i;
            diff = diff - 2 * dy;
        }
        diff = diff + 2 * dx;
        //printf("%f diff and x %d\n", diff, x); //delete
        y += DW_IM;
    }
     printf("Buy Nastya\n"); //delete
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

static void iso(int *x, int *y)
{
	int previous_x;
	int previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(0.523599) - previous_y / DW_IM /DW * sin(0.523599);
	*y = previous_y * cos(0.523599) + previous_x * sin(0.523599);
}

void		draw_plane(t_point ***head, t_data *data, int **img_arr)
{
	size_t	i;
	size_t	j;

print(*head, data);
	j = 0;
   	while (j < data->size_y)
   	{
       i = 0;
       while (i < data->size_x) {
       //    printf("POPO\n");
           printf("x, y %d %d\n", (*head)[j][i].x, (*head)[j][i].y);
           iso(&(*head)[j][i].x, &(*head)[j][i].y);
           printf("x, y %d %d\n", (*head)[j][i].x, (*head)[j][i].y);
           i++;
       }
       j++;
   	}
	   printf("asss\n");
	   print(*head, data);
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
	win.win_ptr = mlx_new_window(win.mlx_ptr, DW_IM * 2, DH_IM * 2, "Koperker");
	win.img_ptr = mlx_new_image(win.mlx_ptr, DW_IM, DH_IM);
	win.img_arr = (int *)mlx_get_data_addr(win.img_ptr,
			&win.bits_per_pixel, &win.size_line, &win.endian);
	draw_plane(head, data, &win.img_arr);
	printf("Sofia\n");
	mlx_put_image_to_window(win.mlx_ptr, win.win_ptr,
			win.img_ptr, 0, 0);
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
