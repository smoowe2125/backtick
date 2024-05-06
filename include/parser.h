#pragma once

#include <stdint.h>
#include <stellarc_utils.h>
#include <sys/types.h>
#include <tokenizer.h>
#include <stdlib.h>

typedef struct {
    // By storing the iterator directly in the parser
    // we enable ourselves to pass the parser and the parser only
    // to functions used for parsing. No need to pass a pointer to the iterator or anything else.
    int iterator;

    TokenList *tokens;
} Parser;

static void
number (Parser *parser);

static void
unary (Parser *parser);

static void
postfix (Parser *parser);

static void
binary (Parser *parser);

static void
ternary (Parser *parser);

static void
grouping (Parser *parser);

static void
subscript (Parser *parser);

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

typedef struct {
    Precedence prec;

    void (*prefix) (Parser *);
    void (*infix) (Parser *);
    void (*postfix) (Parser *);
    void (*mixfix) (Parser *);
} ParseRule;

ParseRule rule_table[] = {
    [TOKEN_INTEGER] = {PREC_NONE, number, NULL, NULL, NULL},
    [TOKEN_FLOAT_LITERAL] = {PREC_NONE, number, NULL, NULL, NULL},
    [TOKEN_STR_LITERAL] = {PREC_NONE, NULL, NULL, NULL, NULL},
    [TOKEN_TRUE] = {PREC_NONE, NULL, NULL, NULL, NULL},
    [TOKEN_FALSE] = {PREC_NONE, NULL, NULL, NULL, NULL},

    [TOKEN_PLUS] = {PREC_TERM, unary, binary, NULL, NULL},
    [TOKEN_PLUS_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},
    [TOKEN_PLUS_PLUS] = {PREC_POSTFIX, unary, binary, postfix, NULL},

    [TOKEN_MINUS] = {PREC_TERM, unary, binary, NULL, NULL},
    [TOKEN_MINUS_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},
    [TOKEN_MINUS_MINUS] = {PREC_POSTFIX, unary, binary, postfix, NULL},

    [TOKEN_STAR] = {PREC_FACTOR, NULL, binary, NULL, NULL},
    [TOKEN_STAR_EQUAL] = {PREC_FACTOR, NULL, binary, NULL, NULL},
    [TOKEN_STAR_STAR] = {PREC_EXPONENT, NULL, binary, NULL, NULL},

    [TOKEN_SLASH] = {PREC_FACTOR, NULL, binary, NULL, NULL},
    [TOKEN_SLASH_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_GREATER] = {PREC_GT_LT, NULL, binary, NULL, NULL},
    [TOKEN_GREATER_EQUAL] = {PREC_GT_LT, NULL, binary, NULL, NULL},
    [TOKEN_RIGHT_SHIFT] = {PREC_BITWISE_LS_RS, NULL, binary, NULL, NULL},
    [TOKEN_RIGHT_SHIFT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_LESS] = {PREC_GT_LT, NULL, binary, NULL, NULL},
    [TOKEN_LESS_EQUAL] = {PREC_GT_LT, NULL, binary, NULL, NULL},
    [TOKEN_LEFT_SHIFT] = {PREC_BITWISE_LS_RS, NULL, binary, NULL, NULL},
    [TOKEN_LEFT_SHIFT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_NOT] = {PREC_PREFIX, unary, NULL, NULL, NULL},
    [TOKEN_NOT_EQUAL] = {PREC_EQ_NEQ, NULL, binary, NULL, NULL},

    [TOKEN_BITWISE_NOT] = {PREC_PREFIX, unary, NULL, NULL, NULL},
    [TOKEN_BITWISE_NOT_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},
    [TOKEN_EQUAL_EQUAL] = {PREC_EQ_NEQ, NULL, binary, NULL, NULL},

    [TOKEN_MODULO] = {PREC_FACTOR, NULL, binary, NULL, NULL},
    [TOKEN_MODULO_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_XOR] = {PREC_BITWISE_XOR, NULL, binary, NULL, NULL},
    [TOKEN_XOR_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},

    [TOKEN_AND] = {PREC_BITWISE_AND, NULL, binary, NULL, NULL},
    [TOKEN_AND_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},
    [TOKEN_LOGIC_AND] = {PREC_LOGICAL_AND, NULL, binary, NULL, NULL},

    [TOKEN_OR] = {PREC_BITWISE_OR, NULL, binary, NULL, NULL},
    [TOKEN_OR_EQUAL] = {PREC_ASSIGN, NULL, binary, NULL, NULL},
    [TOKEN_LOGIC_OR] = {PREC_LOGICAL_OR, NULL, binary, NULL, NULL},

    [TOKEN_OPEN_PAREN] = {PREC_PRIMARY, grouping, NULL, NULL, NULL},
    [TOKEN_CLOSE_PAREN] = {PREC_NONE, NULL, NULL, NULL, NULL, NULL},

    [TOKEN_OPEN_SQUARE] = {PREC_POSTFIX, NULL, NULL, subscript, NULL},
    [TOKEN_CLOSE_SQUARE] = {PREC_NONE, NULL, NULL, NULL, NULL},

    // statements later
};

static ParseRule *
get_rule (TokenType type) {
    return &rule_table[type];
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

}

static void
expression (Parser *parser) {

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
