#include <stellarc_utils.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <tokenizer.h>
// Coming not yet.
// #include <parser.h>

void print_token(Token *t)
{
	printf("[%d : %s : Line %d]\n", t->type, t->lexeme, t->line);
}

void free_token(Token *t)
{
	free(t->lexeme);
    free(t);
}

// #define FUNNY_PUN

// #define DEBUG_PRINT_CHAR_CODES
#define DEBUG_PRINT_TOKEN_VALUES

void compile(char *filename)
{
	int c = 0;

    // Get it? (prima aprilis special leaked)
    #ifdef FUNNY_PUN
        c++;
        raise(SIGSEGV);
    #endif
	
	char *code = malloc(sizeof(char) * 2);
	
	FILE *script = fopen(filename, "r+");

	if(script == NULL)
	{
		printf("Failed to open file %s\n", filename);
		return;
	}

	char cc[2];

	while((c = fgetc(script)) != EOF)
	{

#ifdef DEBUG_PRINT_CHAR_CODES

        printf("Current character code: %d\n", c);

#endif

		cc[0] = (char) c;

        code = realloc(code, strlen(code) + strlen(cc) + 1);

        strcat(code, cc);
	}

	TokenList *tokens = tokenize(code);

	free(code);

    if(had_error)
    {
        walk_token_list(tokens, free_token);
        free_token_list(tokens);
        fclose(script);
        fprintf(stderr, "Errors detected. Compilation halted.\n");
        exit(1);
    }

#ifdef DEBUG_PRINT_TOKEN_VALUES

	walk_token_list(tokens, print_token);

#endif

    // Parsing time

	walk_token_list(tokens, free_token);

    free_token_list(tokens);
	
	fclose(script);
}

// Thank you, https://stackoverflow.com/users/13358003/mortmann, very cool
int ends_with(const char *str, const char *suffix)
{
	size_t str_len = strlen(str);
	size_t suffix_len = strlen(suffix);

	return (str_len >= suffix_len) &&
	       (!memcmp(str + str_len - suffix_len, suffix, suffix_len));
}

void check(char **argv, int i)
{
	if(ends_with(argv[i], ".stellarc") || ends_with(argv[i], ".cstellar"))
	{
		compile(argv[i]);
	}
}

int main(int argc, char **argv)
{
	for(int i = 1; i < argc; i++)
	{
		check(argv, i);
	}
}
