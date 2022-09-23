/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:33:51 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/23 19:33:54 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_read_signal_client(int sig_id)
{
	(void) sig_id;
}

static int	ft_check_pid(pid_t pid)
{
	int	i;

	i = 8;
	while (i-- && kill(pid, SIGUSR2) == 0)
	{
		pause();
		usleep(100);
	}
	return (i == -1);
}

static void	ft_send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 8;
	while (i--)
	{
		if (c >> i & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		pause();
		usleep(100);
	}
}

static void	ft_send_str(pid_t pid, char *str)
{
	size_t	i;

	i = ft_strlen(str) + 1;
	while (i)
	{
		ft_send_char(pid, (unsigned char) *str);
		str++;
		i--;
	}
	ft_send_char(pid, '\n');
}

int	main(int argc, char *argv[])
{	
	pid_t	pid;
	int		i;

	i = 0;
	if (argc != 3)
	{
		ft_putstr_fd("ERROR =./client[PID-POSITIF NUMBER][STRING]\n", 1);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	ft_error_client(argv[1], pid);
	signal(SIGUSR1, ft_read_signal_client);
	if (!ft_check_pid(pid))
	{
		ft_putstr_fd("ERROR = PID INCORRECT\n", 1);
		return (1);
	}
	ft_send_str(pid, argv[2]);
	return (0);
}
