#include "Token.hpp"
#include "common.hpp"

/*
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
*/
#ifdef DEBUG

const char* token_type_name(Type type)
{
    switch (type) {
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case LEFT_BRACE: return "LEFT_BRACE";
        case RIGHT_BRACE: return "RIGHT_BRACE";
        case COMMA: return "COMMA";
        case DOT: return "DOT";
        case MINUS: return "MINUS";
        case PLUS: return "PLUS";
        case SEMICOLON: return "SEMICOLON";
        case SLASH: return "SLASH";
        case STAR: return "STAR";
        case QUESTION: return "QUESTION";
        case COLON: return "COLON";
        case PERCENT: return "PERCENT";
        case BANG: return "BANG";
        case BANG_EQUAL: return "BANG_EQUAL";
        case EQUAL: return "EQUAL";
        case EQUAL_EQUAL: return "EQUAL_EQUAL";
        case GREATER: return "GREATER";
        case GREATER_EQUAL: return "GREATER_EQUAL";
        case LESS: return "LESS";
        case LESS_EQUAL: return "LESS_EQUAL";
        case IDENTIFIER: return "IDENTIFIER";
        case STRING: return "STRING";
        case NUMBER: return "NUMBER";
        case AND: return "AND";
        case STRUCT: return "STRUCT";
        case ELSE: return "ELSE";
        case IF: return "IF";
        case OR: return "OR";
        case SEE: return "SEE";
        case SEEOUT: return "SEEOUT";
        case SEEERR: return "SEEERR";
        case RETURN: return "RETURN";
        case SUPER: return "SUPER";
        case SELF: return "SELF";
        case WHILE: return "WHILE";
        case FOR: return "FOR";
        case VAR : return "VAR";
        case LET:   return "LET";
        case ARR:   return "ARR";
        case TUP:   return "TUP";
        case REF:   return "REF";
        case MREF:  return "MREF";
        case MOVE:  return "MOVE";
        case GOLVAR:return "GOLVAR";
        case SVAR:  return "SVAR";
        case CONST: return "CONST";
        case AUTO:  return "AUTO";
        case HEAP:  return "HEAP";
        case DELETE:return "DELETE";
        case CREATE:return "CREATE";
        case IS:    return "IS";
        case ENUM:  return "ENUM";
        case EXTENSION: return "EXTENSION";
        case PUBLIC: return "PUBLIC";
        case PRIVATE: return "PRIVATE";
        case MACRO: return "MACRO";
        case TRUE: return "TRUE";
        case FALSE: return "FALSE";
        case NIL: return "NIL";
        case TRY: return "TRY";
        case CATCH: return "CATCH";
        case FINALLY: return "FINALLY";
        case THROW: return "THROW";
        case IMPORT: return "IMPORT";
        case NAMESPACE: return "NAMESPACE";
        case TYPEOF: return "TYPEOF";
        case NAMEOF: return "NAMEOF";
        case SIZEOF: return "SIZEOF";
        case IN: return "IN";
        case ENDOFFILE: return "ENDOFFILE";
        default: return "UNKNOWN";
    }
}

#endif 
