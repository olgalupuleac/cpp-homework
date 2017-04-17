#pragma once

#include "bitstream.h"

class HuffmanArchiver {
private:
    std::string in_;
    std::string out_;
public:
    HuffmanArchiver(std::string in, std::string out):in_(in), out_(out){}
    void zip();
    void unzip();
};
