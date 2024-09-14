//
// Created by PETROS on 14/09/2024.
//

#ifndef REDIRECTOUTPUT_H
#define REDIRECTOUTPUT_H

#include <fstream>
#include <string>


class RedirectOutput {
public:
    RedirectOutput(const std::string& filename);

    // Restore the original buffer when the object goes out of scope
    ~RedirectOutput();

private:
    std::ofstream file;
    std::streambuf* originalBuffer;
};





#endif //REDIRECTOUTPUT_H
