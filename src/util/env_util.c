/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarchoi <sarchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 22:22:44 by sarchoi           #+#    #+#             */
/*   Updated: 2022/04/02 15:35:30 by sarchoi          ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_env(char *name_and_value)
{
	add_var(g_mini.env, name_and_value);
}

char	*find_env(char *name)
{
	return (find_var(g_mini.env, name));
}

void	remove_env(char	*name)
{
	remove_var(g_mini.env, name);
}

void	update_env(char *name, char *new_value)
{
	update_var(g_mini.env, name, new_value);
}
