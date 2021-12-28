t_params		g_params;
unsigned long	g_start;

/*
** Number of philosophers
** Time to die
** Time to eat
** Time to sleep
** [Number of times each philosopher must eat]
*/

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*dup;
	char	*str;

	if (!s1)
		return (NULL);
	str = (char*)s1;
	i = 0;
	while (str[i] != '\0')
		i++;
	if ((dup = malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

void	ft_putnbr(int n)
{
	char	c;

	c = 0;
	if (n > 9)
	{
		c = (n / 10) + '0';
		ft_putnbr(n / 10);
	}
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	action(t_philo *philo)
{
	struct timeval time;
	unsigned long	ms = 0;

	gettimeofday(&time, NULL);
	ms = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	ft_putnbr(ms - g_start);
	write(1, " ", 1);
	ft_putnbr(philo->id);
	write(1, " ", 1);
	write(1, g_params.actions[philo->action], strlen(g_params.actions[philo->action]));
	if (philo->action == 2)
	{
		pthread_mutex_unlock(&g_params.forks[philo->left]);
		pthread_mutex_unlock(&g_params.forks[philo->right]);
		pthread_mutex_lock(&philo->eating);
	}
	if (philo->action == 5)
		g_params.dead = 1;
	if (g_params.wait[philo->action] > 0)
	{
		usleep(g_params.wait[philo->action]);
		if (philo->action == 2)
			pthread_mutex_unlock(&philo->eating);
	}
	philo->action++;
}

void	*philo_life(void *philo)
{
	while (1)
	{
		/*if (((t_philo*)philo)->meals == g_params.max_meals)
		{
			g_params.end = 1;
			break ;
		}*/
		if (((t_philo*)philo)->action == 2)
		{
			((t_philo*)philo)->meals++;
		}
		pthread_mutex_lock(&((t_philo*)philo)->active);
		action(philo);
		pthread_mutex_unlock(&((t_philo*)philo)->active);
		if (((t_philo*)philo)->action == 5)
		{
			((t_philo*)philo)->action = 0;
			((t_philo*)philo)->turn = 0;
		}
	}
	return ((void*)0);
}

void	init_philo(t_philo *philo, int id)
{
	philo->id = id;
	philo->action = 0;
	philo->last_meal = 0;
	philo->meals = 0;
	philo->turn = 0;
	philo->left = id;
	philo->right = (id == g_params.nb - 1 ? 0 : id + 1);
	pthread_mutex_init(&philo->eating, NULL);
	pthread_mutex_init(&philo->active, NULL);
}

void	init_forks(void)
{
	int		i;

	i = 0;
	if (!(g_params.forks = malloc(sizeof(pthread_mutex_t) * g_params.nb)))
		return ;
	while (i < g_params.nb)
		pthread_mutex_init(&g_params.forks[i++], NULL);
}

void	init_params(int ac, char **av)
{
	if (!(g_params.actions = malloc(sizeof(char*) * (6 + 1))))
		return ;
	if (!(g_params.wait = malloc(sizeof(int) * (6 + 1))))
		return ;
	g_params.actions[0] = ft_strdup(FORK);
	g_params.wait[0] = 0;
	g_params.actions[1] = ft_strdup(FORK);
	g_params.wait[1] = 0;
	g_params.actions[2] = ft_strdup(EATS);
	g_params.wait[2] = (atoi(av[3]) * 1000);
	g_params.actions[3] = ft_strdup(SLEEPS);
	g_params.wait[3] = (atoi(av[4]) * 1000);
	g_params.actions[4] = ft_strdup(THINKS);
	g_params.wait[4] = 0;
	g_params.actions[5] = ft_strdup(DIES);
	g_params.wait[5] = 0;
	g_params.actions[6] = NULL;
	g_params.wait[6] = -1;
	g_params.nb = atoi(av[1]);
	g_params.time_die = (atoi(av[2]) * 1000);
	g_params.max_meals = (ac == 6 ? atoi(av[5]) : -1);
	g_params.dead = 0;
	g_params.end = 0;
	init_forks();
}

int		main(int ac, char **av)
{
	pthread_t		*philosophers;
	t_philo			*philos_data;
	struct timeval	btv;
	int				i;

	i = 0;
	init_params(ac, av);
	if (!(philos = malloc(sizeof(t_philo) * (g_params.nb + 1))))
		return (0);
	while (i < g_params.nb)
	{
		init_philo(&philos[i], i);
		i++;
	}
	gettimeofday(&btv, NULL);
	g_start = (btv.tv_sec * 1000) + (btv.tv_usec / 1000);
	if (!(philosophers = malloc(sizeof(pthread_t) * (g_params.nb + 1))))
		return (-1);
	i = 0;
	while (i < g_params.nb)
	{
		printf("creatid T%d\n", i);
		pthread_create(&philosophers[i], NULL, philo_life, (void*)&philos[i]);
		//pthread_detach(philosophers[i]);
		i++;
	}
	i = 0;
/*	while (i < g_params.nb && !g_params.end)
	{
		pthread_join(philosophers[i], NULL);
		i++;
	}*/
	return (0);
}