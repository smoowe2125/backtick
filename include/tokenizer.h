#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum
{
    // Keywords
    TOKEN_PRINTLN,
    TOKEN_PRINT,
    TOKEN_CLASS,
    TOKEN_IF,
    TOKEN_ELSE,
    TOKEN_FOR,
    TOKEN_WHILE,
    TOKEN_FOREACH,
    TOKEN_SYSCALL,
    TOKEN_IMPORT,

    // Types
    TOKEN_INT8,
    TOKEN_INT16,
    TOKEN_INT32,
    TOKEN_INT64,

    TOKEN_UINT8,
    TOKEN_UINT16,
    TOKEN_UINT32,
    TOKEN_UINT64,

    TOKEN_FLOAT,
    TOKEN_DOUBLE,
    TOKEN_REAL,

    TOKEN_STRING,
    TOKEN_CHAR,

    TOKEN_OBJECT,
    
    TOKEN_BOOLEAN,

    TOKEN_VOID,

    // Expressions

    TOKEN_NUMBER,

    TOKEN_TRUE,
    TOKEN_FALSE,

    TOKEN_STR_LITERAL,

    // Operators

    TOKEN_PLUS,
    TOKEN_PLUS_EQUAL,
    TOKEN_PLUS_PLUS,
    
    TOKEN_MINUS,
    TOKEN_MINUS_EQUAL,
    TOKEN_MINUS_MINUS,

    TOKEN_STAR,
    TOKEN_STAR_EQUAL,
    TOKEN_STAR_STAR,

    TOKEN_SLASH,
    TOKEN_SLASH_EQUAL,
    TOKEN_SLASH_SLASH,

    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    
    TOKEN_NOT,
    TOKEN_NOT_EQUAL,

    TOKEN_EQUAL,
    TOKEN_EQUAL_EQUAL,

    TOKEN_MODULO,
    TOKEN_MODULO_EQUAL,

    TOKEN_XOR,
    TOKEN_XOR_EQUAL,

    TOKEN_AND,
    TOKEN_AND_EQUAL,
    TOKEN_LOGIC_AND,

    TOKEN_OR,
    TOKEN_OR_EQUAL,
    TOKEN_LOGIC_OR,

    // Other stuff

    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,

    TOKEN_OPEN_SQUARE,
    TOKEN_CLOSE_SQUARE,

    TOKEN_OPEN_BRACE,
    TOKEN_CLOSE_BRACE,

    TOKEN_IDENTIFIER,

    TOKEN_NONE
} TokenType;

typedef struct
{
    TokenType type;
    char *lexeme;
} Token;

bool is_numeric(char c)
{
    return c >= '0' && c <= '9';
}

bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

bool is_alpha_numeric(char c)
{
    return is_alpha(c) || is_numeric(c) || c == '_';
}

Token *string(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    (*i)++;

    while(code[*i] != '\"')
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

    (*i)++;

    out->type = TOKEN_STR_LITERAL;

    return out;
}

Token *number(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    while(is_numeric(code[*i]))
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

	out->type = TOKEN_NUMBER;

    return out;
}

bool compare(char *str1, char *str2)
{
    return strcmp(str1, str2) == 0;
}

Token *identifier(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    while(is_alpha_numeric(code[*i]))
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

    out->type = TOKEN_IDENTIFIER;

    if(compare(out->lexeme, "int8"))
    {
        out->type = TOKEN_INT8;
    }
    else if(compare(out->lexeme, "int16"))
    {
        out->type = TOKEN_INT16;
    }
    else if(compare(out->lexeme, "int32") || compare(out->lexeme, "int"))
    {
        out->type = TOKEN_INT32;
    }
    else if(compare(out->lexeme, "int64"))
    {
        out->type = TOKEN_INT64;
    }
    else if(compare(out->lexeme, "uint8"))
    {
        out->type = TOKEN_UINT8;
    }
    else if(compare(out->lexeme, "uint16"))
    {
        out->type = TOKEN_UINT16;
    }
    else if(compare(out->lexeme, "uint32") || compare(out->lexeme, "uint"))
    {
        out->type = TOKEN_UINT32;
    }
    else if(compare(out->lexeme, "uint64"))
    {
        out->type = TOKEN_UINT64;
    }
    else if(compare(out->lexeme, "float"))
    {
        out->type = TOKEN_FLOAT;
    }
    else if(compare(out->lexeme, "double"))
    {
        out->type = TOKEN_DOUBLE;
    }
    else if(compare(out->lexeme, "real"))
    {
        out->type = TOKEN_REAL;
    }
    else if(compare(out->lexeme, "string"))
    {
        out->type = TOKEN_STRING;
    }
    else if(compare(out->lexeme, "char"))
    {
        out->type = TOKEN_CHAR;
    }
    else if(compare(out->lexeme, "object"))
    {
        out->type = TOKEN_OBJECT;
    }
    else if(compare(out->lexeme, "bool"))
    {
        out->type = TOKEN_BOOLEAN;
    }
    else if(compare(out->lexeme, "void"))
    {
    	out->type = TOKEN_VOID;
    }
    else if(compare(out->lexeme, "true"))
    {
    	out->type = TOKEN_TRUE;
    }
    else if(compare(out->lexeme, "false"))
    {
    	out->type = TOKEN_FALSE;
    }
    else if(compare(out->lexeme, "println"))
    {
    	out->type = TOKEN_PRINTLN;
    }
    else if(compare(out->lexeme, "print"))
    {
    	out->type = TOKEN_PRINT;
    }
    else if(compare(out->lexeme, "class"))
    {
    	out->type = TOKEN_CLASS;
    }
    else if(compare(out->lexeme, "if"))
    {
    	out->type = TOKEN_IF;
    }
    else if(compare(out->lexeme, "else"))
    {
    	out->type = TOKEN_ELSE;
    }
    else if(compare(out->lexeme, "for"))
    {
    	out->type = TOKEN_FOR;
    }
    else if(compare(out->lexeme, "foreach"))
    {
    	out->type = TOKEN_FOREACH;
    }
    else if(compare(out->lexeme, "while"))
    {
    	out->type = TOKEN_WHILE;
    }
    else if(compare(out->lexeme, "syscall"))
    {
    	out->type = TOKEN_SYSCALL;
    }
    else if(compare(out->lexeme, "import"))
    {
    	out->type = TOKEN_IMPORT;
    }

    return out;
}

// I have decided that I'm a never nester so check this shit out

static inline Token *plus(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));

    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_PLUS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "+=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] == '+')
    {
        out->type = TOKEN_PLUS_PLUS;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "++");
        (*i)++;
        return out;
    }
    out->type = TOKEN_PLUS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "+");
    
    return out;
}

static inline Token *minus(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_MINUS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "-=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] == '-')
    {
        out->type = TOKEN_MINUS_MINUS;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "--");
        (*i)++;
        return out;
    }
    out->type = TOKEN_MINUS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "-");
    
    return out;
}

static inline Token *star(char *code, int *i)
{
	Token *out = malloc(sizeof(Token));

    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_STAR_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "*=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] == '*')
    {
        out->type = TOKEN_STAR_STAR;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "**");
        (*i)++;
        return out;
    }
    out->type = TOKEN_STAR;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "*");
    
    return out;
}

static inline Token *slash(char *code, int *i)
{
	Token *out = malloc(sizeof(Token));
    
	if(code[*i + 1] == '=')
	{
	    out->type = TOKEN_SLASH_EQUAL;
	    out->lexeme = malloc(sizeof(char) * 3);
	    strcat(out->lexeme, "/=");
	    (*i)++;
	    return out;
	}
	else if(code[*i + 1] == '/')
	{
	    out->type = TOKEN_SLASH_SLASH;
	    out->lexeme = malloc(sizeof(char) * 3);
	    strcat(out->lexeme, "//");
	    (*i)++;
	    return out;
	}
	out->type = TOKEN_SLASH;
	out->lexeme = malloc(sizeof(char) * 2);
	strcat(out->lexeme, "/");

	return out;
}

static inline Token *greater(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));

    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_GREATER_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, ">=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_GREATER;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, ">");
    
    return out;
}

static inline Token *less(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_LESS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "<=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_LESS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "<");
    
    return out;
}

static inline Token *not(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_NOT_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "!=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_NOT;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "!");
    
    return out;
}

static inline Token *equal(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_EQUAL_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "==");
        (*i)++;
        return out;
    }
    out->type = TOKEN_EQUAL;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "=");
    
    return out;
}

static inline Token *modulo(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_MODULO_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "%=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_MODULO;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "%");
    
    return out;
}

static inline Token *and(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
  	if(code[*i + 1] == '=')
  	{
  	    out->type = TOKEN_AND_EQUAL;
  	    out->lexeme = malloc(sizeof(char) * 3);
  	    strcat(out->lexeme, "&=");
  	    (*i)++;
  	    return out;
  	}
  	else if(code[*i + 1] == '&')
  	{
  	    out->type = TOKEN_LOGIC_AND;
  	    out->lexeme = malloc(sizeof(char) * 3);
  	    strcat(out->lexeme, "&&");
  	    (*i)++;
  	    return out;
  	}
  	out->type = TOKEN_AND;
  	out->lexeme = malloc(sizeof(char) * 2);
  	strcat(out->lexeme, "&");
  
  	return out;
}

static inline Token *xor(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
            
    if(code[*i + 1] == '=')
    {
        out->type = TOKEN_XOR_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcat(out->lexeme, "^=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_XOR;
    out->lexeme = malloc(sizeof(char) * 2);
    strcat(out->lexeme, "^");
    
    return out;
}

static inline Token *or(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
   	if(code[*i + 1] == '=')
   	{
   	    out->type = TOKEN_OR_EQUAL;
   	    out->lexeme = malloc(sizeof(char) * 3);
   	    strcat(out->lexeme, "|=");
   	    (*i)++;
   	    return out;
   	}
   	else if(code[*i + 1] == '|')
   	{
   	    out->type = TOKEN_LOGIC_OR;
   	    out->lexeme = malloc(sizeof(char) * 3);
   	    strcat(out->lexeme, "||");
   	    (*i)++;
   	    return out;
   	}
   	out->type = TOKEN_OR;
   	out->lexeme = malloc(sizeof(char) * 2);
   	strcat(out->lexeme, "|");
   
   	return out;
}

Token *operator(char *code, int *i)
{
    switch(code[*i])
    {
        case '+':
        {
            return plus(code, i);
        }
        case '-':
        {
            return minus(code, i);
        }
        case '*':
        {
            return star(code, i);
        }
        case '/':
        {
            return slash(code, i);
        }
        case '>':
        {
            return greater(code, i);
        }
        case '<':
        {
            return less(code, i);
        }
        case '!':
        {
            return not(code, i);
        }
        case '=':
        {
            return equal(code, i);
        }
        case '%':
        {
            return modulo(code, i);
        }
        case '^':
        {
            return xor(code, i);
        }
        case '&':
        {
            return and(code, i);
        }
        case '|':
        {
            return or(code, i);
        }
        default:
        {
            return NULL;
        }
    }
}

Token *other(char *code, int *i)
{
	if(is_numeric(code[*i]))
	{
		return number(code, i);
	}
	else if(is_alpha(code[*i]))
	{
		return identifier(code, i);
	}
	else
	{
		return NULL;
	}
}

typedef struct
{
    Token **array;
    size_t size;
    size_t capacity;
} TokenList;

void initlist(TokenList **listptr)
{
    TokenList *container = malloc(sizeof(TokenList));

    container->size = 0;
    container->capacity = 8;
    container->array = malloc(8 * sizeof(Token *));

    *listptr = container;
}

void freelist(TokenList *list)
{
    free(list->array);
    free(list);
}

// It took me many many tries to get this entire list system to work, mostly this function
void push(TokenList *list, Token *element)
{
    if(list->size == list->capacity)
    {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(Token *));
    }
    list->array[list->size++] = element;
}

typedef void (*WalkFn)(Token *);

void walk(TokenList *list, WalkFn fn)
{
    for(int i = 0; i < list->size; i++)
    {
        fn(list->array[i]);
    }
}

void analyze(char *code, int *i, TokenList *list)
{
	Token *token;

	switch(code[*i])
    {
        case '+':
        case '-':
        case '*':
        case '/':
        case '>':
        case '<':
        case '!':
        case '=':
        case '%':
        case '^':
        case '&':
        case '|':
        {
            push(list, operator(code, i));
            break;
        }
        case '(':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_PAREN;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "(");
            push(list, token);
            break;
        }
        case ')':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_PAREN;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ")");
            push(list, token);
            break;
        }
        case '[':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_SQUARE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "[");
            push(list, token);
            break;
        }
        case ']':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_SQUARE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "]");
            push(list, token);
            break;
        }
        case '{':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_BRACE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "{");
            push(list, token);
            break;
        }
        case '}':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_BRACE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "}");
            push(list, token);
            break;
        }
        case '\"':
        {
        	push(list, string(code, i));
        	break;
        }
        case '\n':
        case '\t':
        case ' ':
        case ':':
        case ';':
        case EOF:
        {
			return;
        }
        default:
        { 
        	push(list, other(code, i));
        	break;
        }
    }
}

TokenList *tokenize(char *code)
{
    TokenList *list;
    initlist(&list);

    for(int i = 0; i < (int) strlen(code); i++)
    {
        analyze(code, &i, list);
    }

    return list;
}
