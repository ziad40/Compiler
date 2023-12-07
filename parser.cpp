#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

void parser(std::string path)
{
    std::ifstream f(path);
    std::string str;
    if (f)
    {
        std::ostringstream ss;
        ss << f.rdbuf(); // reading data
        str = ss.str();
    }
    std::cout << str;
}

int main(int argc, char *argv[])
{
    parser(argv[1]);
}