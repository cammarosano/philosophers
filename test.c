#include <unistd.h>
#include <stdio.h>
# include <sys/time.h>

void	ft_putnbr(long n)
{
	char digit;

	if (n < 10)
	{
		digit = n + '0';
		write(1, &digit, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		digit = n % 10 + '0';
		write(1, &digit, 1);
	}
}

// returns elapsed time from t1 to t2, in ms 
long	time_diff(struct timeval t1, struct timeval t2)
{
	long	diff;

	diff = (t2.tv_sec - t1.tv_sec) * 1000;
	diff += (t2.tv_usec - t1.tv_usec) / 1000;
	return (diff);
}

void	sleep_well(int time_ms)
{
	struct timeval start;
	struct timeval now;
	long			elapsed_time;
	long			time_2_sleep;

	gettimeofday(&start, NULL);
	elapsed_time = 0;
	time_2_sleep = time_ms * 1000;
	// int i = 0;
	while (elapsed_time < time_2_sleep)
	{
		usleep(50);
		gettimeofday(&now, NULL);
		elapsed_time = now.tv_sec * 1000000 + now.tv_usec - (start.tv_sec * 1000000 + start.tv_usec); 
		// i++;
	}
		// printf("%d cycles\n", i);
}

void	altern_printf(long timestamp)
{
	ft_putnbr(timestamp);
	write(1, " hello\n", 7);
}

int	main(void)
{
	struct timeval start;
	struct timeval now;
	long			timestamp;

	gettimeofday(&start, NULL);

	while (1)
	{
		gettimeofday(&now, NULL);
		timestamp = time_diff(start, now); 
		printf("%ld hello\n", timestamp);
		// altern_printf(timestamp);
		// usleep(1000 * 1000);
		sleep_well(1000);

	}



}