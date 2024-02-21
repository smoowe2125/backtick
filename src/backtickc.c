#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <tokenizer.h>

void print_token(Token *t)
{
	printf("[ Lexeme: %s ; Type: %d ]\n", t->lexeme, t->type);
}

void free_token(Token *t)
{
	free(t->lexeme);
    free(t);
}

void compile(char *filename)
{
	char c;
	
	char *code = malloc(sizeof(char) * 2);
	
	FILE *script = fopen(filename, "r+");

	if(script == NULL)
	{
		printf("Failed to open file %s\n", filename);
		return;
	}

	char cc[2];

	while(!feof(script))
	{
		c = fgetc(script);

		cc[0] = c;

        code = realloc(code, strlen(code) + strlen(cc) + 1);

        strcat(code, cc);
	}

	TokenList *list = tokenize(code);

	free(code);

	walk(list, print_token);

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
