/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgomez <fgomez@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:59:24 by fgomez            #+#    #+#             */
/*   Updated: 2021/06/11 09:43:05 by fgomez           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minitalk_bonus.h"

void	bin_stock(int b)
{
	static int				i = 0;
	static unsigned char	c = 0;

	c |= (b) << i++;
	if (i > 7)
	{
		if (c == '\0')
		{
			ft_putchar_fd('\n', 1);
			ft_putchar_fd(c, 1);
		}
		else
			ft_putchar_fd(c, 1);
		i = 0;
		c = 0;
	}
}

void	handle_sigurs(int sig, siginfo_t *si, void *context)
{
	(void)context;
	if (sig == SIGUSR1)
		bin_stock(0);
	else if (sig == SIGUSR2)
		bin_stock(1);
	kill(si->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sigact;

	pid = getpid();
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sigact.sa_flags = SA_SIGINFO;
	sigact.sa_sigaction = handle_sigurs;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGUSR1);
	sigaddset(&sigact.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
	{
		pause();
	}
}
