/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:41:37 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/11 17:16:07 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_data *d, char **av, int ac)
{
	d->wrong = 0;
	d->tmp = NULL;
	d->ph_nb = ft_atoi(av[1]);
	d->tt_die = ft_atoi(av[2]);
	d->tt_eat = ft_atoi(av[3]);
	d->tt_sleep = ft_atoi(av[4]);
	d->tt_think = 0;
	if (ac == 6)
		d->meal_nb = ft_atoi(av[5]);
	else
		d->meal_nb = -1;
	check_args(d, av, ac);
	d->gtfo = 0;
	d->stop = d->ph_nb;
	d->time_start = timestamp();
	if (d->tt_eat > d->tt_sleep && d->ph_nb % 2 == 1)
		d->tt_think = d->tt_eat - d->tt_sleep;
}

void	init_mutex(t_data *d)
{
	int	i;

	i = -1;
	while (++i < 250)
		pthread_mutex_init(&d->fork[i], NULL);
	pthread_mutex_init(&d->print, NULL);
	pthread_mutex_init(&d->death, NULL);
}

void	init_philo(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->ph_nb)
	{
		d->nb = i;
		if (i == 0 && d->ph_nb == 3)
			d->philo[i].first = 2;
		else
			d->philo[i].first = 0;
		if (i == d->ph_nb - 1 && d->ph_nb % 2 == 1)
			d->philo[i].last = 2;
		else
			d->philo[i].last = 0;
		d->philo[i].nb = d->ph_nb;
		d->philo[i].ph_id = i;
		d->philo[i].tt_die = d->tt_die;
		d->philo[i].tt_think = d->tt_think;
		d->philo[i].tt_eat = d->tt_eat;
		d->philo[i].tt_sleep = d->tt_sleep;
		d->philo[i].meals = d->meal_nb;
		d->philo[i].last_meal = d->time_start;
		d->philo[i].data = d;
		i++;
	}
}

void	fork_print(t_philo *f)
{
	pthread_mutex_lock(&f->data->death);
	if (f->data->gtfo == 0)
	{
		pthread_mutex_lock(&f->data->print);
		printf("%lld Philo %d has taken a fork\n",
			timestamp() - f->data->time_start, f->ph_id + 1);
		pthread_mutex_unlock(&f->data->print);
	}
	pthread_mutex_unlock(&f->data->death);
}

void	eat_check(t_philo *f)
{
	if (f->tt_eat > f->tt_die)
	{
		usleep(f->tt_die * 1000);
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
	}
}
