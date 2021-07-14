#include "philo.h"

// -1 means wrong format
// skips spaces, tolerates one "+", demands at least a digit,
// does not accept characters after the digits
static int	parse_positive_int(char *str)
{
	int	nbr;

	if (!str || !*str)
		return (-1);
	while (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
	 	|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '+')
		str++;
	if (!(*str >= '0' && *str <= '9'))
		return (-1);
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	if (*str != '\0')
		return (-1);
	return (nbr);
}

static int	check_if_positive(t_params *params)
{
	if (params->n_philos < 0)
		return (0);
	if (params->time_to_die < 0)
		return (0);
	if (params->time_to_eat < 0)
		return (0);
	if (params->time_to_sleep < 0)
		return (0);
	if (params->meals_2_eat < 0)
		return (0);
	return (1);
}

// all parameters must be non-negative.
// n_philos must be >= 1
// if there is a 5th parameter, meals_2_eat must be >= 1
int	validate_args(t_params *params, int argc)
{
	if (!check_if_positive(params))
	{
		printf("Bad argument(s)\n");
		return (0);
	}
	if (params->n_philos == 0)
	{
		printf("No philosophers... no forks... no simulation :(\n");
		return (0);
	}
	if (argc == 6 && params->meals_2_eat == 0)
	{
		printf("Optional argument n_times_each_philo_must_eat must be > 0\n");
		printf("(or just consider simulation is over)\n");
		return (0);
	}
	return (1);
}

// parsers parameters. Returns 0 if parameters are valid, -1 otherwise.
int	parse_params(int argc, char **argv, t_params *params)
{
	if (argc < 5 || argc > 6)
	{
		printf("Wrong number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (-1);
	}
	params->n_philos = parse_positive_int(argv[1]);
	params->time_to_die = parse_positive_int(argv[2]);
	params->time_to_eat = parse_positive_int(argv[3]);
	params->time_to_sleep = parse_positive_int(argv[4]);
	params->meals_2_eat = 0;
	if (argc == 6)
		params->meals_2_eat = parse_positive_int(argv[5]);
	if (!validate_args(params, argc))	
		return (-1);
	return (0);
}
