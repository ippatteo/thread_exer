# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <time.h>
#include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>



typedef struct s_philo
{
	int	id_philo;	//numero filosofi
	int meal;
	int sated;
	int dead;
	int	t_die;	//time to die
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat;
	int	end_philo;
	pthread_mutex_t *fork_l; //how meny time they have to eat
	pthread_mutex_t *fork_r;
	struct s_data *data;
	pthread_mutex_t	lock_dead;
	
}	t_philo;

typedef struct s_data
{
	int	n_philo;	//numero filosofi
	int	t_die;	//time to die
	int sms_flag;
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat; //how meny time they have to eat
	int end;
	int sated_condition;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_t *threads;
	pthread_mutex_t lock;
	uint64_t	time;
}	t_data;

void math_sated(t_data *data);
void		*atac(void *ptr);
int			ft_atoi(char *str);
int			error(t_data *data);
int			ft_isdigit(int c);
int			ft_usleep(uint64_t time);
void		init(t_data *data, int ac, char **av);
void 		init_philos(t_data *data);
void 		init_fork(t_data *data);
void 		init_threads(t_data *data);
void		ft_eat(t_philo *philo, pthread_t delorian);
void 		ft_thinking(t_philo *philo);
void 		*ft_routine(void *ptr);
void		alloc(t_data *data);
void		sms(t_data *data, char *str, int id);
uint64_t	get_time(void);
void	free_all(t_data *data);
int ft_kill_all(t_data *data, int i);

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <time.h>
#include <sys/time.h>
# include <sys/types.h>
# include <stdint.h>
# include <pthread.h>
# include <stdlib.h>



typedef struct s_philo
{
	int	id_philo;	//numero filosofi
	int meal;
	int sated;
	int dead;
	int	t_die;	//time to die
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat;
	int	end_philo;
	pthread_mutex_t *fork_l; //how meny time they have to eat
	pthread_mutex_t *fork_r;
	struct s_data *data;
	pthread_mutex_t	lock_dead;
	
}	t_philo;

typedef struct s_data
{
	int	n_philo;	//numero filosofi
	int	t_die;	//time to die
	int sms_flag;
	int	t_eat;	//time to eat
	int	t_sleep;	//time to sleep
	int	n_eat; //how meny time they have to eat
	int end;
	int sated_condition;
	t_philo *philo;
	pthread_mutex_t *forks;
	pthread_t *threads;
	pthread_mutex_t lock;
	uint64_t	time;
}	t_data;

void math_sated(t_data *data);
void		*atac(void *ptr);
int			ft_atoi(char *str);
int			error(t_data *data);
int			ft_isdigit(int c);
int			ft_usleep(uint64_t time);
void		init(t_data *data, int ac, char **av);
void 		init_philos(t_data *data);
void 		init_fork(t_data *data);
void 		init_threads(t_data *data);
void		ft_eat(t_philo *philo, pthread_t delorian);
void 		ft_thinking(t_philo *philo);
void 		*ft_routine(void *ptr);
void		alloc(t_data *data);
void		sms(t_data *data, char *str, int id);
uint64_t	get_time(void);
void	free_all(t_data *data);
int ft_kill_all(t_data *data, int i);

vvoid	init(t_data *data, int ac, char **av)
{
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	data->time = get_time();
	data->sms_flag = 0;
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = 0;
}

void init_philos(t_data *data)
{
	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id_philo = i + 1;
		data->philo[i].t_die = data->t_die;
		data->philo[i].t_eat = data->t_eat;
		data->philo[i].t_sleep = data->t_sleep;
		data->philo[i].n_eat = data->n_eat;
		data->philo[i].meal = 0;
		data->philo[i].sated = 0;
		data->philo[i].dead = 0;
		data->philo[i].end_philo = 0;
		data->philo[i].data = data;
		pthread_mutex_init(&data->philo[i].lock_dead, NULL);
		i++;
	}
}

void init_fork(t_data *data)
{
	int	i;
	
	i = 0;
	while(i < data->n_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->philo[0].fork_l = &data->forks[0];
	data->philo[0].fork_r = &data->forks[data->n_philo - 1];
	i = 1;
	while (i < data->n_philo)
	{
		data->philo[i].fork_l = &data->forks[i];
		data->philo[i].fork_r = &data->forks[i - 1];
		i++;
	}
}

void init_threads(t_data *data)
{
	pthread_t pula;
	int i;
	
	data->end = 0;
	i = 0;
	pthread_mutex_init(&data->lock, NULL);
	pthread_create(&pula, NULL, &atac, data);
	while (i < data->n_philo)
	{
		pthread_create(&data->threads[i], NULL, &ft_routine, &data->philo[i]);
		i++;
		usleep(1000);//qui ritardi i filosofi
	}
	i = 0;
	while(i < data->n_philo)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	pthread_join(pula, NULL);
}


int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void ft_eat(t_philo *philo, pthread_t delorian)
{
	pthread_mutex_lock(philo->fork_l);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_mutex_lock(philo->fork_r);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_join(delorian, NULL);
	sms(philo->data, "is eating", philo->id_philo);
	usleep(philo->t_eat);
	pthread_create(&delorian, NULL, &timer, &philo);
	 philo->meal++;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}
void ft_sleeping(t_philo *philo)
{
		
	if (philo->t_sleep >= philo->t_die)
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		usleep(philo->t_die - philo->t_sleep);
		pthread_mutex_lock(&philo->lock_dead);
		philo->dead = 1;
		philo->end_philo = 1;
		pthread_mutex_lock(&philo->lock_dead);
		printf(" pipolo\n");
	}
	else
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		ft_usleep(philo->t_sleep);
	}
	
}

int is_it_sated(t_philo *philo)
{
	 if(philo->meal == philo->data->n_eat && philo->data->n_eat > 0)
		 {
			pthread_mutex_lock(&philo->lock_dead);
			philo->sated = 1;
			philo->end_philo = 1;
			pthread_mutex_unlock(&philo->lock_dead);
			return (1) ;
		 }
	else
		return (0);
}
void *ft_routine(void *ptr)
{
	t_philo *philo;
	pthread_t delorian;

	philo = (t_philo *)ptr;
	pthread_mutex_init(&philo->lock_dead, NULL);
	while (philo->dead == 0 && philo->data->end == 0)
	{
		pthread_create(&delorian, NULL, &timer, &philo);
		ft_eat(philo, delorian);
		 if(is_it_sated(philo))
			break ;
		if (philo->end_philo == 1 || philo->data->end == 1)
			break ;
		ft_sleeping(philo);
		if (philo->end_philo == 0 && philo->data->end == 0)
			sms(philo->data, "is thinking", philo->id_philo); 
	}
	pthread_join(delorian, NULL);
	pthread_mutex_destroy(&philo->lock_dead);
	return (NULL);
}
int ft_atoi(char *str)
{
	long int r;
	int s;
	int i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		return (-1);
	return (r * s);
}

int error(t_data *data)
{
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0 || data->n_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void alloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
}

uint64_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void sms(t_data *data, char *str, int id)
{
	if(data->sms_flag == 0)
		printf("%ld philo n%d %s\n", (get_time() - data->time), id, str);
}

void free_all(t_data *data)
{	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->philo);
	free(data->forks);
	free(data->threads);
}

void math_sated(t_data *data)
{
	int i;
	
	i = 0;
	data->sated_condition = 0;
	while (i < data->n_philo)
	{
		data->sated_condition += data->philo[i].id_philo;
		i++;
	}
}
int ft_kill_all(t_data *data, int i)
{
	if (data->philo[i].dead == 1)
	{
		data->end = 1;
		sms(data, "is dead", data->philo[i].id_philo);
		return (1);
	}
	else
	{
		return (0);
	}
		
}

void *atac(void *ptr)
{
	t_data	*data;
	int		i;
	int 	a;
	
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{	pthread_mutex_lock(&data->philo[i].lock_dead);
			if(data->philo[i].end_philo == 1)
			{
				if (ft_kill_all(data, i))
				{
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					return (NULL);
				}
				if(data->philo[i].sated == 1)
				{
					a = 0;
					while (a < data->n_philo && data->philo[a].sated == 1)
						a++;
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					if (a > data->n_philo)
						return (NULL);
				}
				pthread_mutex_unlock(&data->philo[i].lock_dead);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_fork(&data);
		init_threads(&data);
		free_all(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
void	*timer(void *ptr)
{
	t_philo		*philo;
	uint16_t	start;
	philo = (t_philo *)ptr;
	while(philo->end_philo == 0 && philo->data->end == 0)
	{
		usleep(5);
		start = get_time() - philo->data->time;
		if (start > (u_int64_t)philo->data->t_die)
			{
				pthread_mutex_lock(&philo->lock_dead);
				philo->dead = 1;
				philo->end_philo = 1;
				printf("\n killed\n");
				pthread_mutex_lock(&philo->lock_dead);
			}
	}
	return(NULL);
}

int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void ft_eat(t_philo *philo, pthread_t delorian)
{
	pthread_mutex_lock(philo->fork_l);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_mutex_lock(philo->fork_r);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_join(delorian, NULL);
	sms(philo->data, "is eating", philo->id_philo);
	usleep(philo->t_eat);
	pthread_create(&delorian, NULL, &timer, &philo);
	 philo->meal++;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}
void ft_sleeping(t_philo *philo)
{
		
	if (philo->t_sleep >= philo->t_die)
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		usleep(philo->t_die - philo->t_sleep);
		pthread_mutex_lock(&philo->lock_dead);
		philo->dead = 1;
		philo->end_philo = 1;
		pthread_mutex_unlock(&philo->lock_dead);
		printf(" pipolo\n");
	}
	else
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		ft_usleep(philo->t_sleep);
	}
	
}

int is_it_sated(t_philo *philo)
{
	 if(philo->meal == philo->data->n_eat && philo->data->n_eat > 0)
		 {
			pthread_mutex_lock(&philo->lock_dead);
			philo->sated = 1;
			philo->end_philo = 1;
			pthread_mutex_unlock(&philo->lock_dead);
			return (1) ;
		 }
	else
		return (0);
}
void *ft_routine(void *ptr)
{
	t_philo *philo;
	pthread_t delorian;

	philo = (t_philo *)ptr;
	while (philo->dead == 0 && philo->data->end == 0)
	{
		pthread_create(&delorian, NULL, &timer, &philo);
		ft_eat(philo, delorian);
		 if(is_it_sated(philo))
			break ;
		if (philo->end_philo == 1 || philo->data->end == 1)
			break ;
		ft_sleeping(philo);
		if (philo->end_philo == 0 && philo->data->end == 0)
			sms(philo->data, "is thinking", philo->id_philo); 
	}
	pthread_join(delorian, NULL);
	pthread_mutex_destroy(&philo->lock_dead);
	return (NULL);
}
int ft_atoi(char *str)
{
	long int r;
	int s;
	int i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		return (-1);
	return (r * s);
}

int error(t_data *data)
{
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0 || data->n_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void alloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
}

uint64_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void sms(t_data *data, char *str, int id)
{
	if(data->sms_flag == 0)
		printf("%ld philo n%d %s\n", (get_time() - data->time), id, str);
}

void free_all(t_data *data)
{	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->philo);
	free(data->forks);
	free(data->threads);
}

void math_sated(t_data *data)
{
	int i;
	
	i = 0;
	data->sated_condition = 0;
	while (i < data->n_philo)
	{
		data->sated_condition += data->philo[i].id_philo;
		i++;
	}
}
int ft_kill_all(t_data *data, int i)
{
	if (data->philo[i].dead == 1)
	{
		data->end = 1;
		sms(data, "is dead", data->philo[i].id_philo);
		return (1);
	}
	else
	{
		return (0);
	}
		
}

void *atac(void *ptr)
{
	t_data	*data;
	int		i;
	int 	a;
	
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{	pthread_mutex_lock(&data->philo[i].lock_dead);
			if(data->philo[i].end_philo == 1)
			{
				if (ft_kill_all(data, i))
				{
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					return (NULL);
				}
				if(data->philo[i].sated == 1)
				{
					a = 0;
					while (a < data->n_philo && data->philo[a].sated == 1)
						a++;
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					if (a > data->n_philo)
						return (NULL);
				}
				pthread_mutex_unlock(&data->philo[i].lock_dead);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_fork(&data);
		init_threads(&data);
		free_all(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}

void	*timer(void *ptr)
{
	t_philo		*philo;
	uint16_t	start;
	philo = (t_philo *)ptr;
	while(philo->end_philo == 0 && philo->data->end == 0)
	{
		usleep(5);
		start = get_time() - philo->data->time;
		if (start > (u_int64_t)philo->data->t_die)
			{
				pthread_mutex_lock(&philo->lock_dead);
				philo->dead = 1;
				philo->end_philo = 1;
				printf("\n killed\n");
				pthread_mutex_lock(&philo->lock_dead);
			}
	}
	return(NULL);
}

int	ft_usleep(uint64_t time)
{
	uint64_t	start;

	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return (0);
}

void ft_eat(t_philo *philo, pthread_t delorian)
{
	pthread_mutex_lock(philo->fork_l);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_mutex_lock(philo->fork_r);
	sms(philo->data, "has taken a fork", philo->id_philo);
	pthread_join(delorian, NULL);
	sms(philo->data, "is eating", philo->id_philo);
	usleep(philo->t_eat);
	pthread_create(&delorian, NULL, &timer, &philo);
	 philo->meal++;
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}
void ft_sleeping(t_philo *philo)
{
		
	if (philo->t_sleep >= philo->t_die)
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		usleep(philo->t_die - philo->t_sleep);
		pthread_mutex_lock(&philo->lock_dead);
		philo->dead = 1;
		philo->end_philo = 1;
		pthread_mutex_unlock(&philo->lock_dead);
		printf(" pipolo\n");
	}
	else
	{
		sms(philo->data, "is sleeping", philo->id_philo);
		ft_usleep(philo->t_sleep);
	}
	
}

int is_it_sated(t_philo *philo)
{
	 if(philo->meal == philo->data->n_eat && philo->data->n_eat > 0)
		 {
			pthread_mutex_lock(&philo->lock_dead);
			philo->sated = 1;
			philo->end_philo = 1;
			pthread_mutex_unlock(&philo->lock_dead);
			return (1) ;
		 }
	else
		return (0);
}
void *ft_routine(void *ptr)
{
	t_philo *philo;
	pthread_t delorian;

	philo = (t_philo *)ptr;
	while (philo->dead == 0 && philo->data->end == 0)
	{
		pthread_create(&delorian, NULL, &timer, &philo);
		ft_eat(philo, delorian);
		 if(is_it_sated(philo))
			break ;
		if (philo->end_philo == 1 || philo->data->end == 1)
			break ;
		ft_sleeping(philo);
		if (philo->end_philo == 0 && philo->data->end == 0)
			sms(philo->data, "is thinking", philo->id_philo); 
	}
	pthread_join(delorian, NULL);
	pthread_mutex_destroy(&philo->lock_dead);
	return (NULL);
}
int ft_atoi(char *str)
{
	long int r;
	int s;
	int i;

	r = 0;
	s = 1;
	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		r = r * 10 + str[i++] - '0';
	}
	if (r > 2147483647 || r < -2147483647)
		return (-1);
	return (r * s);
}

int error(t_data *data)
{
	if (data->n_philo < 0 || data->t_die < 0 || data->t_eat < 0 || data->t_sleep < 0 || data->n_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	else
		return (0);
}

int ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void alloc(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->n_philo);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->n_philo);
	data->threads = malloc(sizeof(pthread_t) * data->n_philo);
}

uint64_t get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}

void sms(t_data *data, char *str, int id)
{
	if(data->sms_flag == 0)
		printf("%ld philo n%d %s\n", (get_time() - data->time), id, str);
}

void free_all(t_data *data)
{	int i;
	
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(data->philo[i].fork_l);
		pthread_mutex_destroy(data->philo[i].fork_r);
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	free(data->philo);
	free(data->forks);
	free(data->threads);
}

void math_sated(t_data *data)
{
	int i;
	
	i = 0;
	data->sated_condition = 0;
	while (i < data->n_philo)
	{
		data->sated_condition += data->philo[i].id_philo;
		i++;
	}
}

int ft_kill_all(t_data *data, int i)
{
	if (data->philo[i].dead == 1)
	{
		data->end = 1;
		sms(data, "is dead", data->philo[i].id_philo);
		return (1);
	}
	else
	{
		return (0);
	}
		
}

void *atac(void *ptr)
{
	t_data	*data;
	int		i;
	int 	a;
	
	data = (t_data *)ptr;
	while (1)
	{
		i = 0;
		while (i < data->n_philo)
		{	pthread_mutex_lock(&data->philo[i].lock_dead);
			if(data->philo[i].end_philo == 1)
			{
				if (ft_kill_all(data, i))
				{
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					return (NULL);
				}
				if(data->philo[i].sated == 1)
				{
					a = 0;
					while (a < data->n_philo && data->philo[a].sated == 1)
						a++;
					pthread_mutex_unlock(&data->philo[i].lock_dead);
					if (a > data->n_philo)
						return (NULL);
				}
				pthread_mutex_unlock(&data->philo[i].lock_dead);
			}
			i++;
		}
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data	data;
	
	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (error(&data))
			return (0);
		alloc(&data);
		init_philos(&data);
		init_fork(&data);
		init_threads(&data);
		free_all(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
