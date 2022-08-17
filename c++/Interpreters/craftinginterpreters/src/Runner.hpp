#pragma once 

#include "common.hpp"
#include <optional>


class Runner {
    public: 
        // method
        static void run_file(const char* filename);
        static void run_prompt();
        static void run_line(const char* line);
        static void halt(const int exit_code);


    private: 
        Runner();
        ~Runner();

        static void error(const char* message , const int exit_code);
        static void error(const std::string& message , const int exit_code);
        static bool is_error;
};