#include "minishell.h"

void	start_program()
{
	char			*input;
	//t_token			*tokens;
	t_shell_state	shell_state = {0}; //REDUCE TO ONE STRUCT!!!
	t_tokenizer 	data;

	signal(SIGINT, handle_sigint); // Set the signal handler for ctrl+c
	while (1)
	{
		input = readline(">>> "); //readline caues mem leaks
		if (input == NULL) //ADJUST TO SUBJECT
		{
			printf("EOF detected, exiting...\n");
			break ;
		}
		if (strcmp(input, "exit") == 0) // add my own ft_strcmp
		{
			free(input);
			break ;
		}
		if (input && *input)
			add_history(input);  //add_history causes mem leaks
		//t_command command = {NULL, NULL}; // Initialize command structure
		if (validate_input(input))
		{
			tokenize(input, &data);
			if (data.head)
			{
				//classify_token_types(data.head);
				replace_env_variables_in_tokens(data.head, &shell_state);
				print_tokens(data.head);
				free_tokens(data.head);
			}
		}
		free(input);
	}
	clear_history();
}

//void	start_program()
//{
	//initialize main data struct to hold tokens and other info
	//initialize signal handlers for the various signals
	//start of infinite while loop
	//use readline to retrieve user input
	//handle various bad input per subject
	//if input is exit then call exit program function
	//if there is in fact legal input add it to history
	//call tokenize function to tokenize input into a linked list inside main data struct
	//if token have been succesfully created, call syntax check function to verify correct grammar
	//then call parse function which dettermine which execute functions to call
	//free the input and tokens
	//clear history
//}
