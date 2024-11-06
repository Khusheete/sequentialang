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


#include "../src/shared.hpp"
#include "functions.hpp"

#include <iostream>


InstanceFuncs *instance;

extern "C" void init(InstanceFuncs *i) {
    instance = i; // Save instance

    // Add preprocess functions
    instance->add_preprocess_function(&is_label_def, &label_def);

    // Add functionnalities
    instance->add_function(&is_label_def, &noop);
    instance->add_function(&is_unvalued_operand, &unvalued_operand);
    instance->add_function(&is_valued_operand, &valued_operand);
    instance->add_function(&is_print, &print);
    instance->add_function(&is_if_statement, &if_statement);
    instance->add_function(&is_jump, &jump);
    instance->add_function(&is_comment, &comment);
}