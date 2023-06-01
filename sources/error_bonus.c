/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nihamdan <nihamdan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:22:54 by nihamdan          #+#    #+#             */
/*   Updated: 2023/06/01 17:23:09 by nihamdan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk_bonus.h"

int	test_pid(pid_t pid)
{
	if (kill(pid, 0) == 0)
		return (1);
	else
	{
		ft_printf("PID is invalid\n");
		return (0);
	}
}

int	check_error(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
	{
		ft_printf("Client usage = [PID][String to send]\n");
		return (0);
	}
	while (argv[1][i])
	{
		if (!ft_isdigit(argv[1][i++]))
		{
			ft_printf("PID must be digit numbers\n");
			return (0);
		}
	}
	if (!test_pid(ft_atoi(argv[1])))
		return (0);
	return (1);
}
