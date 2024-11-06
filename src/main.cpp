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
#include <dlfcn.h>

#include "instance.hpp"
#include "utils.h"
#include "shared.hpp"


Instance instance; // He he
int get_tape_value();
void set_tape_value(int value);
int get_tape_index();
void set_tape_index(int index);
void add_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&));
void add_preprocess_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&));
void add_execution_point(const std::string &name);
void remove_execution_point(const std::string &name);
void jump_to_execution_point(const std::string &name);
std::string peek_token();
std::string consume_token();


int main(int argc, char **argv) {
    FATAL_ERROR(argc < 2, "Shared library not specified.");
    FATAL_ERROR(argc < 3, "Source file not specified.");

    // Execution instance
    InstanceFuncs funcs = {
        &get_tape_value,
        &set_tape_value,
        &get_tape_index,
        &set_tape_index,
        &add_function,
        &add_preprocess_function,
        &add_execution_point,
        &remove_execution_point,
        &jump_to_execution_point,
        &peek_token,
        &consume_token
    };

    // Load library
    void *lib = dlopen(argv[1], RTLD_NOW);
    FATAL_ERROR(!lib, "Could not load library %s:\n\t%s", argv[1], dlerror());

    void (*init)(InstanceFuncs*) = (void(*)(InstanceFuncs*))dlsym(lib, "init");
    FATAL_ERROR(!init, "Could not find init function in library:\n\t%s", dlerror());

    // Init it
    init(&funcs);

    // Execute program :)
    instance.execute_file(argv[2]);

    // Close library
    dlclose(lib);
    return 0;
}


// Hahahahahah
int get_tape_value() { return instance.get_tape_value(); }
void set_tape_value(int value) { instance.set_tape_value(value); }

int get_tape_index() { return instance.get_tape_index(); }
void set_tape_index(int index) { instance.set_tape_index(index); }

void add_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&)) {
    instance.add_function(is_function_for, execute);
}

void add_preprocess_function(bool (*is_function_for)(const std::string&), int (*execute)(const std::string&)) {
    instance.add_preprocess_function(is_function_for, execute);
}

void add_execution_point(const std::string &name) {
    instance.add_execution_point(name);
}
void remove_execution_point(const std::string &name) {
    instance.remove_execution_point(name);
}
void jump_to_execution_point(const std::string &name) {
    instance.jump_to_execution_point(name);
}

std::string peek_token() {
    return instance.peek_token();
}
std::string consume_token() {
    return instance.consume_token();
}