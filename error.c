/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhamdan <nhamdan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 19:08:10 by nhamdan           #+#    #+#             */
/*   Updated: 2022/09/23 19:24:31 by nhamdan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_error_client(char *argv, int pid)
{
	while (*argv)
	{
		if (!(ft_isdigit(*argv)) || pid <= 0)
		{
			ft_putstr_fd ("ERROR = PID MUST BE POSITIF NUMBER\n", 1);
			exit (EXIT_FAILURE);
		}
		argv++;
	}
}
