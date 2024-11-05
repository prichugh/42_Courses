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

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef enum
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,			//	<
	TOKEN_REDIR_OUT,		// >
	TOKEN_REDIR_APPEND,		// >>
	TOKEN_HEREDOC			// <<
}	e_token_type;

typedef struct	s_token
{
	e_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct	s_data
{
	t_token	*head;
	t_token	*tail;
	char	buffer[BUFFER_SIZE];
	int		buf_index;
	int		in_single_quote;
	int		in_double_quote;
	int		i;
	int		last_exit_status; //needs to be implemented!
	t_env		*env_lst; // linkedlst featuring the current envp
	char*		cmd;
	int			exit; // to quit minishell
}			t_data;

//-----------main.c------------//
int main(int argc, char **argv, char **envp);


//-----------utils.c------------//
int		ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_isspace(char c);
int		ft_isalnum(char c);
//ft_strcmp


//--------utils_token.c--------//
void	print_tokens(t_token *token_list);
char	*trim_whitespace(char *str);
void 	free_tokens(t_token *head);
int		validate_input(t_token *tokens);
char	*ft_itoa(int n);


//-----------signals.c----------//
void	handle_sigint(int sig);


//---------tokenize.c----------//
void	tokenize(char *input, t_data *data);
t_token	*new_token(e_token_type type, char *value);
//void	handle_buffer(t_data *data, int token_type);
void 	handle_buffer(t_data *data, e_token_type token_type);
//void	add_token_to_list(t_token **token_list, t_token *new_token);
void	add_token_to_list(t_data *data, t_token *new_token);
//void	add_token(t_data *data, int token_type, char *value);


//------start_program.c-------//
void	start_program(t_data *data);


//---------env_var.c---------//
void	replace_env_variables_in_tokens(t_token *tokens, t_data *data);
char	*replace_variables_in_string(char *input, t_data *data);


//---------inti.c-----------//
void	reset_data(t_data *data);
void	struct_init(t_data *shell);
int		t_env_init(t_data *shell, char **envp);


//---------free.c---------//
void	free_envlst(t_env *lst);


#endif

