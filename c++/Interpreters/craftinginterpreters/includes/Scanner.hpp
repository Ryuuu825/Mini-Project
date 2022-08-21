#pragma once 

#include "common.hpp"
#include "Token.hpp"

#include <map>

class Scanner
{
    public:
        Scanner(const char* source);
        Scanner(std::string source);
        Scanner();
        ~Scanner();
        
        // start to scan the source
        std::vector<Token> start_scan() ;
        std::vector<Token> rescan(const char* source) ;
        std::vector<Token> append_scan(const char* source) ;
        std::vector<Token> get_scanned_tokens();

        std::string scan_string();
        std::string scan_number();
        std::string scan_identifier();


        char peek() const; // peek the next char
        char peek(int index) const; // peek the next char
        
        void set_source(const char* source);
        void set_source(std::string source);

        void print_debug_info();

    private:
        std::string source;
        std::vector<Token> scanned_token;
        static std::map<std::string, TokenType> keywords;

        // state 
        unsigned long current_line = 0;
        unsigned int current_row_index = 0;
        unsigned long current_pos = 0;

        char current_char;
        std::string current_buffer;
        std::string current_token;

        // method
        char advance();
        bool is_at_end() const;
        bool match(const char& expected);

        void add_token(const TokenType& token_type);
        void add_token(const TokenType& token_type, const std::string& literal);
        void scan_token();
        
        void clear_state();

        bool is_digit(char c) const;
        bool is_identifier() const;
        bool is_alpha(char c) const;

};