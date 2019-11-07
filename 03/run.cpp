#include "parser.h"

#include <iostream>
#include <string>
#include <stdexcept>

int run(const std::string& to_parse) {
    try {
        Parser parser = Parser()
            .registerOnStart([]() { std::cout << "Start callback" << std::endl; })
            .registerOnToken([](std::string token) { std::cout << "String token = " << std::move(token) << std::endl; })
            .registerOnToken([](int token) { std::cout << "Int token = " << token << std::endl; })
            .registerOnFinish([]() { std::cout << "Finish callback" << std::endl; });
        parser.parse(to_parse);
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unhandled exception" << std::endl;
        throw;
    }
    return 0;
}

int main(int argc, const char* argv[]) {
    if (argc < 2) {
        std::cout << "Invalid arguments. Example:\n";
        std::cout << "run [string]" << std::endl;
        return -1;
    }
    return run(std::string(argv[1]));
}
