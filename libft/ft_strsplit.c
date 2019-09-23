/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: koparker <koparker@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 20:52:16 by koparker          #+#    #+#             */
/*   Updated: 2019/09/23 20:01:15 by koparker         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// static size_t	ft_words_len(char const *s, char c)
// {
// 	size_t		res;
// 	const char	*tmp;

// 	res = 0;
// 	tmp = s;
// 	while (*tmp)
// 	{
// 		while (*tmp == c)
// 			tmp++;
// 		if (*tmp)
// 			res++;
// 		while (*tmp && *tmp != c)
// 			tmp++;
// 	}
// 	return (res);
// }

// static char		*ft_strncpy_custom(char *dst, const char *src, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (src[i] && i < len)
// 	{
// 		dst[i] = src[i];
// 		i++;
// 	}
// 	dst[i] = '\0';
// 	return (dst);
// }

// static void		ft_del(char ***res, size_t k)
// {
// 	while (k--)
// 	{
// 		free((*res)[k]);
// 		(*res)[k] = NULL;
// 	}
// 	ft_strdel(*res);
// }

// char			**ft_strsplit(char const *s, char c)
// {
// 	const char	*word_head;
// 	size_t		k;
// 	char		**res;

// 	if (s == NULL || c == 0)
// 		return (NULL);
// 	if (!(res = (char **)malloc(sizeof(char*) * (ft_words_len(s, c) + 1))))
// 		return (NULL);
// 	k = 0;
// 	while (*s)
// 	{
// 		while (*s && *s == c)
// 			s++;
// 		word_head = s;
// 		while (*s && *s != c)
// 			s++;
// 		if (!(res[k] = ft_memalloc(s - word_head + 1)))
// 			ft_del(&res, k);
// 		else if ((s - word_head) != 0)
// 			ft_strncpy_custom(res[k++], word_head, s - word_head);
// 	}
// 	res[k] = NULL;
// 	return (res);
// }

static int		ft_count_word(char const *s, char c)
{
	int lenght;

	lenght = 0;
	while (*s != '\0')
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			lenght++;
		while (*s != '\0' && *s != c)
			s++;
	}
	return (lenght + 1);
}

static int		ft_count_letter(char const *s, char c)
{
	int lenght;

	lenght = 0;
	while (*s != c && *s++ != '\0')
		lenght++;
	return (lenght);
}

static char		**ft_delete(char ***a)
{
	int i;

	i = 0;
	while (*a[i] != NULL)
	{
		ft_strdel(&(*a[i]));
		*a[i] = NULL;
		i++;
	}
	ft_memdel((void *)(&(*a)));
	*a = NULL;
	return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**arr;
	int		i;
	int		lenght;

	lenght = 0;
	i = 0;
	if (s == NULL ||
			!(arr = (char **)malloc(sizeof(*arr) * ft_count_word(s, c))))
		return (NULL);
	while (*s != '\0')
	{
		if (*s != c)
		{
			lenght = ft_count_letter(s, c);
			if ((arr[i] = ft_strnew(lenght)) == NULL)
				return (ft_delete(&arr));
			arr[i] = ft_strncpy(arr[i], s, lenght);
			arr[i][lenght] = '\0';
			i++;
			s += lenght - 1;
		}
		s++;
	}
	arr[i] = 0;
	return (arr);
}