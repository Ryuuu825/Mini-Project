#pragma once 

#include "common.hpp"
#include "Scanner.hpp"
#include <optional>
#include <fstream>

class Runner {
    public: 
        // method
        static void run_file(const char* filename);
        static void run_prompt();
        static void run_line(const char* line);
        
        static void error(const char* message);
        static void error(const std::string& message);
        static void error(const int line, const int row, const char* message);
        static void fatal_error(const char* message , const int exit_code);
        static void fatal_error(const std::string& message , const int exit_code);



    private: 
        Runner();
        ~Runner();

        static void halt(const int exit_code);
        static void halt(const char* msg, const int exit_code);

        static Scanner scanner;
        static std::string source;

        static bool is_error;
};