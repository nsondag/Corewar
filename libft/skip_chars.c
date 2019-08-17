/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_chars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsondag <nsondag@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:09:39 by nsondag           #+#    #+#             */
/*   Updated: 2019/08/17 20:51:35 by nsondag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*skip_chars(char *s, char *chars)
{
	int i;

	i = 0;
	if (!s || !*s)
		return (s);
	while (chars[i] && *s)
	{
		if (*s == chars[i])
		{
			s++;
			i = 0;
		}
		else
			i++;
	}
	return (s);
}
