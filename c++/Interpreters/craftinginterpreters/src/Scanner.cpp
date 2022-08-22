#include "Scanner.hpp"
#include "Runner.hpp"
#include <sstream>

std::map<std::string , TokenType> Scanner::keywords = {
    {"and" , AND},
    {"struct" , STRUCT},
    {"else" , ELSE},
    {"if" , IF},
    {"nil" , NIL},
    {"or" , OR},
    {"see" , SEE},
    {"seeout" , SEEOUT},
    {"seererr" , SEEERR},
    {"return" , RETURN},
    {"super" , SUPER},
    {"self" , SELF},
    {"while" , WHILE},
    {"for" , FOR},
    {"var" , VAR},
    {"let" , LET},
    {"arr" , ARR},
    {"tup" , TUP},
    {"ref" , REF},
    {"mref" , MREF},
    {"move" , MOVE},
    {"golvar" , GOLVAR},
    {"svar" , SVAR},
    {"const" , CONST},
    {"auto" , AUTO},
    {"heap" , HEAP},
    {"delete" , DELETE},
    {"create" , CREATE},
    {"is" , IS},
    {"enum" , ENUM},
    {"extension" , EXTENSION},
    {"public" , PUBLIC},
    {"private" , PRIVATE},
    {"macro" , MACRO},
    {"true" , TRUE},
    {"false" , FALSE},
    {"nil" , NIL},
    {"try" , TRY},
    {"catch" , CATCH},
    {"finally" , FINALLY},
    {"throw" , THROW},
    {"import" , IMPORT},
    {"namespace" , NAMESPACE},
    {"typeof" , TYPEOF},
    {"nameof" , NAMEOF},
    {"sizeof" , SIZEOF},
    {"in" , IN},
};

std::vector<Token> Scanner::get_scanned_tokens()
{
    return this->scanned_token;
}

void Scanner::clear_state()
{
    this->current_line = 0;
    this->current_row_index = 0;
    this->current_pos = 0;
    this->current_char = '\0';
    this->current_buffer = "";
    this->current_token = "";
    this->scanned_token.clear();
    this->source.clear();
}


std::vector<Token> Scanner::rescan(const char* source) 
{
    clear_state();
    this->source = source;
    this->scanned_token.clear();
    return this->start_scan();
}

std::vector<Token> Scanner::append_scan(const char* source) 
{
    this->source += source;
    while(!this->is_at_end())
    {
        this->scan_token();
    }
    return this->scanned_token;
}

std::vector<Token> Scanner::start_scan() 
{
    this->scanned_token.clear();
    this->scan_token();
    #ifdef DEBUG
        this->print_debug_info();
    #endif
    return this->scanned_token;
}

bool Scanner::is_at_end() const
{
    return this->current_pos >= this->source.size();
}

Scanner::Scanner(const char* source)
{
    this->source = source;
    assert(this->source.size() > 0);
    this->current_line = 0;
    this->current_row_index = 0;
    this->current_pos = 0;
    this->current_char = source[0];
    this->current_buffer = "";
    this->current_token = "";
}
Scanner::Scanner(std::string source)
{
    this->source = source;
    assert(this->source.size() > 0);
    this->current_line = 0;
    this->current_row_index = 0;
    this->current_pos = 0;
    this->current_char = source[0];
    this->current_buffer = "";
    this->current_token = "";
}

Scanner::Scanner()
{
    this->current_line = 0;
    this->current_row_index = 0;
    this->current_pos = 0;
    this->current_char = '\0';
    this->current_buffer = "";
    this->current_token = "";
}
Scanner::~Scanner()
{
    this->scanned_token.clear();
}


void Scanner::add_token(const TokenType& token_type)
{
    this->scanned_token.push_back(Token(token_type));
}
char Scanner::advance()
{
    this->current_char = this->source[this->current_pos++];
    this->current_row_index++;
    return this->current_char;
}

bool Scanner::match(const char& expected)
{
    if (is_at_end()) return false;
    if (this->source[current_pos] != expected) return false;
    current_pos++;
    return true;
}

void Scanner::set_source(const char* source)
{
    this->source = source;
}

void Scanner::set_source(std::string source)
{
    this->source = source;
}


char Scanner::peek() const  {
    return this->source[this->current_pos + 1];
}
char Scanner::peek(int index) const  {
    return this->source[this->current_pos + index];
}

void Scanner::scan_token()
{
    char c = advance();
    switch (c) {
        case '(': add_token(TokenType::LEFT_PAREN); break;
        case ')': add_token(TokenType::RIGHT_PAREN); break;
        case '{': add_token(TokenType::LEFT_BRACE); break;
        case '}': add_token(TokenType::RIGHT_BRACE); break;
        case ',': add_token(TokenType::COMMA); break;
        case '.': add_token(TokenType::DOT); break;
        case '-': add_token(TokenType::MINUS); break;
        case '+': add_token(TokenType::PLUS); break;
        case ';': add_token(TokenType::SEMICOLON); break;
        case '*': add_token(TokenType::STAR); break; 
        case '!': add_token(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG); break;
        case '=': add_token(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL); break;
        case '<': add_token(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS); break;
        case '>': add_token(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER); break;
        case '/':
        {
            if (match('/')) {
                while (peek() != '\n' && !is_at_end()) {
                    advance();
                }
            } else if (match('*')){
                while (peek() != '*' && peek(1) != '/' && !is_at_end()) {
                    advance();
                }
                advance(); // skip *
                advance(); // skip /
            } 
            else {
                add_token(TokenType::SLASH);
            }
            break;
        }
        case ' ':
        case '\r':
        case '\t':
            break;
        case '\n':
        {
            this->current_line++;
            this->current_row_index = 0;
            break;
        }
        case '"':
        {
            std::string string = this->scan_string();
            add_token(TokenType::STRING, string);
            break;
        }
        case ':':
        {
            add_token(TokenType::COLON);
            break;
        }
        default: 
            if (isnumber(c)) {
                std::string number = this->scan_number();
                add_token(TokenType::NUMBER, number);
            } 
            else if (is_alpha(c))
            {
                std::string identifier = this->scan_identifier();
                TokenType token_type = this->keywords.find(identifier) != this->keywords.end() ? this->keywords.at(identifier) : TokenType::IDENTIFIER;
                add_token(token_type, identifier);
            }
            else {
                Runner::error(this->current_line, this->current_row_index, "Unexpected character.");
            }
    }

}

std::string Scanner::scan_string()
{
    std::string string = "";
    while (peek() != '"' && !is_at_end()) {
        char c = advance();
        if (c == '\n') {
            Runner::error("Newline in string");
        }
        string += c;
    }

    if (string.size() == 1 && string[0] == '"') {
        return ""; // empty string
    }
    else  {
        // if we call advance() here
        // it will return the previous char before the "
        char c = advance();  
        string += c;
        // if we call advance() here
        // it will return "
        advance();
        return string;
    }
   
}


void Scanner::print_debug_info()
{   
    // print the all scanned tokens
    std::cout << "Scanned tokens: " << this->scanned_token.size() << std::endl;
    for (auto token : this->scanned_token) {
        std::cout << token_type_name(token.type) << " " << token.literal << std::endl;
    }
}

void Scanner::add_token(const TokenType& token_type, const std::string& literal)
{
    this->scanned_token.push_back(Token(token_type, literal));
}

bool Scanner::is_digit(char c) const
{
    return c >= '0' && c <= '9';
}

std::string Scanner::scan_number()
{
    std::string number = "";
    number+= this->current_char;
    while (is_digit(peek())) {
        number += advance();
    }
    if (peek() == '.' && is_digit(peek(2))) {
        number += advance();
        while (is_digit(peek())) {
            number += advance();
        }
    }

    if (is_digit(this->current_char))
    {
        number += advance();
    }
    return number;
}


std::string Scanner::scan_identifier()
{
    std::string identifier = "";
    identifier += this->current_char;
    while (is_alpha(peek())) {
        identifier += advance();
    }
    if (is_alpha(this->current_char))
    {
        identifier += advance();
    }
    return identifier;
}

bool Scanner::is_alpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

