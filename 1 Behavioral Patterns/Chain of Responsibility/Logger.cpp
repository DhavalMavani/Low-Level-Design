#include <iostream>
using namespace std;

enum class LogType{INFO, DEBUG, WARNING, ERROR, FATAL };

class Logger{
public:
    Logger* nextLogger;
    LogType type;
    Logger(Logger* nextLogger){ this->nextLogger=nextLogger; }

    virtual void log(LogType logType, string message){ 
        if(nextLogger) nextLogger->log(logType, message);
    }
};

class DebugLogger: public Logger{
public:
    DebugLogger(Logger* nextLogger): Logger(nextLogger){
        type=LogType::DEBUG;
    }

    void log(LogType logType, string message){
        if(this->type==logType) cout<<"[Debug]: "<<message<<"\n";
        else Logger::log(logType, message);
    }
};

class ErrorLogger: public Logger{
public:
    ErrorLogger(Logger* nextLogger): Logger(nextLogger){
        type=LogType::ERROR;
    }

    void log(LogType logType, string message){
        if(this->type==logType) cout<<"[Error]: "<<message<<"\n";
        else Logger::log(logType, message);
    }
};

class InfoLogger: public Logger{
public:
    InfoLogger(Logger* nextLogger): Logger(nextLogger){
        type=LogType::INFO;
    }

    void log(LogType logType, string message){
        if(this->type==logType) cout<<"[Info]: "<<message<<"\n";
        else Logger::log(logType, message);
    }
};

class WarningLogger: public Logger{
public:
    WarningLogger(Logger* nextLogger): Logger(nextLogger){
        type=LogType::WARNING;
    }

    void log(LogType logType, string message){
        if(this->type==logType) cout<<"[Warning]: "<<message<<"\n";
        else Logger::log(logType, message);
    }
};

class FatalLogger: public Logger{
public:
    FatalLogger(Logger* nextLogger): Logger(nextLogger){
        type=LogType::FATAL;
    }

    void log(LogType logType, string message){
        if(this->type==logType) cout<<"[Fatal]: "<<message<<"\n";
        else Logger::log(logType, message);
    }
};

int main(){
    Logger* logObject= new InfoLogger(new DebugLogger( new WarningLogger( new ErrorLogger( new FatalLogger(NULL) ) ) ));

    logObject->log(LogType::INFO, "This is Info log");
    logObject->log(LogType::DEBUG, "This is Debug log");
    logObject->log(LogType::WARNING, "This is Warning log");
    logObject->log(LogType::ERROR, "This is Error log");
    logObject->log(LogType::FATAL, "This is Fatal log");

    return 0;
}


