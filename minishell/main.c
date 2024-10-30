#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	// if (argc == 2 && strcmp(argv[1], "--test") == 0)
    // {
    //     test_tokenize_and_replace();
    //     return 0;
    // }
	if (argc != 1)
	{
		printf("\"./minishell\" must be the only argument\n");
		return (0);
	}
	start_program();
	return (0);
}
