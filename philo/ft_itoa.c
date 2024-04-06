/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:43:42 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/10 19:00:51 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_intlen(size_t n)
{
	int	i;

	i = 1;
	while ((n / 10) > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_fill(long n, int sign, int i, int intlen)
{
	char		*str;
	long int	u;

	u = n;
	if (n < 0)
	{
		u = (n * -1);
		i = 1;
		sign = 1;
	}
	intlen = ft_intlen(u) + i;
	str = malloc(sizeof(char) * intlen + 1);
	if (str == NULL)
		return (NULL);
	str[intlen] = '\0';
	while (intlen > 0)
	{
		str[--intlen] = '0' + u % 10;
		u = u / 10;
	}
	if (sign == 1)
		str[intlen] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		sign;
	int		intlen;
	long	imin;

	sign = 0;
	i = 0;
	intlen = 0;
	imin = (long)n;
	return (ft_fill(imin, sign, i, intlen));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void	check_args(t_data *d, char **av, int ac)
{
	d->tmp = ft_itoa(d->ph_nb);
	if (ft_strcmp(d->tmp, av[1]) != 0)
		d->wrong = 1;
	free(d->tmp);
	d->tmp = ft_itoa(d->tt_die);
	if (ft_strcmp(d->tmp, av[2]) != 0)
		d->wrong = 1;
	free(d->tmp);
	d->tmp = ft_itoa(d->tt_eat);
	if (ft_strcmp(d->tmp, av[3]) != 0)
		d->wrong = 1;
	free(d->tmp);
	d->tmp = ft_itoa(d->tt_sleep);
	if (ft_strcmp(d->tmp, av[4]) != 0)
		d->wrong = 1;
	free(d->tmp);
	if (ac == 6)
	{
		d->tmp = ft_itoa(d->meal_nb);
		if (ft_strcmp(d->tmp, av[5]) != 0)
			d->wrong = 1;
		free(d->tmp);
	}
}
