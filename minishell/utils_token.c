#include "minishell.h"

char *trim_whitespace(char *str)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')
		start++;
	while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n'))
		end--;
	str[end + 1] = '\0';
	return (&str[start]);
}

void print_tokens(t_token *token_list)
{
    t_token *current = token_list;

    while (current != NULL) {
        printf("Token: %s, Type: ", current->value);

        //Check the type and print accordingly
        if (current->type == TOKEN_WORD) {
            printf("COMMAND");
        } else if (current->type == TOKEN_WORD) {
            printf("ARGUMENT");
        } else if (current->type == TOKEN_PIPE) {
            printf("PIPE");
        } else if (current->type == TOKEN_HEREDOC) {
            printf("HEREDOC");
		} else if (current->type == TOKEN_REDIR_APPEND) {
            printf("REDIR APPEND");
		} else if (current->type == TOKEN_REDIR_IN) {
            printf("REDIR IN");
		} else if (current->type == TOKEN_REDIR_OUT) {
            printf("REDIR OUT");
        } else {
            printf("UNKNOWN");
        }
        printf("\n");

        current = current->next;
    }
}
void	free_envlst(t_env *lst)
{
	(void)lst;
}
//free's a linked list
void free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->value)
			free(temp->value);
		free(temp);
	}
}
//Make preliminary checks on input. Ensure operators (|, <<, >) are not next to
//eachother. That input doesn't start or end with an operator, that operator are
//not next to eachother and check for missing args after operators. Error msgs
//are incoorect for testing purposes but need to be updated to match bash!!
int	validate_input(t_token *tokens)
 {
    t_token *current = tokens;
    int token_count = 0;

    // Check for empty input (null or no tokens)
    if (!current) {
        return 1; // Empty prompt for no tokens
    }

    // Check if the first token is an operator
    if (current->value[0] == '|' || current->value[0] == '<' || current->value[0] == '>') {
        fprintf(stderr, "Syntax error: Operator at the start of input\n");
        return 0;
    }

    while (current) {
        token_count++;

        // Check for invalid consecutive operators
        if ((current->value[0] == '<' || current->value[0] == '>' || current->value[0] == '|'))
		{
            if (current->next && (current->next->value[0] == '<' || current->next->value[0] == '>' || current->next->value[0] == '|'))
			{
                // Allow valid redirection chains
                if (!(current->value[0] == '>' && current->next->value[0] == '>') &&
                    !(current->value[0] == '<' && current->next->value[0] == '<'))
				{
                    printf("syntax error Invalid sequence '%s %s'\n", current->value, current->next->value);
                    return 0;
                }
            }
        }

        // Check for missing arguments after a redirection operator
        if ((current->value[0] == '<' || current->value[0] == '>'))
		{
            if (!current->next || !current->next->value[0]
				|| current->next->value[0] == '|'
				|| current->next->value[0] == '<'
				|| current->next->value[0] == '>')
			{
                printf("syntax error Missing argument after '%s'\n", current->value);
                return 0;
            }
        }

        current = current->next; // Move to the next token
    }

    // Check if the last token is an operator
    if (tokens)
	{
        t_token *last = tokens;
        while (last->next) {
            last = last->next;
        }
        if (last->value[0] == '|' || last->value[0] == '<' || last->value[0] == '>')
		{
            printf("Syntax error: Operator at the end of input\n");
            return 0;
        }
    }

    return (1); // Input passed validation
}
