/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:03:24 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/11 16:37:40 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	check_status(t_philo *f)
{
	pthread_mutex_lock(&f->data->death);
	if (timestamp() - f->last_meal > f->tt_die && f->data->gtfo == 0)
	{	
		pthread_mutex_lock(&f->data->print);
		printf("%lld Philo [%d] died\n",
			timestamp() - f->data->time_start, f->ph_id + 1);
		f->data->gtfo = 1;
		pthread_mutex_unlock(&f->data->print);
	}	
	if (f->data->gtfo == 1)
		f->offmode = 1;
	pthread_mutex_unlock(&f->data->death);
}

void	check_timer(t_philo *f, int mode)
{
	if (mode == 2)
		eat_check(f);
	if (f->tt_die - (timestamp() - f->last_meal) <= 0)
	{
		pthread_mutex_lock(&f->data->death);
		if (f->data->gtfo == 0)
		{
			pthread_mutex_lock(&f->data->print);
			printf("%lld Philo [%d] died\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
			f->data->gtfo = 1;
			pthread_mutex_unlock(&f->data->print);
		}
		pthread_mutex_unlock(&f->data->death);
		f->offmode = 1;
		mode = 0;
		return ;
	}
	if (mode == 1)
		sleep_check(f);
}

void	sleep_check(t_philo *f)
{
	if (timestamp() - f->last_meal + f->tt_sleep > f->tt_die)
	{		
		usleep((f->tt_die - (timestamp() - f->last_meal)) * 1000);
		pthread_mutex_lock(&f->data->death);
		if (f->data->gtfo == 0)
		{
			pthread_mutex_lock(&f->data->print);
			printf("%lld Philo [%d] died\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
			f->data->gtfo = 1;
			pthread_mutex_unlock(&f->data->print);
		}
		pthread_mutex_unlock(&f->data->death);
		f->offmode = 1;
	}
}
