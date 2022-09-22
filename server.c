/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:12:29 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/22 18:32:30 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include "libft/libft.h"

char	*ft_strjoin_modif(char *s1, char c)
{
	int	i;
	char *r;

	i = ft_strlen(s1);
	r = malloc(sizeof(char)* (i + 2));
	ft_memmove(r , s1, i);
	r[i] = c;
	i++;
	r[i] = '\0';
	return(r);
}

static void	ft_read_signal(int sig_id, siginfo_t *info, void *context)
{
	static unsigned char		c;
	static int					i;
	static char					*str;

	(void) context;
	i += 1;
	c |= (sig_id == SIGUSR1);
		if(i < 8)
			c <<= 1;			
		if(i == 8)
		{
			if(c == '\0')
				{
					ft_putstr_fd(str, 1);
					free (str);
					str = NULL;
				}
			str = ft_strjoin_modif(str, c);
			c = 0;
			i = 0;
		}
	usleep(10);
	kill(info->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	str;

	ft_putstr_fd("Server PID: ", 1);
	ft_putnbr_fd(getpid(), 1);
	ft_putchar_fd('\n', 1);
	str.sa_flags = SA_SIGINFO;
	str.sa_sigaction = ft_read_signal;
	sigaction(SIGUSR1, &str, NULL);
	sigaction(SIGUSR2, &str, NULL);
	while (1)
		pause();
	return (0);	
}
