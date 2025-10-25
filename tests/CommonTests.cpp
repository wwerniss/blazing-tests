#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <string>
#include "../src/common/Logger.h"

// Helper class to capture cout/cerr output
class StreamCapture {
    std::streambuf* oldCout;
    std::streambuf* oldCerr;
    std::ostringstream captureStream;
    std::ostringstream errorStream;

public:
    void start() {
        oldCout = std::cout.rdbuf(captureStream.rdbuf());
        oldCerr = std::cerr.rdbuf(errorStream.rdbuf());
    }

    void stop() {
        std::cout.rdbuf(oldCout);
        std::cerr.rdbuf(oldCerr);
    }

    std::string getOutput() {
        return captureStream.str();
    }

    std::string getError() {
        return errorStream.str();
    }

    void reset() {
        captureStream.str("");
        captureStream.clear();
        errorStream.str("");
        errorStream.clear();
    }
};

TEST(LoggerTests, LogMessage) {
    StreamCapture capture;
    capture.start();
    
    Logger::getInstance().info("Test log message");
    
    capture.stop();
    
    std::string output = capture.getOutput();
    EXPECT_NE(output.find("[INFO] Test log message"), std::string::npos);
}

TEST(LoggerTests, WarningMessage) {
    StreamCapture capture;
    capture.start();
    
    Logger::getInstance().warning("Test warning message");
    
    capture.stop();
    
    std::string output = capture.getOutput();
    EXPECT_NE(output.find("[WARNING] Test warning message"), std::string::npos);
}

TEST(LoggerTests, ErrorMessage) {
    StreamCapture capture;
    capture.start();
    
    Logger::getInstance().error("Test error message");
    
    capture.stop();
    
    std::string errorOutput = capture.getOutput();
    EXPECT_NE(errorOutput.find("[ERROR] Test error message"), std::string::npos);
}

TEST(LoggerTests, CombatLogMessage) {
    StreamCapture capture;
    capture.start();
    
    Logger::getInstance().combatLog("Test combat log message");
    
    capture.stop();
    
    std::string output = capture.getOutput();
    EXPECT_NE(output.find("[БІЙ] Test combat log message"), std::string::npos);
}

TEST(LoggerTests, GameLogMessage) {
    StreamCapture capture;
    capture.start();
    
    Logger::getInstance().gameLog("Test game log message");
    
    capture.stop();
    
    std::string output = capture.getOutput();
    EXPECT_NE(output.find("[ГРА] Test game log message"), std::string::npos);
}

