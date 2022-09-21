/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:12:14 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/21 16:42:23 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

static void		read_signal_client(int sig_id)
{
		(void) sig_id;
}

static void		send_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 8;

	while(i--)
		{
			if (c >> i & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			pause();
			usleep(100);
		}
}

static void		send_str(pid_t pid, char *str)
{
	while(*str)
		{
			send_char(pid, (unsigned char) *str);
			str++;
		}
	send_char(pid, '\n');
}

int main(int argc, char *argv[])
{	
	pid_t 	pid;
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, read_signal_client);
	send_str(pid, argv[2]);
	return(0);
}
