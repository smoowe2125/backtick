#pragma once

#include <stdint.h>
#include <stdio.h>
#include <stellarc_utils.h>
#include <sys/types.h>
#include <tokenizer.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct {
    // By storing the iterator directly in the parser
    // we enable ourselves to pass the parser and the parser only
    // to functions used for parsing. No need to pass a pointer to the iterator or anything else.
    int iterator;

    TokenList *tokens;
} Parser;

static void
expression (Parser *);

static void
number (Parser *);

static void
unary (Parser *);

static void
postfix (Parser *);

static void
binary (Parser *);

static void
ternary (Parser *);

static void
grouping (Parser *);

static void
subscript (Parser *);

typedef enum {
    PREC_NONE,

    PREC_ASSIGN,
    PREC_TERNARY,

    PREC_LOGICAL_OR,
    PREC_LOGICAL_AND,

    PREC_BITWISE_OR,
    PREC_BITWISE_XOR,
    PREC_BITWISE_AND,
    
    PREC_EQ_NEQ,
    PREC_GT_LT,

    PREC_BITWISE_LS_RS,

    PREC_TERM,
    PREC_FACTOR,

    PREC_EXPONENT,
    
    PREC_PREFIX,
    PREC_POSTFIX,

    PREC_PRIMARY
} Precedence;

typedef enum {
    OP_PUSH,
    OP_POP,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
    OP_MODULO,

    OP_STORE_VARIABLE,
    OP_SET_VARIABLE,
    OP_GET_VARIABLE,

    OP_PRINTLN,
    OP_PRINT,

    OP_RETURN
} BytecodeInstruction;

typedef struct {
    uint8_t *arr;
    size_t cap;
    size_t size;
} BytecodeChunk;

static void
write_chunk (BytecodeChunk *);

static void
free_chunk (BytecodeChunk *);

typedef void (*ParseFn) (Parser *);

typedef struct {
    Precedence prec;

    ParseFn prefix;
    ParseFn infix;
    ParseFn postfix;
} ParseRule;

ParseRule rule_table[] = {
    [TOKEN_INTEGER] = {PREC_NONE, number, NULL, NULL},
    [TOKEN_FLOAT_LITERAL] = {PREC_NONE, number, NULL, NULL},
    [TOKEN_STR_LITERAL] = {PREC_NONE, NULL, NULL, NULL},
    [TOKEN_TRUE] = {PREC_NONE, NULL, NULL, NULL},
    [TOKEN_FALSE] = {PREC_NONE, NULL, NULL, NULL},

    [TOKEN_PLUS] = {PREC_TERM, unary, binary, NULL},
    [TOKEN_PLUS_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},
    [TOKEN_PLUS_PLUS] = {PREC_POSTFIX, unary, binary, postfix},

    [TOKEN_MINUS] = {PREC_TERM, unary, binary, NULL},
    [TOKEN_MINUS_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},
    [TOKEN_MINUS_MINUS] = {PREC_POSTFIX, unary, binary, postfix},

    [TOKEN_STAR] = {PREC_FACTOR, NULL, binary, NULL},
    [TOKEN_STAR_EQUAL] = {PREC_FACTOR, NULL, binary, NULL},
    [TOKEN_STAR_STAR] = {PREC_EXPONENT, NULL, binary, NULL},

    [TOKEN_SLASH] = {PREC_FACTOR, NULL, binary, NULL},
    [TOKEN_SLASH_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_GREATER] = {PREC_GT_LT, NULL, binary, NULL},
    [TOKEN_GREATER_EQUAL] = {PREC_GT_LT, NULL, binary, NULL},
    [TOKEN_RIGHT_SHIFT] = {PREC_BITWISE_LS_RS, NULL, binary, NULL},
    [TOKEN_RIGHT_SHIFT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_LESS] = {PREC_GT_LT, NULL, binary, NULL},
    [TOKEN_LESS_EQUAL] = {PREC_GT_LT, NULL, binary, NULL},
    [TOKEN_LEFT_SHIFT] = {PREC_BITWISE_LS_RS, NULL, binary, NULL},
    [TOKEN_LEFT_SHIFT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_NOT] = {PREC_PREFIX, unary, NULL, NULL},
    [TOKEN_NOT_EQUAL] = {PREC_EQ_NEQ, NULL, binary, NULL},

    [TOKEN_BITWISE_NOT] = {PREC_PREFIX, unary, NULL, NULL},
    [TOKEN_BITWISE_NOT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},
    [TOKEN_EQUAL_EQUAL] = {PREC_EQ_NEQ, NULL, binary, NULL},

    [TOKEN_MODULO] = {PREC_FACTOR, NULL, binary, NULL},
    [TOKEN_MODULO_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_XOR] = {PREC_BITWISE_XOR, NULL, binary, NULL},
    [TOKEN_XOR_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},

    [TOKEN_AND] = {PREC_BITWISE_AND, NULL, binary, NULL},
    [TOKEN_AND_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},
    [TOKEN_LOGIC_AND] = {PREC_LOGICAL_AND, NULL, binary, NULL},

    [TOKEN_OR] = {PREC_BITWISE_OR, NULL, binary, NULL},
    [TOKEN_OR_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL},
    [TOKEN_LOGIC_OR] = {PREC_LOGICAL_OR, NULL, binary, NULL},

    [TOKEN_OPEN_PAREN] = {PREC_PRIMARY, grouping, NULL, NULL},
    [TOKEN_CLOSE_PAREN] = {PREC_NONE, NULL, NULL, NULL, NULL},

    [TOKEN_OPEN_SQUARE] = {PREC_POSTFIX, NULL, NULL, subscript},
    [TOKEN_CLOSE_SQUARE] = {PREC_NONE, NULL, NULL, NULL},

    [TOKEN_QUESTION_MARK] = {PREC_TERNARY, NULL, ternary, NULL},

    // statements later
};

static void
write_chunk (BytecodeChunk *chunk) {
    if (chunk->size == chunk->cap) {
        
    }
}

static ParseRule *
get_rule (TokenType type) {
    return &rule_table[type];
}

static bool
match (Parser *parser, TokenType type) {
    return parser->tokens->array[parser->iterator + 1]->type == type;
}

static void
consume (Parser *parser, TokenType type, const char *format, ...) {
    if (match (parser, type)) {
        parser->iterator++;
        return;
    }

    va_list args;

    va_start (args, format);

    fprintf (stderr, "[Line %d] ", parser->tokens->array[parser->iterator]->line);
    
    vfprintf (stderr, format, args);

    va_end (args);

    had_error = true;
}

static void
advance (Parser *parser) {
    parser->iterator++;
}

// Sets up the parser just how we like it
static Parser *
make_parser () {
    // I'll just keep using the heap however much I like because it's MY CODE. IT'S MY CODE. MY.
    Parser *parser = malloc (sizeof (Parser));

    parser->iterator = 0;

    return parser;
}

static void
actually_parse (Parser *parser) {
    for (; parser->iterator < parser->tokens->size; parser->iterator++) {
        expression (parser);
    }
}

void
parse (TokenList *tokens) {
    Parser *parser = make_parser ();

    parser->tokens = tokens;

    actually_parse (parser);
}

static void
handle_precedence (Parser *parser, Precedence prec) {
    advance (parser);

    ParseFn prefix = get_rule(parser->tokens->array[parser->iterator - 1]->type)->prefix;

    if (prefix == NULL) {
        REPORT_ERROR (parser->tokens->array[parser->iterator]->line,
                "Expected expression.");
        return;
    }

    prefix (parser);

    while (prec <= get_rule (parser->tokens->array[parser->iterator]->type)->prec) {
        advance (parser);

        ParseFn infix = get_rule (parser->tokens->array[parser->iterator - 1]->type)->infix;

        infix (parser);
    }
}

static void
expression (Parser *parser) {
    handle_precedence (parser, PREC_ASSIGN);
}

static void
number (Parser *parser) {

}

static void
unary (Parser *parser) {

}

static void
binary (Parser *parser) {

}

static void
ternary (Parser *parser) {

}

static void
grouping (Parser *parser) {

}

static void
postfix (Parser *parser) {

}

static void
subscript (Parser *parser) {
    
}
