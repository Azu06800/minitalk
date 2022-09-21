/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:12:29 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/21 16:44:05 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

static void	read_signal(int sig_id, siginfo_t *info, void *context)
{
	static unsigned char		c;
	static int		i;


	(void) context;
	i += 1;
	c |= (sig_id == SIGUSR1);
		if(i < 8)
			c <<= 1;
		if(i == 8)
		{
			write(1, &c,1);
			c = 0;
			i = 0;
		}
	usleep(100);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	str;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	str.sa_flags = SA_SIGINFO;
	str.sa_sigaction = read_signal;
	sigaction(SIGUSR1, &str, NULL);
	sigaction(SIGUSR2, &str, NULL);
	while (1)
		pause();
	return (0);	
}
