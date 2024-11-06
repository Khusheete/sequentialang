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


#include "functions.hpp"
#include "../src/utils.h"

#include <cstddef>
#include <iostream>
#include <map>
#include <string>


extern InstanceFuncs *instance;
static int reg = 0; // the register


std::string _replace_all(const std::string& s, std::string const& toReplace, std::string const& replaceWith) {
    std::string buf;
    std::size_t pos = 0;
    std::size_t prevPos;

    // Reserves rough estimate of final size of string.
    buf.reserve(s.size());

    while (true) {
        prevPos = pos;
        pos = s.find(toReplace, pos);
        if (pos == std::string::npos)
            break;
        buf.append(s, prevPos, pos - prevPos);
        buf += replaceWith;
        pos += toReplace.size();
    }

    buf.append(s, prevPos, s.size() - prevPos);
    return buf;
}


std::string _replace_escape_chars(const std::string &str) {
    return _replace_all(str, "\\n", "\n");
}


int _get_value(const std::string &str) {
    if (str == "val") {
        int value = instance->get_tape_value();
        return value;
    } else if (str == "reg") {
        return reg;
    } else if (str == "idx") {
        return instance->get_tape_index();
    } else {
        unsigned long len_read;
        int value = stoi(str, &len_read);
        FATAL_ERROR(len_read != str.size(), "Unknown int litteral: %s", str.c_str());
        return value;
    }
}


bool is_print(const std::string &command) {
    return command == "print"
        || command == "println";
}


int print(const std::string &command) {    
    std::string token = _replace_escape_chars(instance->consume_token());

    if (token.length() == 0) return 0; // ignore print on file end

    if (token[0] == '"') {
        int index = 1;
        while (token[index] != '"') {
            std::cout << token[index];
            index++;

            if (index == token.length()) { // reatched end of token
                token = " " + _replace_escape_chars(instance->consume_token());
                index = 0;
                if (token.length() == 0) {
                    std::cout << std::endl;
                    WARNING(true, break;, "No ending '\"' to string");
                }
            }
        }
    } else if (token == "val") {
        std::cout << instance->get_tape_value();
    } else if (token == "char_val") {
        std::cout << (char)instance->get_tape_value();
    } else if (token == "idx") {
        std::cout << instance->get_tape_index();
    } else if (token == "char_idx") {
        std::cout << (char)instance->get_tape_index();
    } else if (token == "reg") {
        std::cout << reg;
    } else if (token == "char_reg") {
        std::cout << (char)reg;
    } else {
        std::cout << token;
    }

    if (command.length() == 7) // println
        std::cout << std::endl;
    else
        std::cout.flush();
    
    return 0;
}


bool is_valued_operand(const std::string &command) {
    return command == "+"   // add
        || command == "-"   // sub
        || command == "*"   // mult
        || command == "/"   // divide
        || command == "%"   // modulus
        || command == ">>"  // shift right
        || command == "<<"  // shift left
        || command == ">"   // move tape pointer to the right
        || command == "<"   // move tape pointer to the left
        || command == "^"   // xor
        || command == "|"   // or
        || command == "&"   // and
        || command == "="   // set
    ;
}


int valued_operand(const std::string &command) {
    int value = _get_value(instance->consume_token());

    if (command == "+") {
        instance->set_tape_value(instance->get_tape_value() + value);
    } else if (command == "-") {
        instance->set_tape_value(instance->get_tape_value() - value);
    } else if (command == "*") {
        instance->set_tape_value(instance->get_tape_value() * value);
    } else if (command == "/") {
        instance->set_tape_value(instance->get_tape_value() / value);
    } else if (command == "%") {
        instance->set_tape_value(instance->get_tape_value() % value);
    } else if (command == ">>") {
        instance->set_tape_value(instance->get_tape_value() >> value);
    } else if (command == "<<") {
        instance->set_tape_value(instance->get_tape_value() + value);
    } else if (command == "=") {
        instance->set_tape_value(value);
    } else if (command == "^") {
        instance->set_tape_index(instance->get_tape_value() ^ value);
    } else if (command == "|") {
        instance->set_tape_value(instance->get_tape_value() | value);
    } else if (command == "&") {
        instance->set_tape_value(instance->get_tape_value() & value);
    } else if (command == ">") {
        instance->set_tape_index(instance->get_tape_index() + value);
    } else if (command == "<") {
        instance->set_tape_index(instance->get_tape_index() - value);
    }

    return 0;
}


bool is_unvalued_operand(const std::string &command) {
    return command == "++"
        || command == "--"
        || command == "1>"
        || command == "1<"
        || command == "get_val"   // get the value of the current cell and store it into the register
        || command == "get_idx"   // get the current tape index and store it into the register
    ;
}


int unvalued_operand(const std::string &command) {
    if (command == "++") {
        instance->set_tape_value(instance->get_tape_value() + 1);
    } else if (command == "--") {
        instance->set_tape_value(instance->get_tape_value() - 1);
    } else if (command == "1>") {
        instance->set_tape_index(instance->get_tape_index() + 1);
    } else if (command == "1<") {
        instance->set_tape_index(instance->get_tape_index() - 1);
    } else if (command == "get_val") {
        reg = instance->get_tape_value();
    } else if (command == "get_idx") {
        reg = instance->get_tape_index();
    }

    return 0;
}


bool is_label_def(const std::string &command) {
    return *(--command.end()) == ':';
}


int label_def(const std::string &command) {
    std::string label_name = command.substr(0, command.length() - 1);
    instance->add_execution_point(label_name);
    return 0;
}


int noop(const std::string &command) {
    return 0;
}


bool is_jump(const std::string &command) {
    return command == "jump"
        || command == "jump_zer"    // jump if register is 0
        || command == "jump_nzr"    // jump if register is not 0
        || command == "jump_pos"    // jump if register is positive or null
        || command == "jump_neg"    // jump if register is negative or null
    ;
}


int jump(const std::string &command) {
    std::string label = instance->consume_token();

    if ((reg != 0 && command == "jump_zer")
        || (reg == 0 && command == "jump_nzr")
        || (reg < 0 && command == "jump_pos")
        || (reg > 0 && command == "jump_neg")
    ) return 0;

    instance->jump_to_execution_point(label);
    return 0;
}


bool is_if_statement(const std::string &command) {
    return command == "if"
        || command == "endif";
}


int if_statement(const std::string &command) {
    if (command == "endif") return 0; // Skip endif keyword
    
    bool cond_verified = false;

    
    std::string first = instance->consume_token();

    if (first == "false") {
        cond_verified = false;
    } else {
        int a = _get_value(first);

        std::string op  = instance->consume_token();
        int b = _get_value(instance->consume_token());


        if (op == "==") {
            cond_verified = (a == b);
        } else if (op == "!=") {
            cond_verified = (a != b);
        } else if (op == "<") {
            cond_verified = (a < b);
        } else if (op == ">") {
            cond_verified = (a > b);
        } else if (op == "<=") {
            cond_verified = (a <= b);
        } else if (op == ">=") {
            cond_verified = (a >= b);
        } else {
            FATAL_ERROR(true, "Unknown comparaison operator: %s", op.c_str());
        }
    }

    // Seek endif
    if (!cond_verified) {
        std::string token;
        int if_count = 1;

        while (if_count > 0) {
            token = instance->consume_token();

            if (token.length() == 0) FATAL_ERROR(true, "No endif found after if statement");

            if (token == "if") if_count++;
            else if (token == "endif") if_count--;

            if (is_label_def(token)) label_def(token); // Still define labels
        }
    }

    return 0;
}


bool is_comment(const std::string &command) {
    return command == "/*";
}


int comment(const std::string &command) {
    while (instance->consume_token() != "*/");
    return 0;
}