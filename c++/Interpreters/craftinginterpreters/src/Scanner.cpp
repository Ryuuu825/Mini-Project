#include "Scanner.hpp"
#include "Runner.hpp"

std::vector<Token::Type> Scanner::get_scanned_tokens()
{
    return this->scanned_token;
}


std::vector<Token::Type> Scanner::rescan(const char* source) 
{
    this->source = source;
    this->scanned_token.clear();
    return this->start_scan();
}

std::vector<Token::Type> Scanner::append_scan(const char* source) 
{
    this->source += source;
    return this->start_scan();
}

std::vector<Token::Type> Scanner::start_scan() 
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
}
Scanner::Scanner(std::string source)
{
    this->source = source;
}

Scanner::Scanner()
{
}
Scanner::~Scanner()
{
    this->scanned_token.clear();
}


void Scanner::add_token(const Token::Type& token_type)
{
    this->scanned_token.push_back(token_type);
}
char Scanner::advance()
{
    this->current_pos++;
    this->current_char = this->source[this->current_pos];
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

bool Scanner::is_at_end()
{
    return this->current_pos >= this->source.size();
}

void Scanner::scan_token()
{
    char c = advance();
    switch (c) {
      case '(': add_token(Token::Type::LEFT_PAREN); break;
      case ')': add_token(Token::Type::RIGHT_PAREN); break;
      case '{': add_token(Token::Type::LEFT_BRACE); break;
      case '}': add_token(Token::Type::RIGHT_BRACE); break;
      case ',': add_token(Token::Type::COMMA); break;
      case '.': add_token(Token::Type::DOT); break;
      case '-': add_token(Token::Type::MINUS); break;
      case '+': add_token(Token::Type::PLUS); break;
      case ';': add_token(Token::Type::SEMICOLON); break;
      case '*': add_token(Token::Type::STAR); break; 
      case '!': add_token(match('=') ? Token::Type::BANG_EQUAL : Token::Type::BANG); break;
      case '=': add_token(match('=') ? Token::Type::EQUAL_EQUAL : Token::Type::EQUAL); break;
      case '<': add_token(match('=') ? Token::Type::LESS_EQUAL : Token::Type::LESS); break;
      case '>': add_token(match('=') ? Token::Type::GREATER_EQUAL : Token::Type::GREATER); break;
      default: Runner::halt("Unknown token", 1); break;
    }
}




#ifdef DEBUG
void Scanner::print_debug_info()
{   
    // print the all scanned tokens
    std::cout << "Scanned tokens: ";
    for (auto token : this->scanned_token) {
        std::cout << token << " ";
    }

}

#endif