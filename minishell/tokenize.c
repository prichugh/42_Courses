#include "minishell.h"

// void tokenize(char *input, t_token **tokens)
// {
// 	t_tokenizer data = {NULL, NULL, {0}, 0, 0, 0, 0, 0};
// 	int	i;
// 	i = 0;

// 	while (input[i] != '\0')
// 	{
// 		if (input[i] == '\'' && !data.in_double_quote)
// 		{
// 			data.in_single_quote = !data.in_single_quote;
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '\"' && !data.in_single_quote)
// 		{
// 			data.in_double_quote = !data.in_double_quote;
// 			i++;
// 			continue;
// 		}
// 		printf("test %d\n", i);
// 		if (ft_isspace(input[i]) && !data.in_single_quote && !data.in_double_quote)
// 		{
// 			handle_buffer(&data, TOKEN_WORD);
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '|') {
// 			handle_buffer(&data, TOKEN_WORD);
// 			add_token_to_list(&data.head, new_token(TOKEN_PIPE, "|"));
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '>')
// 		{
// 			if (input[i + 1] == '>') {
// 				handle_buffer(&data, TOKEN_WORD);
// 				add_token_to_list(&data.head, new_token(TOKEN_REDIR_APPEND, ">>"));
// 				i += 2;
// 				continue;
// 			}
// 			handle_buffer(&data, TOKEN_WORD);
// 			add_token_to_list(&data.head, new_token(TOKEN_REDIR_OUT, ">"));
// 			i++;
// 			continue;
// 		}
// 		if (input[i] == '<')
// 		{
// 			if (input[i + 1] == '<')
// 			{
// 				handle_buffer(&data, TOKEN_WORD);
// 				add_token_to_list(&data.head, new_token(TOKEN_HEREDOC, "<<"));
// 				i += 2;
// 				continue;
// 			}
// 			handle_buffer(&data, TOKEN_WORD);
// 			add_token_to_list(&data.head, new_token(TOKEN_REDIR_IN, "<"));
// 			i++;
// 			continue;
// 		}
// 		data.buffer[data.buf_index++] = input[i++];
// 	}
// 	handle_buffer(&data, TOKEN_WORD); // Handle any remaining buffer
// 	*tokens = data.head; // Return the list of tokens
// }

// t_token *new_token(e_token_type type, char *value)
// {
// 	t_token *token;
// 	token = (t_token *)malloc(sizeof(t_token));
// 	if (!token)
// 		return (NULL);
// 	token->type = type;
// 	token->value = ft_strdup(value);
// 	token->next = NULL;
// 	return (token);
// }

// void	add_token(t_tokenizer *data, int token_type, char *value)
// {
// 	t_token	*token;

// 	token = new_token(token_type, value);
// 	// if (!token)
// 	// 	return ;
// 	if (!data->head)
// 		data->head = token;
// 	else
// 		data->tail->next = token;
// 	data->tail = token;
// }

// void	handle_buffer(t_tokenizer *data, int token_type)
// {
// 	if (data->buf_index > 0)
// 	{
// 		data->buffer[data->buf_index] = '\0';
// 		add_token(data, token_type, data->buffer);
// 		data->buf_index = 0;
// 	}
// }

// void add_token_to_list(t_token **token_list, t_token *new_token) {
//     t_token *current;

//     if (*token_list == NULL) {
//         // If the list is empty, the new token becomes the first element
//         *token_list = new_token;
//     } else {
//         // Traverse the list to find the last token
//         current = *token_list;
//         while (current->next != NULL) {
//             current = current->next;
//         }
//         // Add the new token at the end of the list
//         current->next = new_token;
//     }
// }

// void add_token_to_list(t_tokenizer *data, t_token *new_token)
// {
//     if (data->head == NULL) {
//         data->head = new_token;
//     } else {
//         data->tail->next = new_token;
//     }
//     data->tail = new_token;
// }

// t_token *new_token(e_token_type type, char *value) {
//     t_token *token = (t_token *)malloc(sizeof(t_token));
//     if (!token) {
//         perror("Failed to allocate token");
//         exit(EXIT_FAILURE);
//     }
//     token->type = type;
//     token->value = strdup(value); // Copying value
//     token->next = NULL;
//     return token;
// }

// void add_token(t_tokenizer *data, int token_type, char *value) {
//     t_token *token = new_token(token_type, value);
//     add_token_to_list(data, token);
// }

// void handle_buffer(t_tokenizer *data, int token_type) {
//     if (data->buf_index > 0) {
//         data->buffer[data->buf_index] = '\0';
//         add_token(data, token_type, data->buffer);
//         data->buf_index = 0;
//     }
// }

// void tokenize(char *input, t_tokenizer *data) {
//     data->head = data->tail = NULL;
//     data->buf_index = data->in_single_quote = data->in_double_quote = 0;

//     int i = 0;
//     while (input[i] != '\0') {
//         if (data->buf_index >= BUFFER_SIZE - 1) {
//             fprintf(stderr, "Buffer overflow detected\n");
//             exit(EXIT_FAILURE);
//         }
//         if (input[i] == '\'' && !data->in_double_quote) {
//             data->in_single_quote = !data->in_single_quote;
//             i++;
//             continue;
//         }
//         if (input[i] == '\"' && !data->in_single_quote) {
//             data->in_double_quote = !data->in_double_quote;
//             i++;
//             continue;
//         }
//         if (isspace(input[i]) && !data->in_single_quote && !data->in_double_quote) {
//             handle_buffer(data, TOKEN_WORD);
//             i++;
//             continue;
//         }
//         if (input[i] == '|') {
//             handle_buffer(data, TOKEN_WORD);
//             add_token_to_list(data, new_token(TOKEN_PIPE, "|"));
//             i++;
//             continue;
//         }
//         if (input[i] == '>') {
//             handle_buffer(data, TOKEN_WORD);
//             if (input[i + 1] == '>') {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_APPEND, ">>"));
//                 i += 2;
//             } else {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_OUT, ">"));
//                 i++;
//             }
//             continue;
//         }
//         if (input[i] == '<') {
//             handle_buffer(data, TOKEN_WORD);
//             if (input[i + 1] == '<') {
//                 add_token_to_list(data, new_token(TOKEN_HEREDOC, "<<"));
//                 i += 2;
//             } else {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_IN, "<"));
//                 i++;
//             }
//             continue;
//         }
//         data->buffer[data->buf_index++] = input[i++];
//     }
//     handle_buffer(data, TOKEN_WORD);
// }


t_token *new_token(e_token_type type, char *value) {
    t_token *token = (t_token *)malloc(sizeof(t_token));
    if (!token) {
        perror("Failed to allocate token");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->value = strdup(value);
    token->next = NULL;
    return token;
}

void add_token_to_list(t_tokenizer *data, t_token *new_token) {
    if (data->head == NULL) {
        data->head = new_token;
    } else {
        data->tail->next = new_token;
    }
    data->tail = new_token;
}

void handle_buffer(t_tokenizer *data, e_token_type token_type) {
    if (data->buf_index > 0) {
        data->buffer[data->buf_index] = '\0';
        add_token_to_list(data, new_token(token_type, data->buffer));
        data->buf_index = 0;
    }
}

// void tokenize(char *input, t_tokenizer *data) {
//     data->head = data->tail = NULL;
//     data->buf_index = data->in_single_quote = data->in_double_quote = 0;

//     int i = 0;
//     while (input[i] != '\0') {
//         if (data->buf_index >= BUFFER_SIZE - 1) {
//             fprintf(stderr, "Buffer overflow detected\n");
//             exit(EXIT_FAILURE);
//         }
//         if (input[i] == '\'' && !data->in_double_quote) {
//             data->in_single_quote = !data->in_single_quote;
//             i++;
//             continue;
//         }
//         if (input[i] == '\"' && !data->in_single_quote) {
//             data->in_double_quote = !data->in_double_quote;
//             i++;
//             continue;
//         }
//         if (isspace(input[i]) && !data->in_single_quote && !data->in_double_quote) {
//             handle_buffer(data, TOKEN_WORD);
//             i++;
//             continue;
//         }
//         if (input[i] == '|') {
//             handle_buffer(data, TOKEN_WORD);
//             add_token_to_list(data, new_token(TOKEN_PIPE, "|"));
//             i++;
//             continue;
//         }
//         if (input[i] == '>') {
//             handle_buffer(data, TOKEN_WORD);
//             if (input[i + 1] == '>') {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_APPEND, ">>"));
//                 i += 2;
//             } else {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_OUT, ">"));
//                 i++;
//             }
//             continue;
//         }
//         if (input[i] == '<') {
//             handle_buffer(data, TOKEN_WORD);
//             if (input[i + 1] == '<') {
//                 add_token_to_list(data, new_token(TOKEN_HEREDOC, "<<"));
//                 i += 2;
//             } else {
//                 add_token_to_list(data, new_token(TOKEN_REDIR_IN, "<"));
//                 i++;
//             }
//             continue;
//         }

//         // Check for missing space (e.g., ">>output.txt")
//         if (input[i] == '>' || input[i] == '<') {
//             fprintf(stderr, "Error: Missing space after operator at position %d\n", i);
//             exit(EXIT_FAILURE);
//         }

//         data->buffer[data->buf_index++] = input[i++];
//     }
//     handle_buffer(data, TOKEN_WORD);
//    //
// }

void tokenize(char *input, t_tokenizer *data) {
    data->head = data->tail = NULL;
    data->buf_index = data->in_single_quote = data->in_double_quote = 0;

    int i = 0;
    while (input[i] != '\0') {
        if (data->buf_index >= BUFFER_SIZE - 1) {
            fprintf(stderr, "Buffer overflow detected\n");
            exit(EXIT_FAILURE);
        }

        // Handle single quotes
        if (input[i] == '\'' && !data->in_double_quote) {
            data->buffer[data->buf_index++] = input[i];  // Add quote to buffer
            data->in_single_quote = !data->in_single_quote;
            i++;
            continue;
        }

        // Handle double quotes
        if (input[i] == '\"' && !data->in_single_quote) {
            data->buffer[data->buf_index++] = input[i];  // Add quote to buffer
            data->in_double_quote = !data->in_double_quote;
            i++;
            continue;
        }

        // Ignore backslashes and semicolons
        if (input[i] == '\\' || input[i] == ';') {
            i++;
            continue;
        }

        // Handle whitespace outside of quotes
        if (isspace(input[i]) && !data->in_single_quote && !data->in_double_quote) {
            handle_buffer(data, TOKEN_WORD);
            i++;
            continue;
        }

        // Handle pipe
        if (input[i] == '|') {
            handle_buffer(data, TOKEN_WORD);
            add_token_to_list(data, new_token(TOKEN_PIPE, "|"));
            i++;
            continue;
        }

        // Handle redirection: output
        if (input[i] == '>') {
            handle_buffer(data, TOKEN_WORD);
            if (input[i + 1] == '>') {
                add_token_to_list(data, new_token(TOKEN_REDIR_APPEND, ">>"));
                i += 2;
            } else {
                add_token_to_list(data, new_token(TOKEN_REDIR_OUT, ">"));
                i++;
            }
            continue;
        }

        // Handle redirection: input
        if (input[i] == '<') {
            handle_buffer(data, TOKEN_WORD);
            if (input[i + 1] == '<') {
                add_token_to_list(data, new_token(TOKEN_HEREDOC, "<<"));
                i += 2;
            } else {
                add_token_to_list(data, new_token(TOKEN_REDIR_IN, "<"));
                i++;
            }
            continue;
        }

        // Add regular characters to buffer
        data->buffer[data->buf_index++] = input[i++];
    }

    // Finalize last token if available
    handle_buffer(data, TOKEN_WORD);

   if (data->in_single_quote || data->in_double_quote) {
        fprintf(stderr, "Error: Unclosed quote detected\n");
        if (data->head) {  // Only free tokens if they exist
            free_tokens(data->head);
        }
        data->head = data->tail = NULL; // Reset head and tail
        return;
    }
}
