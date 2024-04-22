#pragma once

#include <backtick_utils.h>

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
    TOKEN_IMPORT,
    TOKEN_RETURN,
    TOKEN_THROW,
    TOKEN_CATCH,
    TOKEN_FINALLY,
    TOKEN_SWITCH,
    TOKEN_CASE,
    TOKEN_DEFAULT,
    TOKEN_BREAK,
    TOKEN_CONTINUE,

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

    TOKEN_INTEGER,
    TOKEN_FLOAT_LITERAL,

    TOKEN_TRUE,
    TOKEN_FALSE,

    TOKEN_STR_LITERAL,

    TOKEN_CHARACTER_LITERAL,

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

    TOKEN_GREATER,
    TOKEN_GREATER_EQUAL,
    TOKEN_RIGHT_SHIFT,
    TOKEN_RIGHT_SHIFT_EQUAL,
    
    TOKEN_LESS,
    TOKEN_LESS_EQUAL,
    TOKEN_LEFT_SHIFT,
    TOKEN_LEFT_SHIFT_EQUAL,
    
    TOKEN_NOT,
    TOKEN_NOT_EQUAL,

    TOKEN_BITWISE_NOT,
    TOKEN_BITWISE_NOT_EQUAL,

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

    TOKEN_COMMA,
    TOKEN_DOT,
    TOKEN_QUESTION_MARK,
    TOKEN_BACKSLASH,
    TOKEN_AT,
    TOKEN_HASHTAG,
    TOKEN_DOLLAR,
    TOKEN_COLON,

    TOKEN_SEMICOLON,

    TOKEN_IDENTIFIER,

    TOKEN_EOF
} TokenType;

int current_line = 1;

typedef struct
{
    TokenType type;
    char *lexeme;
    int line;
} Token;

bool is_numeric(char c)
{
    return c >= '0' && c <= '9';
}

bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool is_alpha_numeric(char c)
{
    return is_alpha(c) || is_numeric(c);
}

static inline Token *lex_string(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    (*i)++;

    while(code[*i] != '\"')
    {
        if(code[*i] == EOF) { REPORT_ERROR(SCAN_ERROR, current_line, "Unterminated string.\n"); break; }
        else if(code[*i] == '\n') continue;
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

    out->type = TOKEN_STR_LITERAL;

    return out;
}

static inline Token *lex_number(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    while(code[*i] != EOF && is_numeric(code[*i]))
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

    if(code[*i] != '.')
    {
        out->type = TOKEN_INTEGER;
        return out;
    }

    if(*i + 1 < strlen(code) && is_numeric(code[*i + 1]))
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
        while(is_numeric(code[*i]))
        {
            cc[0] = code[*i];

            out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

            strcat(out->lexeme, cc);

            (*i)++;
        }
    }

	out->type = TOKEN_FLOAT_LITERAL;

    return out;
}

static inline Token *lex_identifier(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    out->lexeme = malloc(sizeof(char));

    char cc[2];

    cc[1] = '\0';

    strcpy(out->lexeme, "");

    while(code[*i] != EOF && is_alpha_numeric(code[*i]))
    {
        cc[0] = code[*i];

        out->lexeme = realloc(out->lexeme, strlen(out->lexeme) + strlen(cc) + 1);

        strcat(out->lexeme, cc);

        (*i)++;
    }

    out->type = TOKEN_IDENTIFIER;

    if(compare(out->lexeme, "int8") || compare(out->lexeme, "i8"))
    {
        out->type = TOKEN_INT8;
    }
    else if(compare(out->lexeme, "int16") || compare(out->lexeme, "i16"))
    {
        out->type = TOKEN_INT16;
    }
    else if(compare(out->lexeme, "int32") || compare(out->lexeme, "int") || compare(out->lexeme, "i32"))
    {
        out->type = TOKEN_INT32;
    }
    else if(compare(out->lexeme, "int64") || compare(out->lexeme, "i64"))
    {
        out->type = TOKEN_INT64;
    }
    else if(compare(out->lexeme, "uint8") || compare(out->lexeme, "u8"))
    {
        out->type = TOKEN_UINT8;
    }
    else if(compare(out->lexeme, "uint16") || compare(out->lexeme, "u16"))
    {
        out->type = TOKEN_UINT16;
    }
    else if(compare(out->lexeme, "uint32") || compare(out->lexeme, "uint") || compare(out->lexeme, "u32"))
    {
        out->type = TOKEN_UINT32;
    }
    else if(compare(out->lexeme, "uint64") || compare(out->lexeme, "u64"))
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
    else if(compare(out->lexeme, "bool") || compare(out->lexeme, "boolean") || compare(out->lexeme, "boole") || compare(out->lexeme, "Boole"))
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
    else if(compare(out->lexeme, "import"))
    {
    	out->type = TOKEN_IMPORT;
    }
    else if(compare(out->lexeme, "return"))
    {
        out->type = TOKEN_RETURN;
    }
    else if(compare(out->lexeme, "throw"))
    {
        out->type = TOKEN_THROW;
    }
    else if(compare(out->lexeme, "catch"))
    {
        out->type = TOKEN_CATCH;
    }
    else if(compare(out->lexeme, "finally"))
    {
        out->type = TOKEN_FINALLY;
    }
    else if(compare(out->lexeme, "switch"))
    {
        out->type = TOKEN_SWITCH;
    }
    else if(compare(out->lexeme, "case"))
    {
        out->type = TOKEN_CASE;
    }
    else if(compare(out->lexeme, "default"))
    {
        out->type = TOKEN_DEFAULT;
    }
    else if(compare(out->lexeme, "break"))
    {
        out->type = TOKEN_BREAK;
    }
    else if(compare(out->lexeme, "continue"))
    {
        out->type = TOKEN_CONTINUE;
    }

    (*i)--;

    return out;
}

// I have decided that I'm a never nester so check this shit out

static inline Token *plus(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));

    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_PLUS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "+=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] != EOF && code[*i + 1] == '+')
    {
        out->type = TOKEN_PLUS_PLUS;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "++");
        (*i)++;
        return out;
    }
    out->type = TOKEN_PLUS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "+");
    
    return out;
}

// Basically the same thing as the plus function but it covers minus
// (i know, very surprising, the name didn't give that out)
static inline Token *minus(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_MINUS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "-=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] != EOF && code[*i + 1] == '-')
    {
        out->type = TOKEN_MINUS_MINUS;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "--");
        (*i)++;
        return out;
    }
    out->type = TOKEN_MINUS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "-");
    
    return out;
}

static inline Token *star(char *code, int *i)
{
	Token *out = malloc(sizeof(Token));

    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_STAR_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "*=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] != EOF && code[*i + 1] == '*')
    {
        out->type = TOKEN_STAR_STAR;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "**");
        (*i)++;
        return out;
    }
    out->type = TOKEN_STAR;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "*");
    
    return out;
}

static inline Token *slash(char *code, int *i)
{
	Token *out = malloc(sizeof(Token));
    
	if(code[*i + 1] != EOF && code[*i + 1] == '=')
	{
	    out->type = TOKEN_SLASH_EQUAL;
	    out->lexeme = malloc(sizeof(char) * 3);
	    strcpy(out->lexeme, "/=");
	    (*i)++;
	    return out;
	}
	out->type = TOKEN_SLASH;
	out->lexeme = malloc(sizeof(char) * 2);
	strcpy(out->lexeme, "/");

	return out;
}

static inline Token *greater(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));

    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_GREATER_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, ">=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] != EOF && code[*i + 1] == '>')
    {
        if(code[*i + 2] != EOF && code[*i + 2] == '=')
        {
            out->type = TOKEN_RIGHT_SHIFT_EQUAL;
            out->lexeme = malloc(sizeof(char) * 4);
            strcpy(out->lexeme, ">>=");
            (*i) += 2;
            return out;
        }
        out->type = TOKEN_RIGHT_SHIFT;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, ">>");
        (*i)++;
        return out;
    }
    out->type = TOKEN_GREATER;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, ">");
    
    return out;
}

static inline Token *less(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
    
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_LESS_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "<=");
        (*i)++;
        return out;
    }
    else if(code[*i + 1] != EOF && code[*i + 1] == '<')
    {
        if(code[*i + 2] != EOF && code[*i + 2] == '=')
        {
            out->type = TOKEN_LEFT_SHIFT_EQUAL;
            out->lexeme = malloc(sizeof(char) * 4);
            strcpy(out->lexeme, "<<=");
            (*i) += 2;
            return out;
        }
        out->type = TOKEN_LEFT_SHIFT;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "<<");
        (*i)++;
        return out;
    }
    out->type = TOKEN_LESS;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "<");
    
    return out;
}

static inline Token *not_(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_NOT_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "!=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_NOT;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "!");
    
    return out;
}

static inline Token *equal(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_EQUAL_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "==");
        (*i)++;
        return out;
    }
    out->type = TOKEN_EQUAL;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "=");
    
    return out;
}

static inline Token *modulo(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_MODULO_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "%=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_MODULO;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "%");
    
    return out;
}

static inline Token *and_(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
  	if(code[*i + 1] != EOF && code[*i + 1] == '=')
  	{
  	    out->type = TOKEN_AND_EQUAL;
  	    out->lexeme = malloc(sizeof(char) * 3);
  	    strcpy(out->lexeme, "&=");
  	    (*i)++;
  	    return out;
  	}
  	else if(code[*i + 1] != EOF && code[*i + 1] == '&')
  	{
  	    out->type = TOKEN_LOGIC_AND;
  	    out->lexeme = malloc(sizeof(char) * 3);
  	    strcpy(out->lexeme, "&&");
  	    (*i)++;
  	    return out;
  	}
  	out->type = TOKEN_AND;
  	out->lexeme = malloc(sizeof(char) * 2);
  	strcpy(out->lexeme, "&");
  
  	return out;
}

static inline Token *xor_(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
            
    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_XOR_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "^=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_XOR;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "^");
    
    return out;
}

static inline Token *or_(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));
        
   	if(code[*i + 1] != EOF && code[*i + 1] == '=')
   	{
   	    out->type = TOKEN_OR_EQUAL;
   	    out->lexeme = malloc(sizeof(char) * 3);
   	    strcpy(out->lexeme, "|=");
   	    (*i)++;
   	    return out;
   	}
   	else if(code[*i + 1] != EOF && code[*i + 1] == '|')
   	{
   	    out->type = TOKEN_LOGIC_OR;
   	    out->lexeme = malloc(sizeof(char) * 3);
   	    strcpy(out->lexeme, "||");
   	    (*i)++;
   	    return out;
   	}
   	out->type = TOKEN_OR;
   	out->lexeme = malloc(sizeof(char) * 2);
   	strcpy(out->lexeme, "|");
   
   	return out;
}

static inline Token *bitwise_not(char *code, int *i)
{
    Token *out = malloc(sizeof(Token));

    if(code[*i + 1] != EOF && code[*i + 1] == '=')
    {
        out->type = TOKEN_BITWISE_NOT_EQUAL;
        out->lexeme = malloc(sizeof(char) * 3);
        strcpy(out->lexeme, "~=");
        (*i)++;
        return out;
    }
    out->type = TOKEN_BITWISE_NOT;
    out->lexeme = malloc(sizeof(char) * 2);
    strcpy(out->lexeme, "~");

    return out;
}

static inline Token *operator_(char *code, int *i)
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
            return not_(code, i);
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
            return xor_(code, i);
        }
        case '&':
        {
            return and_(code, i);
        }
        case '|':
        {
            return or_(code, i);
        }
        case '~':
        {
            return bitwise_not(code, i);
        }
        default:
        {
            return NULL;
        }
    }
}

static inline Token *other(char *code, int *i)
{
	if(is_numeric(code[*i]))
	{
		Token *temp = lex_number(code, i);
        (*i)--;
        return temp;
	}
	else if(is_alpha(code[*i]))
	{
		return lex_identifier(code, i);
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

void init_token_list(TokenList **listptr)
{
    TokenList *container = malloc(sizeof(TokenList));

    container->size = 0;
    container->capacity = 8;
    container->array = malloc(8 * sizeof(Token *));

    *listptr = container;
}

void free_token_list(TokenList *list)
{
    free(list->array);
    free(list);
}

// It took me many many tries to get this entire list system to work, mostly this function
void append_token(TokenList *list, Token *element)
{
    if(!element) return;

    element->line = current_line;

    if(list->size == list->capacity)
    {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(Token *));
    }
    list->array[list->size++] = element;
}

typedef void (*TokenWalkFn)(Token*);

void walk_token_list(TokenList *list, TokenWalkFn fn)
{
    for(int i = 0; i < list->size; i++)
    {
        fn(list->array[i]);
    }
}

static inline Token *comment_stuff(char *code, int *i, TokenList *list)
{
    if(code[(*i) + 1] == '/')
    {
        while(code[*i] != '\n' && code[*i] != EOF)
        {
            (*i)++;
        }
        return NULL;
    }

    return slash(code, i);
}

static inline void analyze(char *code, int *i, TokenList *list)
{
	Token *token;

	switch(code[*i])
    {
        case '/':
            append_token(list, comment_stuff(code, i, list));
            break;
        case '+':
        case '-':
        case '*':
        case '>':
        case '<':
        case '!':
        case '=':
        case '%':
        case '^':
        case '&':
        case '|':
        case '~':
        {
            append_token(list, operator_(code, i));
            break;
        }
        case '(':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_PAREN;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "(");
            append_token(list, token);
            break;
        }
        case ')':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_PAREN;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ")");
            append_token(list, token);
            break;
        }
        case '[':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_SQUARE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "[");
            append_token(list, token);
            break;
        }
        case ']':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_SQUARE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "]");
            append_token(list, token);
            break;
        }
        case '{':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_OPEN_BRACE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "{");
            append_token(list, token);
            break;
        }
        case '}':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_CLOSE_BRACE;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "}");
            append_token(list, token);
            break;
        }
        case '.':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_DOT;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ".");
            append_token(list, token);
            break;
        }
        case ',':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_COMMA;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ",");
            append_token(list, token);
            break;
        }
        case '?':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_QUESTION_MARK;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "?");
            append_token(list, token);
            break;
        }
        case '\\':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_BACKSLASH;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "\\");
            append_token(list, token);
            break;
        }
        case '@':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_AT;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "@");
            append_token(list, token);
            break;
        }
        case '#':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_HASHTAG;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "#");
            append_token(list, token);
            break;
        }
        case '$':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_DOLLAR;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, "$");
            append_token(list, token);
            break;
        }
        case ':':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_COLON;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ":");
            append_token(list, token);
            break;
        }
        case ';':
        {
            token = malloc(sizeof(Token));
            token->type = TOKEN_SEMICOLON;
            token->lexeme = malloc(2 * sizeof(char));
            strcpy(token->lexeme, ";");
            append_token(list, token);
            break;
        }
        case '\'':
        {
            // append_token(list, char_literal(code, i));
            break;
        }
        case '\"':
        {
        	append_token(list, lex_string(code, i));
        	break;
        }
        default:
        { 
        	append_token(list, other(code, i));
        	break;
        }
    }
}

TokenList *tokenize(char *code)
{
    TokenList *list;
    init_token_list(&list);

    for(int i = 0; i < (int) strlen(code); i++)
    {
        analyze(code, &i, list);
        if(code[i] == '\n' || code[i] == '\r')
        {
            current_line++;
        }
    }

    Token *eof = malloc(sizeof(Token));

    eof->lexeme = malloc(sizeof(char) * 4);
    eof->type = TOKEN_EOF;
    strcpy(eof->lexeme, "EOF");

    append_token(list, eof);

    return list;
}
