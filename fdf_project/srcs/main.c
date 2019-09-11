/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdudley <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 16:28:36 by koparker          #+#    #+#             */
/*   Updated: 2019/09/11 15:54:57 by bdudley          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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

void    find_open(t_point ***head, t_data *data)
{
    void *mlx_ptr;
    void    *win_ptr;
    void    *img_ptr;
    int     *img_arr;
    int bits_per_pixel;
    int size_line;
    int endian;
    int i;
    int j;
    int  step;
    int stepy;
    int delta_x;
    int delta_y;

    bits_per_pixel = 0;
    size_line = 0;
    endian = 0;
    mlx_ptr = mlx_init();
    win_ptr = mlx_new_window(mlx_ptr, DW*2, DH*2, "Koperker");
    img_ptr = mlx_new_image(mlx_ptr, DW, DH);
    img_arr = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);
    j = 0;
 //   (*head)[0][0].alt = 0;
    stepy = DH / data->size_y;
    delta_y = DH - stepy * data->size_y;
    printf("size_x |%zu|\n", data->size_x);
    while (j < DH )
    {
        i = 0;
        step = DW / data->size_x;
        delta_x = DW - step * data->size_x;
        while (i < DW )
        {

           //     img_arr[j * DW + i] = (*head)[j / stepy][i / step].color;
            if (i % step == 0 || j % stepy == 0 || i == DW - delta_x - 1 || j == DH - delta_y - 1) {
               if ((*head)[j / stepy][i / step].alt != 0)
                    img_arr[j * DW + i] = 0xFFFFF;
                else
                    img_arr[j * DW + i] = (*head)[j / stepy][i / step].color;
            }
            i++;
        }
        j++;
    }
    mlx_put_image_to_window (mlx_ptr, win_ptr, img_ptr, DW /4, DH / 4 );
    mlx_loop(mlx_ptr);
}


int main(int ac, char **av)
{
	int		fd;
	t_point	**head;
	t_data	data;
	//t_list	*lst;

	(void)ac;//
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
//	find_open();
	find_open(&head, &data);
	//lst = head;
/*	while (lst != NULL)
	{
		printf("alt %d\n", lst->content->alt);
		lst = lst->next;
	}
*/	return (0);
}
