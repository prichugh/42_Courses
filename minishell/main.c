#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data data;

	struct_init(&data);
	t_env_init(&data, envp);
	(void)argv;
	(void)envp;

	if (argc != 1)
	{
		printf("\"./minishell\" must be the only argument\n");
		return (0);
	}
	start_program(&data);
	return (0);
}
