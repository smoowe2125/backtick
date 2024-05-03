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

typedef enum {
    PREC_NONE,

    PREC_COMMA,
    PREC_ASSIGN,
    PREC_TERNARY,

    PREC_LOGICAL_OR,
    PREC_LOGICAL_AND,

    PREC_BITWISE_OR,
    PREC_BITWISE_XOR,
    PREC_BITWISE_AND,
    
    PREC_COMPARE,

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
