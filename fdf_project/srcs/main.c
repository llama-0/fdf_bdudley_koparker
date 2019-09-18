/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/18 16:31:14 by koparker         ###   ########.fr       */
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
        y_i = -y_i;
        dy = -dy;
    }
    diff = 2 * dy - dx;
	y = p1->y + SHIFT_Y / 2;
	x = p1->x + SHIFT_X / 2;
    while (x < p2->x + SHIFT_X / 2)
    {
        if (x >= 0 && y >= 0 && y < DH_IM * DW_IM && x < DW_IM)
		{	
			(*img_arr)[y * DW_IM + x] = 0xFFFFFF;
		}
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
        x_i = -x_i;
        dx = -dx;
    }
    diff = 2 * dx - dy;
	y = p1->y + SHIFT_Y / 2;
	x = p1->x + SHIFT_X / 2;
	while (y < p2->y + SHIFT_Y / 2 + 1)
    {
		if (x >= 0 && y >= 0 && y < DH_IM * DW_IM && x < DW_IM)
		{
			(*img_arr)[x + y * DW_IM] = WHITE;
		}
        if (diff > 0)
        {
            x = x + x_i;
            diff = diff - 2 * dy;
        }
        diff = diff + 2 * dx;
        y++;
    }
}

void		plot(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
	if (abs(p2->y - p1->y) < abs(p2->x - p1->x))
	{
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

static void rotate_OZ(int *x, int *y)
{
	int previous_x;
	int previous_y;
	int alpha;

	alpha = 330;
	previous_x = *x - DW / 2;
	previous_y = *y - DH / 2;
	*x = trunc((previous_x * COS(alpha)) - trunc(previous_y * SIN(alpha))) + DW / 2;
	*y = trunc((previous_y * COS(alpha)) + trunc(previous_x * SIN(alpha))) + DH / 2;
}

static void iso(int *x, int *y, int z)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * COS(30);
    *y = -z + (previous_x + previous_y) * SIN(30);
}


// TODO: add rotation_OX, rotation_OY; remove iso. 
void	apply_rotation(t_point ***head, t_data *data, int flag)
{
	size_t	i;
	size_t	j;

	j = 0;
   	while (j < data->size_y)
   	{
       	i = 0;
       	while (i < data->size_x)
		{
        	if (flag == 1)
				rotate_OZ(&(*head)[j][i].x, &(*head)[j][i].y);
			else
				iso(&(*head)[j][i].x, &(*head)[j][i].y, (*head)[j][i].alt * 3);
			i++;
      	}
       	j++;
   	}
}

// TODO: add balancer
void		draw_plane(t_point ***head, t_data *data, int **img_arr)
{
	size_t	i;
	size_t	j;
	int step_x;
	int step_y;

	apply_rotation(head, data, 0);
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

int mlx_close(void)
{
   exit(0);
}
void        find_open(t_point ***head, t_data *data)
{
   t_window    win;
   void *p;

   win.mlx_ptr = mlx_init();
   win.win_ptr = mlx_new_window(win.mlx_ptr, DW_IM, DH_IM, "Koperker");
   win.img_ptr = mlx_new_image(win.mlx_ptr, DW_IM, DH_IM);
   win.img_arr = (int *)mlx_get_data_addr(win.img_ptr,
                                          &win.bits_per_pixel, &win.size_line, &win.endian);
   draw_plane(head, data, &win.img_arr);
   mlx_put_image_to_window(win.mlx_ptr, win.win_ptr,
                           win.img_ptr, 0, 0);
   mlx_hook(win.win_ptr, 17, 0, &mlx_close, p);
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
