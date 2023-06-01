/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 16:14:44 by nihamdan          #+#    #+#             */
/*   Updated: 2023/06/01 17:14:59 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*ft_realloc(char *string, char c)
{
	char	*tmp;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(string);
	tmp = malloc(sizeof(char) * (len + 2));
	while (++i < len)
		tmp[i] = string[i];
	tmp[i++] = c;
	tmp[i] = '\0';
	if (string)
	{
		free(string);
		string = NULL;
	}
	return (tmp);
}

void	receive_string(int signum, siginfo_t *info, void *context)
{
	static char		c;
	static int		byte;
	static char		*string;
	static int		i;

	(void) context;
	if (signum == SIGUSR1)
		c |= 1 << byte;
	if (byte++ == 7)
	{
		string = ft_realloc(string, c);
		if (c == '\0')
		{
			ft_printf("%s", string);
			free(string);
			string = NULL;
			i = 0;
			kill(info->si_pid, SIGUSR1);
		}
		c = 0;
		byte = 0;
	}
	return ;
}

int	main(void)
{
	struct sigaction	sa;

	ft_printf("PID is %d.\n", getpid());
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = receive_string;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
