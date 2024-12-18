#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <termcolor/termcolor.hpp>
#include <iostream>
#include <string>

class Logger {
public:
    static void info(const std::string& message) {
        std::cout << termcolor::cyan << "[INFO] " << termcolor::reset << message << std::endl;
    }

    static void success(const std::string& message) {
        std::cout << termcolor::green << "[SUCCESS] " << termcolor::reset << message << std::endl;
    }

    static void error(const std::string& message) {
        std::cerr << termcolor::red << "[ERROR] " << termcolor::reset << message << std::endl;
    }

    static void input(const std::string& prompt) {
        std::cout << termcolor::yellow << "[INPUT] " << termcolor::reset << prompt;
    }
};

#endif // LOGGER_HPP
