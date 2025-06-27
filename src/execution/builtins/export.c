/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iel-ghou <iel-ghou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 08:35:52 by iel-ghou          #+#    #+#             */
/*   Updated: 2025/06/26 13:39:08 by iel-ghou         ###   ########.fr       */
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

int	handle_export_arg(char *arg, t_env *env)
{
	int	error_ret;

	if (!is_valid_identifier(arg))
	{
		fprintf(stderr, "export: `%s': not a valid identifier\n", arg);
		return (1);
	}
	if (arg[0] == '=')
		error_ret = -3;
	else
		error_ret = is_valid_env(arg);
	if (error_ret <= 0)
	{
		print_error(error_ret, arg);
		return (1);
	}
	if (is_in_env(env, arg))
		env_update(arg, env);
	else
		env_add(arg, env);
	return (0);
}

int	ft_export(char **args, t_env *env)
{
	int	i;
	int	status;

	status = 0;
	if (!args[1])
	{
		print_sorted_env(env);
		return (SUCCESS);
	}
	i = 1;
	while (args[i])
	{
		if (handle_export_arg(args[i], env) != 0)
			status = 1;
		i++;
	}
	return (status);
}
