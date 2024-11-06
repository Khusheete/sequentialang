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

#include "../src/shared.hpp"

#include <string>


bool is_print(const std::string &command);
int print(const std::string &command);


bool is_valued_operand(const std::string &command);
int valued_operand(const std::string &command);


bool is_unvalued_operand(const std::string &command);
int unvalued_operand(const std::string &command);


bool is_label_def(const std::string &command);
int label_def(const std::string &command);
int noop(const std::string &command);


bool is_jump(const std::string &command);
int jump(const std::string &command);


bool is_if_statement(const std::string &command);
int if_statement(const std::string &command);

bool is_comment(const std::string &command);
int comment(const std::string &command);