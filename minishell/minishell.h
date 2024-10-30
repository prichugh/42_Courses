#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>
# include <assert.h>
# define BUFFER_SIZE 1024

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,      // <
	TOKEN_REDIR_OUT,     // >
	TOKEN_REDIR_APPEND,  // >>
	TOKEN_HEREDOC        // <<
}	e_token_type;

typedef struct	s_token
{
	e_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct	s_tokenizer
{
	t_token	*head;
	t_token	*tail;
	char	buffer[BUFFER_SIZE];
	int		buf_index;
	int		in_single_quote;
	int		in_double_quote;
	int		i;
	int last_exit_status; //maybe remove
}			t_tokenizer;

typedef struct s_shell_state
{
	int	last_exit_status;
}	t_shell_state;

typedef enum {
    REDIR_IN,       // <
    REDIR_OUT,      // >
    REDIR_APPEND,   // >>
    HEREDOC         // <<
} e_redirection_type;


typedef struct s_redirection {
    e_redirection_type type;
    char *filename;
    struct s_redirection *next;
} t_redirection;

typedef struct s_command {
    char *command;
    t_redirection *redirections;
} t_command;

//-----------main.c------------//
int main(int argc, char **argv, char **envp);


//-----------utils.c------------//
int		ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_isspace(char c);
int		ft_isalnum(char c);
//ft_strcmp

//--------utils_token.c--------//
void print_tokens(t_token *token_list);
char *trim_whitespace(char *str);
void free_tokens(t_token *head);
int	validate_input(const char *input);

//-----------signals.c----------//
void	handle_sigint(int sig);


//---------tokenize.c----------//
void	tokenize(char *input, t_tokenizer *data);
t_token	*new_token(e_token_type type, char *value);
//void	handle_buffer(t_tokenizer *data, int token_type);
void 	handle_buffer(t_tokenizer *data, e_token_type token_type);
//void	add_token_to_list(t_token **token_list, t_token *new_token);
void	add_token_to_list(t_tokenizer *data, t_token *new_token);
void	add_token(t_tokenizer *data, int token_type, char *value);


//------start_program.c-------//
void	start_program();


//---------env_var.c---------//
void	replace_env_variables_in_tokens(t_token *tokens, t_shell_state *shell_state);
char	*replace_variables_in_string(char *input, t_shell_state *shell_state);

#endif

