#include "minishell.h"

void	struct_init(t_data *shell)
{
	//shell->arg = "cat";
	shell->exit = 0;
	shell->head = NULL;
	shell->tail = NULL;
	shell->buf_index = 0;
	shell->in_double_quote = 0;
	shell->in_single_quote = 0;
}

void	reset_data(t_data *data)
{
	data->head = NULL;
	data->tail = NULL;
	data->in_double_quote = 0;
	data->in_single_quote = 0;
}

//Takes an array of environment variables envp, creates a linked list,
//saves a copy of the env_array in SHELL->t_env and returns 0 when SUCCEED.
int	t_env_init(t_data *shell, char **envp)
{
	t_env	*current;
	int		i;

	current = (t_env *)malloc(sizeof(t_env));
	if (!(current))
		return (-1);
	current->content = ft_strdup(envp[0]);
	if (!(current->content))
	{
		free_envlst(current);
		return (-1);
	}
	current->next = NULL;
	shell->env_lst = current;
	i = 1;
	while (envp && envp[i])
	{
		current->next = (t_env *)malloc(sizeof(t_env));
		if (!(current->next))
		{
			free_envlst(current);
			return (-1);
		}
		current = current->next;
		current->content = ft_strdup(envp[i]);
		if (!(current->content))
		{
			free_envlst(current);
			return (-1);
		}
		current->next = NULL;
		i++;
	}
	return (0);
}
