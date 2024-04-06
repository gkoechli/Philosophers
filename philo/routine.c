/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 11:33:57 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/11 17:15:22 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *f)
{
	if (f->offmode == 0)
	{
		pthread_mutex_lock(&f->data->death);
		pthread_mutex_lock(&f->data->print);
		if (f->data->gtfo == 0)
		{
			printf("%lld Philo %d is sleeping\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
		}
		pthread_mutex_unlock(&f->data->print);
		pthread_mutex_unlock(&f->data->death);
		check_timer(f, 1);
		if (f->offmode == 0)
			usleep(f->tt_sleep * 1000);
	}
	check_status(f);
}

void	ft_think(t_philo *f)
{
	if (f->offmode == 0)
	{
		pthread_mutex_lock(&f->data->death);
		if (f->data->gtfo == 0)
		{
			pthread_mutex_lock(&f->data->print);
			printf("%lld Philo %d is thinking\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
			pthread_mutex_unlock(&f->data->print);
		}
		pthread_mutex_unlock(&f->data->death);
		if (f->offmode == 0 && f->tt_die >= f->tt_eat * 3)
			usleep(f->tt_think * 1000);
	}
	check_status(f);
}

void	ft_eat(t_philo *f)
{
	check_status(f);
	if (f->offmode == 0)
	{
		pthread_mutex_lock(&f->data->death);
		if (f->data->gtfo == 0)
		{
			f->last_meal = timestamp();
			pthread_mutex_lock(&f->data->print);
			printf("%lld Philo %d has taken a fork\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
			printf("%lld Philo %d is eating\n",
				timestamp() - f->data->time_start, f->ph_id + 1);
			pthread_mutex_unlock(&f->data->print);
		}
		pthread_mutex_unlock(&f->data->death);
	}
}

void	ft_fork(t_philo *f, int g, int d)
{
	if ((f->ph_id + f->last) % 2 != 1)
	{
		check_status(f);
		pthread_mutex_lock(&f->data->fork[g]);
		fork_print(f);
		pthread_mutex_lock(&f->data->fork[d]);
		check_status(f);
		ft_eat(f);
		check_timer(f, 2);
		usleep(f->tt_eat * 1000);
		pthread_mutex_unlock(&f->data->fork[g]);
		pthread_mutex_unlock(&f->data->fork[d]);
		update_state(f);
	}
	else
		ft_fork_reverse(f, g, d);
}

void	ft_fork_reverse(t_philo *f, int g, int d)
{
	check_status(f);
	pthread_mutex_lock(&f->data->fork[d]);
	fork_print(f);
	pthread_mutex_lock(&f->data->fork[g]);
	check_status(f);
	ft_eat(f);
	check_timer(f, 2);
	usleep(f->tt_eat * 1000);
	pthread_mutex_unlock(&f->data->fork[d]);
	pthread_mutex_unlock(&f->data->fork[g]);
	update_state(f);
}
