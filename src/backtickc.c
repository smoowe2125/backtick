#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#include <tokenizer.h>

void print_token(Token *t)
{
	printf("[ Lexeme: %s ; Type: %d ; Line: %d ]\n", t->lexeme, t->type, t->line);
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

	TokenList *list = tokenize(code);

	free(code);

#ifdef DEBUG_PRINT_TOKEN_VALUES

	walk(list, print_token);

#endif

	walk(list, free_token);

    freelist(list);
	
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
	if(ends_with(argv[i], ".backtick"))
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
