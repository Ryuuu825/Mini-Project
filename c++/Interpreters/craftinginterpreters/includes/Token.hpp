#pragma once 

#include <string>

typedef enum TokenType {
    // Single-character tokens.
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,
    QUESTION, COLON, PERCENT,
    // One or two character tokens.
    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,
    // Literals.
    IDENTIFIER, STRING, NUMBER,
    // Keywords.
    AND, STRUCT, ELSE, IF, OR,
    SEE, SEEOUT, SEEERR, RETURN, SUPER, SELF, WHILE, FOR,
    VAR , LET, ARR, TUP, REF, MREF, MOVE, GOLVAR, SVAR, CONST, AUTO, HEAP, DELETE, CREATE,
    IS , ENUM, EXTENSION, PUBLIC, PRIVATE, MACRO, TRUE, FALSE, NIL, TRY, CATCH, FINALLY, THROW,
    IMPORT, NAMESPACE, TYPEOF, NAMEOF, SIZEOF, IN, 
    // End of file.
    ENDOFFILE
} Type;

class Token {
public:
    Token(const TokenType& type, const std::string& literal) : type(type), literal(literal) {}
    Token(const TokenType& type) : type(type) {}
    Token() {}
    Type type;
    std::string literal;
};

#define DEBUG 

#ifdef DEBUG
const char* token_type_name(Type type);
#endif 