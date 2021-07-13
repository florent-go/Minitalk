/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:59:27 by fgomez            #+#    #+#             */
/*   Updated: 2021/06/11 09:47:01 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk.h"

static int	g_sig = 0;

void	ft_error(char *str)
{
	ft_putstr_fd("Error\n", 1);
	ft_putstr_fd(str, 1);
	exit(1);
}

void	g_glob(int i)
{
	(void)i;
	g_sig = 1;
}

void	ft_binary(char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_sig = 0;
		usleep(100);
		if ((c >> i) & 1)
		{
			if (kill(pid, SIGUSR2) == -1)
				ft_error("Can't kill\n");
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				ft_error("Can't kill\n");
		}
		i++;
		while (!g_sig)
			;
	}
}

int	main(int ac, char **av)
{
	int		i;
	pid_t	pid;

	i = -1;
	g_sig = 0;
	signal(SIGUSR1, g_glob);
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		while (av[2][++i] != '\0')
			ft_binary(av[2][i], pid);
		ft_binary(0, pid);
	}
	else
		ft_putstr_fd("Error\n", 1);
	return (0);
}
