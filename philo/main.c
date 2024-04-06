/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 12:00:03 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/11 17:14:16 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

struct	s_data;

void	*routine(void *d)
{
	t_philo	*f;

	f = (t_philo *)d;
	f->left = f->ph_id;
	f->offmode = 0;
	if (f->left % 2 != 0)
		usleep(f->tt_eat / 10 * 1000);
	f->right = f->left + 1;
	if (f->left == f->nb - 1)
		f->right = 0;
	while (f->offmode == 0)
	{
		ft_setup(f, f->left, f->right);
		ft_stall(f);
	}
	return (d);
}

void	ft_setup(t_philo *f, int g, int d)
{
	pthread_mutex_lock(&f->data->death);
	if (timestamp() - f->last_meal >= f->tt_die && f->data->gtfo == 0)
	{
		pthread_mutex_lock(&f->data->print);
		printf("%lld Philo %d died\n",
			timestamp() - f->data->time_start, f->ph_id + 1);
		f->data->gtfo = 1;
		pthread_mutex_unlock(&f->data->print);
	}
	pthread_mutex_unlock(&f->data->death);
	check_status(f);
	ft_fork(f, g, d);
	ft_sleep(f);
	ft_think(f);
}

void	ft_stall(t_philo *f)
{
	if (f->nb % 2 == 1)
	{
		if (f->tt_die / 3 < f->tt_eat
			&& f->tt_die > (f->tt_eat + f->tt_sleep))
			usleep((f->tt_die - f->tt_eat - f->tt_sleep) * 1000);
		else if (f->left % 2 == 0)
			usleep(100);
	}
	else
	{
		if (f->tt_die / 2 < f->tt_eat
			&& f->tt_die > (f->tt_eat + f->tt_sleep))
			usleep((f->tt_die - f->tt_eat - f->tt_sleep) * 1000);
	}
}

void	update_state(t_philo *f)
{
	pthread_mutex_lock(&f->data->death);
	f->meals--;
	if (f->meals == 0)
		f->data->stop--;
	if (f->data->stop == 0)
		f->data->gtfo = 1;
	if (f->data->gtfo == 1)
		f->offmode = 1;
	if (f->first == 2)
		f->first = 0;
	pthread_mutex_unlock(&f->data->death);
}

int	main(int ac, char **av)
{
	int		i;
	t_data	d;

	i = -1;
	if (ac != 5 && ac != 6)
		return (write(1, "Invalid number of arguments\n", 28));
	init_args(&d, av, ac);
	d.time_start = timestamp();
	if (d.ph_nb < 1 || d.tt_die < 1 || d.tt_eat < 1
		|| d.ph_nb > 250 || d.tt_sleep < 1 || d.wrong == 1)
		return (write(1, "Invalid argument\n", 17));
	if (d.ph_nb == 1)
	{
		printf("%lld Philo 1 has taken a fork\n", timestamp() - d.time_start);
		usleep(d.tt_die * 1000);
		return (printf("%lld Philo 1 died\n", timestamp() - d.time_start));
	}
	init_mutex(&d);
	init_philo(&d);
	while (++i < d.ph_nb)
		pthread_create(&d.philo[i].thread_id, NULL, routine, &d.philo[i]);
	i = -1;
	while (++i < d.ph_nb)
		pthread_join(d.philo[i].thread_id, NULL);
	return (0);
}
