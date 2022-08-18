#pragma once 

#include "common.hpp"
#include "Token.hpp"

class Scanner
{
    public:
        Scanner(const char* source);
        Scanner(std::string source);
        Scanner();
        ~Scanner();
        
        // start to scan the source
        std::vector<Token::Type> start_scan() ;
        std::vector<Token::Type> rescan(const char* source) ;
        std::vector<Token::Type> append_scan(const char* source) ;
        std::vector<Token::Type> get_scanned_tokens();
        
        void set_source(const char* source);
        void set_source(std::string source);


    private:
        std::string source;
        std::vector<Token::Type> scanned_token;

        // state 
        unsigned long current_line = 0;
        unsigned int current_row_index = 0;
        unsigned long current_pos = 0;

        char current_char;
        std::string current_buffer;
        std::string current_token;

        // method
        bool is_at_end() const;
        void add_token(const Token::Type& token_type);
        void scan_token();
        char advance();
        bool match(const char& expected);
        bool is_at_end();

        #ifdef DEBUG

            void print_debug_info();

        #endif
};