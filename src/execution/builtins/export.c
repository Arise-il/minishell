/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:52 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/25 16:32:09 by iel-ghou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	print_error(int error, const char *arg)
{
	int	i;

	i = 0;
	ft_putstr_fd("bash: export: `", STDERR);
	while (arg[i] && arg[i] != '=')
	{
		write(STDERR, &arg[i], 1);
		i++;
	}
	if (i == 0 || arg[i] == '=')
		write(STDERR, "=", 1);
	ft_putstr_fd("': ", STDERR);
	if (error == -3)
		ft_putstr_fd("not valid in this context", STDERR);
	else if (error == -1 || error == 0)
		ft_putstr_fd("not a valid identifier", STDERR);
	write(STDERR, "\n", 1);
	return (ERROR);
}

int	env_add(const char *value, t_env *env)
{
	t_env	*new;

	if (!env)
		return (-1);
	if (env->value == NULL)
	{
		env->value = ft_strdup(value);
		if (!env->value)
			return (-1);
		return (SUCCESS);
	}
	new = ft_malloc(sizeof(t_env), 1);
	if (!new)
		return (-1);
	new->value = ft_strdup(value);
	if (!new->value)
		return (-1);
	new->next = NULL;
	while (env->next)
		env = env->next;
	env->next = new;
	return (SUCCESS);
}

char	*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=' && i < BUFF_SIZE - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
			return (1);
		env = env->next;
	}
	return (0);
}

int	is_valid_identifier(const char *s)
{
	int	i;

	i = 0;
	if (!s || !s[0])
		return (0);
	if (!(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

int	env_update(char *new_value, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, new_value);
	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			env->value = ft_strdup(new_value);
			if (!env->value)
				return (ERROR);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (ERROR);
}

int	ft_export(char **args, t_env *env)
{
	int		error_ret;
	int		i;
	int		status;

	status = 0;
	if (!args[1])
	{
		print_sorted_env(env);
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			fprintf(stderr, "export: `%s': not a valid identifier\n", args[i]);
			status = 1;
			i++;
			continue ;
		}
		error_ret = is_valid_env(args[i]);
		if (args[i][0] == '=')
			error_ret = -3;
		if (error_ret <= 0)
		{
			print_error(error_ret, args[i]);
			status = 1;
			i++;
			continue ;
		}
		if (is_in_env(env, args[i]))
			env_update(args[i], env);
		else
			env_add(args[i], env);
		i++;
	}
	return (status);
}
