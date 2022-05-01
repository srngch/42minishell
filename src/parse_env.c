/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpak <cpak@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:41:00 by cpak              #+#    #+#             */
/*   Updated: 2022/04/29 19:38:26 by cpak             ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_str(char *str, int *idx, int *sep)
{
	int	len;

	*sep = 0;
	len = 0;
	set_quotes_flag(str[*idx], sep);
	if (*sep != 0)
	{
		len = check_quote_closed(str + (*idx), sep);
		set_quotes_flag(str[*idx], sep);
		if (len)
			return (ft_strndup(str + (*idx), len + 1));
	}
	len += 1;
	while (str[*idx + len] && !is_quote(str[*idx + len]))
		len += 1;
	*sep = 0;
	return (ft_strndup(str + (*idx), len));
}

int	parse_str_env(char **str)
{
	int		idx;
	char	*tar;
	char	*new;
	int		sep;

	idx = 0;
	sep = 0;
	while ((*str)[idx])
	{
		tar = get_next_str(*str, &idx, &sep);
		if (tar == 0)
			continue ;
		new = ft_strtrim(tar, (const char *)&sep);
		if (sep != '\'' && trans_all_env(&new) == 0)
			return (0);
		*str = change_str(*str, tar, new);
		idx += ft_strlen(new);
		free(new);
		free(tar);
	}
	return (1);
}

int	parse_cmd_env(char **cmd)
{
	int	idx;

	idx = 0;
	while (cmd[idx])
	{
		parse_str_env(&cmd[idx]);
		idx += 1;
	}
	return (1);
}
