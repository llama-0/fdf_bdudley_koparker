/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/14 19:52:09 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void    *mlx_ptr;
void    *win_ptr;

//    printf("step`-x |%d|\n", step_x);
//    printf("step`-y |%d|\n", step_y);
//    (void)head;
//    while (j < DH)
//    {
//        i = 0;
//        while (i < DW)
//        {
//            if ((i % step_x == 0 || j % step_y == 0)
//            && ((size_t)j)<= ((data->size_y - 1) * (step_y))
//            && ((size_t)i)<= ((data->size_x - 1)* (step_x)))
//            {
//              //  draw_line(&((*head)[j / step_y][i / step_x]), &((*head)[j / step_y][i / step_x]))
//                if ((*head)[j / step_y][i / step_x].alt != 0)
//                    (*img_arr)[j * DW + i] = 0xFFFFF;
//                else
//                    (*img_arr)[j * DW + i] = (*head)[j / step_y][i / step_x].color;
//            printf("i = %d - d %lu\n j = %d - d %lu\n", i,((data->size_x - 1)* (step_x)) , j , ((data->size_y - 1) * (step_y)));
//            }
//            i++;
//        }
//        j++;
//    }
//    step_y = DH / data->size_y;

void	print(t_point **points, t_data *data)
{
	for (size_t j = 0; j < data->size_y; j++)
	{
		for (size_t i = 0; i < data->size_x; i++)
		{
			printf("%d ", points[j][i].alt);
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
    int step_x;
    int step_y;
    int x;

    step_y = DH / data->size_y;
    step_x = DW / data->size_x;
    dx = (p2->x - p1->x)*step_x;
    dy = (p2->y - p1->y)*step_y;
    y_i = DH;
    if (dy < 0)
    {
        y_i = -y_i;
        dy = -dy;
    }
    diff = 2 * dy - dx;
    y = p1->y * step_y;
    x = p1->x * step_x;
    while (x < p2->x * step_x)
    {
        (*img_arr)[y + x] = 0xFFFFFF;
       // mlx_pixel_put(mlx_ptr, win_ptr, x, p1->y * step_y * DH, 0xFFFFFF);
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
    int step_y;
    int step_x;
    int x;

    step_y = DH / data->size_y;
    step_x = DW / data->size_x;
    dx = (p2->x - p1->x)*step_x;
    dy = (p2->y - p1->y)*step_y;
    x_i = DW;
    if (dx < 0)
    {
        x_i = -x_i;
        dx = -dx;
    }
    diff = 2 * dx - dy;
    x = p1->x * step_x;
    y = p1->y * step_y;
    printf("p1->y %d and p2->y %d\n", p1->y, p2->y);
    while (y < p2->y * step_y)
    {
       // mlx_pixel_put(mlx_ptr, win_ptr, p1->x * step_x, y * DW, 0xFFFFFF);
        printf("x + y * DW %d\n", x + y * DW);
        (*img_arr)[x + y * DW] = 0xFFFFFF;
        if (diff > 0)
        {
            x = x + x_i;
            diff = diff - 2 * dy;
        }
        diff = diff + 2 * dx;
        printf("%f diff and x %d\n", diff, x);
        y++;
    }
     printf("Nastya\n");
}

//static void iso(int *x, int *y)
//{
//    int previous_x;
//    int previous_y;
//
//    previous_x = *x;
//    previous_y = *y;
//    *x = previous_x * cos(0.523599) - previous_y * sin(0.523599);
//    *y = previous_y * cos(0.523599) + previous_x * sin(0.523599);
//}
//
//static void riso(int *x, int *y)
//{
//    int previous_x;
//    int previous_y;
//
//    previous_x = *x;
//    previous_y = *y;
//    *x = previous_x * cos(5.75959) - previous_y * sin(5.75959);
//    *y = previous_y * cos(5.75959) + previous_x * sin(5.75959);
//}


void    plot(t_point *p1, t_point *p2, int **img_arr, t_data *data)
{
    if (abs(p2->y - p1->y) < abs(p2->x - p1->x))
    {
        if (p1->x > p2->x)
        {
            printf("draw_line_low\n");
            draw_line_low(p2, p1, img_arr, data);
        }
        else
        {
            draw_line_low(p1, p2, img_arr, data);
        }
    }
    else
    {
        printf("draw_line_high\n");
        p1->y > p2->y ? draw_line_high(p2, p1, img_arr, data) : draw_line_high(p1, p2, img_arr, data);
//        if (p1->y > p2->y)
//        {
//            iso(&(p2->x), &(p2->y));
//            draw_line_high(p2, p1, img_arr, data);
//            riso(&(p2->x), &(p2->y));
//        }
//        else
//        {
//            iso(&(p1->x), &(p1->y));
//            draw_line_high(p1, p2, img_arr, data);
//            riso(&(p1->x), &(p1->y));
//        }
    }
}

static void iso(int *x, int *y)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = previous_x * cos(0.523599) - previous_y * sin(0.523599);
    *y = previous_y * cos(0.523599) + previous_x * sin(0.523599);
}

static void riso(int *x, int *y)
{
    int previous_x;
    int previous_y;

    previous_x = *x;
    previous_y = *y;
    *x = previous_x * cos(5.75959) - previous_y * sin(5.75959);
    *y = previous_y * cos(5.75959) + previous_x * sin(5.75959);
}


void    draw_plane(t_point ***head, t_data *data, int **img_arr)
{
    size_t i;
    size_t j;

//    j = 0;
//    while (j < data->size_y)
//    {
//        i = 1;
//        while (i < data->size_x) {
//        //    printf("POPO\n");
//            iso(&(*head)[j][i].x, &(*head)[j][i].y);
//            i++;
//        }
//        j++;
//    }

//    int previous_x;
//    int previous_y;
//
//    previous_x = (*head)[0][1].x;
//    previous_y = (*head)[0][1].y;
//    (*head)[0][1].x = previous_x * cos(5.75959) - previous_y * sin(5.75959);
//    (*head)[0][1].y = previous_y * cos(5.75959) + previous_x * sin(5.75959);
    // (*head)[0][0].x = 0;
    // (*head)[0][0].y = 0;
    // (*head)[0][1].x = 1;
    //         (*head)[0][1].y = 1;
    //       //  printf("x_0, y_1 %d %d\n", (*head)[0][1].x, (*head)[0][1].y);
    j = 0;
    while (j < data->size_y)
    {
        i = 0;
        while (i < data->size_x)
        {
            if (i < data->size_x - 1) {
                //iso(&(*head)[j][i].x, &(*head)[j][i].y);
           //    iso(&(*head)[j][i + 1].x, &(*head)[j][i + 1].y);
                plot(&((*head)[j][i]), &((*head)[j][i + 1]), img_arr, data);
               // plot(&((*head)[j][i]), &((*head)[j][i + 1]), img_arr, data);
               // riso(&(*head)[j][i].x, &(*head)[j][i].y);
              // riso(&(*head)[j][i + 1].x, &(*head)[j][i + 1].y);
            }
            if (j < data->size_y - 1) {
               // iso(&(*head)[j][i].x, &(*head)[j][i].y);
             //  iso(&(*head)[j + 1][i].x, &(*head)[j + 1][i].y);
                plot(&((*head)[j][i]), &((*head)[j + 1][i]), img_arr, data);
                //riso(&(*head)[j][i].x, &(*head)[j][i].y);
               // riso(&(*head)[j + 1][i].x, &(*head)[j + 1][i].y);
            }
            i++;
        }
        j++;
    }
}

void    find_open(t_point ***head, t_data *data)
{

    void    *img_ptr;
    int     *img_arr;
    int     bits_per_pixel;
    int     size_line;
    int     endian;


    bits_per_pixel = 0;
    size_line = 0;
    endian = 0;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, DW*2, DH*2, "Koperker");
    img_ptr = mlx_new_image(mlx_ptr, DW, DH);
    img_arr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
    draw_plane(head, data, &img_arr);
    mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, DW /4, DH / 4 );
    mlx_loop(mlx_ptr);
}


int main(int ac, char **av)
{
	int		fd;
	t_point	**head;
	t_data	data;

	(void)ac;
	if ((fd = open(av[1], O_RDONLY)) >= 0)
	{
		head = read2(fd, &data);
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
