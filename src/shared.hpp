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


#pragma once

#include <string>



struct InstanceFuncs {
    int (*get_tape_value)();
    void (*set_tape_value)(int value);

    int (*get_tape_index)();
    void (*set_tape_index)(int index);

    void (*add_function)(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&));
    void (*add_preprocess_function)(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&));
    
    void (*add_execution_point)(const std::string &name);
    void (*remove_execution_point)(const std::string &name);
    void (*jump_to_execution_point)(const std::string &name);

    std::string (*peek_token)();
    std::string (*consume_token)();
};