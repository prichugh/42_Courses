#include "minishell.h"


//Go trough the list of tokens and correctly identify what is a commands
//and what is a argument
void	classify_token_types(t_data *data)
{
	(void) data;
	// 	char *new_value;

	// while (data->head->next)
	// {
	// 	printf("testing\n");
	// 	if (tokens->type == TOKEN_WORD)
	// 	{
	// 		new_value = replace_variables_in_string(tokens->value, data);
	// 		if (new_value != tokens->value) // Only free if they are different
	// 		{
	// 			free(tokens->value);
	// 			tokens->value = new_value;
	// 		}
	// 		else
	// 			free(new_value); // Free the new_value since it wasn't needed
	// 	}
	// 	tokens = tokens->next;
	// }
}
