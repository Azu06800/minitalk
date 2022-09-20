/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:12:29 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/19 19:13:53 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

static void	sig_handler(int sig)
{
	static int	i;
	static unsigned char	c;

	i = 0;
	c |= sig == SIGUSR1;
	if (++i == 8)
	{
		i = 0;
		ft_putchar_fd(c, 1);
		c = 0;
	}
	else
		c <<= 1;
}

int	main(void)
{
	struct sigaction	str;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	str.sa_flags = SA_SIGINFO;
	str.sa_handler = sig_handler;
	sigaction(SIGUSR1, &str, NULL);
	sigaction(SIGUSR2, &str, NULL);
	while (1)
		pause();
	return (0);
}
