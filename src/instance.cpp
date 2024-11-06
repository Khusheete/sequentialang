/*
    MIT License
    
    Copyright (c) 2024 Souchet Ferdinand
    
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:
    
    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <sys/types.h>

#include "instance.hpp"
#include "utils.h"


Instance::Instance() {}
Instance::~Instance() {}


void Instance::execute_file(char *file_path) {
    exec_stream.open(file_path);

    WARNING(!exec_stream.is_open(),
        return;
    , "Could not open file %s.", file_path);


    // Preprocess
    while (exec_stream.good()) {
        std::string token = consume_token();

        if (token.length() == 0) break;

        for (Function f : preproc_funcs) {
            if (f.is_function_for(token)) {
                f.execute(token);
                break;
            }
        }
    }

    // Go back to the start
    exec_stream.close();
    exec_stream.open(file_path);


    // Execute
    while (exec_stream.good()) {
        bool exec = false;

        std::string token = consume_token();

        if (token.length() == 0) break;
        
        for (Function f : funcs) {
            if (f.is_function_for(token)) {
                f.execute(token);
                exec = true;
                break;
            }
        }

        FATAL_ERROR(!exec, "Undefined instruction: %s", peek_token().c_str());
    }
}


std::string Instance::peek_token() {
    int pos = exec_stream.tellg();
    std::string token("");
    exec_stream >> token;
    exec_stream.seekg(pos);
    return token;
}


std::string Instance::consume_token() {
    std::string token("");
    exec_stream >> token;
    return token;
}


int Instance::get_tape_index() {
    return tape_index;
}


void Instance::set_tape_index(int index) {
    tape_index = index;
}


int Instance::get_tape_value() {
    return tape[tape_index];
}


void Instance::set_tape_value(int value) {
    tape[tape_index] = value;
}


void Instance::add_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&)) {
    Instance::Function func = {is_function_for, execute};
    funcs.push_back(func);
}


void Instance::add_preprocess_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&)) {
    Instance::Function func = {is_function_for, execute};
    preproc_funcs.push_back(func);
}


void Instance::add_execution_point(const std::string &name) {
    execution_points[name] = exec_stream.tellg();
}


void Instance::remove_execution_point(const std::string &name) {
    execution_points.erase(name);
}


void Instance::jump_to_execution_point(const std::string &name) {
    try {
        int pos = execution_points.at(name);
        exec_stream.seekg(pos);

    } catch (std::out_of_range range) {
        FATAL_ERROR(true, "Tried to jump to unknown point: %s.", name.c_str());
    }
}