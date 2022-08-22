#pragma once 

#include <string>

class Object 
{
    public:
        Object();
        ~Object();

        virtual std::string to_string() const;
        std::string class_name = "Object";

};