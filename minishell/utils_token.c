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
// int validate_input(const char *input)
// {
//     for (int i = 0; input[i] != '\0'; i++) {
//         if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c|'\n", input[i]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '|%c'\n", input[i + 1]);
//             return 0;
//         }
//     }
//     return 1;
// }
// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty input
//     if (length == 0) {
//         fprintf(stderr, "Syntax error: Empty input\n");
//         return 0;
//     }

//     // Check for operators at the start or end
//     if (input[0] == '|' || input[0] == '<' || input[0] == '>' ||
//         input[length - 1] == '|' || input[length - 1] == '<' ||
//         input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Check for invalid sequences
//         if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c|'\n", input[i]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '|%c'\n", input[i + 1]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '|' || input[i + 1] == '|')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '||'\n");
//             return 0;
//         }

//         // Check for multiple consecutive operators
//         if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c%c'\n", input[i], input[i + 1]);
//             return 0;
//         }

//         // Check for missing arguments after redirection operators
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//             return 0;
//         }

//         // Check for space before a pipe or redirection operator
//         if (i > 0 && isspace(input[i]) && (input[i + 1] == '|' || input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Space before operator '%c'\n", input[i + 1]);
//             return 0;
//         }

//         // Check for space after a pipe or redirection operator
//         if (i < length - 1 && (input[i] == '|' || input[i] == '<' || input[i] == '>') && isspace(input[i + 1])) {
//             fprintf(stderr, "Syntax error: Space after operator '%c'\n", input[i]);
//             return 0;
//         }

//         i++; // Increment the index
//     }

//     return 1; // All checks passed, input is valid
// }

// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty input
//     if (length == 0) {
//         fprintf(stderr, "Syntax error: Empty input\n");
//         return 0;
//     }

//     // Check for operators at the start or end
//     if (input[0] == '|' || input[0] == '<' || input[0] == '>' ||
//         input[length - 1] == '|' || input[length - 1] == '<' ||
//         input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Skip spaces to focus on meaningful characters
//         while (i < length && isspace(input[i])) i++;

//         // Check for invalid operator sequences
//         if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == '|')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c|'\n", input[i]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '|%c'\n", input[i + 1]);
//             return 0;
//         }
//         if (input[i] == '|' && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '||'\n");
//             return 0;
//         }

//         // Check for consecutive redirection operators without intermediate text
//         if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c%c'\n", input[i], input[i + 1]);
//             return 0;
//         }

//         // Check for missing arguments after a redirection operator
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             // Ensure there's a non-space argument after the operator
//             int j = i + 1;
//             while (j < length && isspace(input[j])) j++;
//             if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
//                 fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//                 return 0;
//             }
//         }

//         // Check for space before an operator
//         if (i > 0 && isspace(input[i - 1]) && (input[i] == '|' || input[i] == '<' || input[i] == '>')) {
//             fprintf(stderr, "Syntax error: Space before operator '%c'\n", input[i]);
//             return 0;
//         }

//         i++; // Move to the next character
//     }

//     return 1; // Input passed validation
// }

// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty input
//     if (length == 0) {
//         fprintf(stderr, "Syntax error: Empty input\n");
//         return 0;
//     }

//     // Check for invalid operators at the start or end
//     if (input[0] == '|' || input[length - 1] == '|' ||
//         input[length - 1] == '<' || input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Skip spaces to focus on meaningful characters
//         while (i < length && isspace(input[i])) i++;

//         // Check for invalid operator sequences
//         if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c|'\n", input[i]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '|%c'\n", input[i + 1]);
//             return 0;
//         }
//         if (input[i] == '|' && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '||'\n");
//             return 0;
//         }

//         // Check for consecutive redirection operators without intermediate text
//         if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c%c'\n", input[i], input[i + 1]);
//             return 0;
//         }

//         // Check for missing arguments after a redirection operator
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             // Ensure there's a non-space argument after the operator
//             int j = i + 1;
//             while (j < length && isspace(input[j])) j++;
//             if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
//                 fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//                 return 0;
//             }
//         }

//         // Check for space before an operator, e.g., "< command > " with no command in between
//         if (i > 0 && isspace(input[i - 1]) && (input[i] == '|' || input[i] == '<' || input[i] == '>')) {
//             fprintf(stderr, "Syntax error: Space before operator '%c'\n", input[i]);
//             return 0;
//         }

//         i++; // Move to the next character
//     }

//     return 1; // Input passed validation
// }
// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty input
//     if (length == 0) {
//         fprintf(stderr, "Syntax error: Empty input\n");
//         return 0;
//     }

//     // Check for invalid operators at the start or end
//     if (input[0] == '|' || input[length - 1] == '|' ||
//         input[length - 1] == '<' || input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Skip spaces to focus on meaningful characters
//         while (i < length && isspace(input[i])) i++;

//         // Check for invalid operator sequences like "<|", "|<", "||"
//         if ((input[i] == '<' || input[i] == '>') && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c|'\n", input[i]);
//             return 0;
//         }
//         if (input[i] == '|' && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '|%c'\n", input[i + 1]);
//             return 0;
//         }
//         if (input[i] == '|' && input[i + 1] == '|') {
//             fprintf(stderr, "Syntax error: Invalid sequence '||'\n");
//             return 0;
//         }

//         // Check for consecutive redirection operators without intermediate text
//         if ((input[i] == '<' || input[i] == '>') && (input[i + 1] == '<' || input[i + 1] == '>')) {
//             fprintf(stderr, "Syntax error: Invalid sequence '%c%c'\n", input[i], input[i + 1]);
//             return 0;
//         }

//         // Check for missing arguments after a redirection operator
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             // Ensure there's a non-space argument after the operator
//             int j = i + 1;
//             while (j < length && isspace(input[j])) j++;
//             if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
//                 fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//                 return 0;
//             }
//         }

//         i++; // Move to the next character
//     }

//     return 1; // Input passed validation
// }
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty or whitespace-only input
//     while (i < length && isspace(input[i])) i++;
//     if (i == length) {
//         fprintf(stderr, "Syntax error: Empty or whitespace-only input\n");
//         return 0;
//     }
//     i = 0; // Reset i after checking for whitespace-only input

//     // Check for invalid operators at the start or end
//     if (input[0] == '|' || input[length - 1] == '|' ||
//         input[0] == '<' || input[0] == '>' ||
//         input[length - 1] == '<' || input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Skip spaces to focus on meaningful characters
//         while (i < length && isspace(input[i])) i++;

//         // Check for invalid consecutive or spaced operators
//         if ((input[i] == '<' || input[i] == '>' || input[i] == '|')) {
//             char op = input[i];
//             int j = i + 1;

//             // Skip spaces after the operator
//             while (j < length && isspace(input[j])) j++;

//             // Check if the next character is another operator
//             if (j < length && (input[j] == '<' || input[j] == '>' || input[j] == '|')) {
//                 fprintf(stderr, "Syntax error: Invalid sequence '%c %c'\n", op, input[j]);
//                 return 0;
//             }
//         }

//         // Check for missing arguments after a redirection operator
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             // Ensure there's a non-space argument after the operator
//             int j = i + 1;
//             while (j < length && isspace(input[j])) j++;
//             if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
//                 fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//                 return 0;
//             }
//         }

//         i++; // Move to the next character
//     }

//     return 1; // Input passed validation
// }

// int validate_input(const char *input) {
//     int i = 0;
//     int length = strlen(input);

//     // Check for empty or whitespace-only input
//     while (i < length && isspace(input[i])) i++;
//     if (i == length) {
//         return 1; // Return empty prompt for whitespace-only input
//     }
//     i = 0; // Reset i after checking for whitespace-only input

//     // Check for invalid operators at the start or end
//     if (input[0] == '|' || input[length - 1] == '|' ||
//         input[0] == '<' || input[0] == '>' ||
//         input[length - 1] == '<' || input[length - 1] == '>') {
//         fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
//         return 0;
//     }

//     while (i < length) {
//         // Skip spaces to focus on meaningful characters
//         while (i < length && isspace(input[i])) i++;

//         // Check for invalid consecutive or spaced operators
//         if ((input[i] == '<' || input[i] == '>' || input[i] == '|')) {
//             char op = input[i];
//             int j = i + 1;

//             // Skip spaces after the operator
//             while (j < length && isspace(input[j])) j++;

//             // Check if the next character is another operator, but allow valid chaining
//             if (j < length && (input[j] == '<' || input[j] == '>' || input[j] == '|')) {
//                 // Allow valid redirection chains
//                 if ((op == '>' && input[j] == '>') || (op == '<' && input[j] == '<')) {
//                     i = j; // Move past this valid operator sequence
//                     continue;
//                 }
//                 fprintf(stderr, "Syntax error: Invalid sequence '%c %c'\n", op, input[j]);
//                 return 0;
//             }
//         }

//         // Check for missing arguments after a redirection operator
//         if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
//             // Ensure there's a non-space argument after the operator
//             int j = i + 1;
//             while (j < length && isspace(input[j])) j++;
//             if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
//                 fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
//                 return 0;
//             }
//         }

//         i++; // Move to the next character
//     }

//     return 1; // Input passed validation
// }

int validate_input(const char *input) {
    int i = 0;
    int length = strlen(input);

    // Check for empty or whitespace-only input
    while (i < length && ft_isspace(input[i])) i++;
    if (i == length) {
        return 1; // Return empty prompt for whitespace-only input
    }
    i = 0; // Reset i after checking for whitespace-only input

    // Check for invalid operators at the start or end
    if (input[0] == '|' || input[length - 1] == '|' ||
        input[0] == '<' || input[0] == '>' ||
        input[length - 1] == '<' || input[length - 1] == '>') {
        fprintf(stderr, "Syntax error: Operator at the start or end of input\n");
        return 0;
    }

    while (i < length) {
        // Skip spaces to focus on meaningful characters
        while (i < length && isspace(input[i])) i++;

        // Check for invalid consecutive or spaced operators
        if ((input[i] == '<' || input[i] == '>' || input[i] == '|')) {
            char op = input[i];
            int j = i + 1;

            // Skip spaces after the operator
            while (j < length && isspace(input[j])) j++;

            // Check if the next character is another operator, but allow valid chaining
            if (j < length && (input[j] == '<' || input[j] == '>' || input[j] == '|')) {
                // Allow valid redirection chains
                if ((op == '>' && input[j] == '>') || (op == '<' && input[j] == '<')) {
                    i = j; // Move past this valid operator sequence
                    continue;
                }
                fprintf(stderr, "Syntax error: Invalid sequence '%c %c'\n", op, input[j]);
                return 0;
            }
        }

        // Check for missing arguments after a redirection operator
        if ((input[i] == '<' || input[i] == '>') && (i == length - 1 || isspace(input[i + 1]))) {
            // Ensure there's a non-space argument after the operator
            int j = i + 1;
            while (j < length && isspace(input[j])) j++;
            if (j == length || input[j] == '|' || input[j] == '<' || input[j] == '>') {
                fprintf(stderr, "Syntax error: Missing argument after '%c'\n", input[i]);
                return 0;
            }
        }

        i++; // Move to the next character
    }

    return 1; // Input passed validation
}
