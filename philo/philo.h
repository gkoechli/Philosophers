/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkoechli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 19:31:11 by gkoechli          #+#    #+#             */
/*   Updated: 2022/02/11 15:53:31 by gkoechli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	struct s_data	*data;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				tt_think;
	int				ph_id;
	int				meals;
	int				last;
	int				first;
	int				left;
	int				right;
	long long		last_meal;
	int				offmode;
	int				nb;
}		t_philo;

typedef struct s_data
{
	int					ph_nb;
	int					tt_die;
	int					tt_eat;
	int					tt_sleep;
	int					tt_think;
	int					nb;
	int					id;
	char				*tmp;
	int					index;
	int					wrong;
	int					stop;
	int					gtfo;
	int					meal_nb;
	long long			time_start;
	pthread_mutex_t		fork[300];
	pthread_mutex_t		death;
	pthread_mutex_t		print;
	t_philo				philo[300];
}	t_data;

/*	utils.c */

int			ft_atoi(const char *str);
void		check_status(t_philo *f);
void		check_timer(t_philo *f, int mode);
void		sleep_check(t_philo *f);
long long	timestamp(void);

/*	ft_itoa.c */

void		check_args(t_data *d, char **av, int ac);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_itoa(int n);

/*	routine.c */

void		ft_fork(t_philo *f, int i, int y);
void		ft_fork_reverse(t_philo *f, int i, int y);
void		ft_eat(t_philo *f);
void		ft_sleep(t_philo *f);
void		ft_think(t_philo *f);

/*	init.c */

void		init_args(t_data *d, char **av, int ac);
void		init_mutex(t_data *d);
void		init_philo(t_data *d);
void		fork_print(t_philo *f);
void		eat_check(t_philo *f);

/*	main.c */

void		ft_setup(t_philo *f, int i, int y);
void		update_state(t_philo *f);
void		ft_stall(t_philo *f);
void		*routine(void *d);
#endif
