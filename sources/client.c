/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:39 by nihamdan          #+#    #+#             */
/*   Updated: 2023/06/01 17:39:22 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static void	ft_read_signal(int sig_id)
{
	(void) sig_id;
}

void	send_string(pid_t pid, char *string)
{
	int	len;
	int	byte;
	int	i;

	len = ft_strlen(string) + 1;
	i = -1;
	while (++i < len)
	{
		byte = 0;
		while (byte < 8)
		{
			if (string[i] >> byte++ & 1)
				kill(pid, SIGUSR1);
			else
				kill(pid, SIGUSR2);
			usleep(100);
		}
	}
	return ;
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (!check_error(argc, argv))
		return (0);
	pid = ft_atoi(argv[1]);
	signal(SIGUSR1, ft_read_signal);
	send_string(pid, argv[2]);
	return (0);
}
