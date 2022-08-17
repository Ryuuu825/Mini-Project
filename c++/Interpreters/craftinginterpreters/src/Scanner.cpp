#include "Scanner.hpp"

std::vector<Token::Type> Scanner::scan(const char* source)
{
    return this->scanned_token;
}