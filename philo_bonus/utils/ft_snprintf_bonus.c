/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_snprintf_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khorike <khorike@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:46:25 by khorike           #+#    #+#             */
/*   Updated: 2024/01/29 13:09:24 by khorike          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*tmp_dest;
	const char	*tmp_src;
	size_t		i;

	if (!dest && !src)
		return (NULL);
	tmp_dest = (char *)dest;
	tmp_src = (const char *)src;
	i = 0;
	while (i < n)
	{
		tmp_dest[i] = tmp_src[i];
		i++;
	}
	return (dest);
}

// static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
// {
// 	size_t	srclen;

// 	srclen = ft_strlen(src);
// 	if (srclen + 1 < dstsize)
// 	{
// 		ft_memcpy(dst, src, srclen + 1);
// 		dst[srclen] = '\0';
// 	}
// 	else if (dstsize != 0)
// 	{
// 		ft_memcpy(dst, src, dstsize - 1);
// 		dst[dstsize - 1] = '\0';
// 	}
// 	return (srclen);
// }

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	size_t	len;

	len = 0;
	while (len < maxlen && s[len])
		len++;
	return (len);
}

static size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strnlen(dst, dstsize);
	if (dstlen == dstsize)
		return (dstsize + srclen);
	if (dstsize < srclen + dstlen + 1)
	{
		ft_memcpy(dst + dstlen, src, dstsize - dstlen - 1);
		dst[dstsize - 1] = '\0';
	}
	else
		ft_memcpy(dst + dstlen, src, srclen + 1);
	return (dstlen + srclen);
}

char	*ft_snprintf(char *str, int n)
{
	char	*num;
	char	*r_str;

	num = ft_itoa(n);
	r_str = ft_calloc(sizeof(char), 16);
	ft_strlcat(r_str, str, ft_strlen(str) + 1);
	ft_strlcat(r_str, num, ft_strlen(str) + ft_strlen(num) + 1);
	free(num);
	num = NULL;
	return (r_str);
}