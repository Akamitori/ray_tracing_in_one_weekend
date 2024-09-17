//
// Created by PETROS on 14/09/2024.
//

#include "RedirectOutput.h"
#include <iostream>

RedirectOutput::RedirectOutput(const std::string &filename) : file(filename) {
    // Save the original buffer
    originalBuffer = std::cout.rdbuf();
    // Redirect cout to the file stream
    std::cout.rdbuf(file.rdbuf());
}

RedirectOutput::~RedirectOutput() {
    std::cout.rdbuf(originalBuffer);
}