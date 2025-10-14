/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpinho-c <cpinho-c@student.42.fr>          #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-12-17 13:05:26 by cpinho-c          #+#    #+#             */
/*   Updated: 2024-12-17 13:05:26 by cpinho-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	dest = (char *)malloc (s_len + 1);
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char) c;
	i = 0;
	if (!s && cc != '\0')
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == cc)
			return ((char *) s + i);
		i++;
	}
	if (cc == '\0')
		return ((char *) s + i);
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	f_len;
	size_t	i;
	size_t	j;

	f_len = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	j = 0;
	str = (char *)malloc(f_len + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[f_len] = '\0';
	free(s1);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	r_len;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	r_len = ft_strlen(s);
	if (start >= r_len)
		r_len = 0;
	else if (len < r_len - start)
		r_len = len;
	else
		r_len = r_len - start;
	sub = (char *)malloc(r_len + 1);
	if (sub == NULL)
		return (NULL);
	while (i < r_len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[r_len] = '\0';
	return (sub);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
