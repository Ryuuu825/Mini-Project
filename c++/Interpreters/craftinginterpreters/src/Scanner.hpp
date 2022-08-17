#pragma once 

#include "common.hpp"
#include "Token.hpp"

class Scanner
{
    public:
        std::vector<Token::Type> scan(const char* source);
        std::vector<Token::Type> scan(const std::string& source);

        // member 
        std::vector<Token::Type> scanned_token;

};