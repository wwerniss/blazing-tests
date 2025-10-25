#pragma once

#include <string>
#include <iostream>

// Forward declarations
class Character;
class Item;

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    void raw(const std::string& message) {
        std::cout << message;
    }

    void log(const std::string& prefix, const std::string& level, const std::string& message) {
        std::cout << prefix << "[" << level << "] " << message << "\033[0m" << std::endl;
    }

    void info(const std::string& message) {
        log("\033[32m", "INFO", message);
    }
    
    void error(const std::string& message) {
        log("\033[31m", "ERROR", message);
    }
    
    void warning(const std::string& message) {
        log("\033[33m", "WARNING", message);
    }
    
    void combatLog(const std::string& message) {
        log("\033[31m", "БІЙ", message);
    }
    
    void gameLog(const std::string& message) {
        log("\033[35m", "ГРА", message);
    }
    
private:
    Logger() {}
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
};
