#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Core.hpp"
// #include "Error_Code.hpp"

namespace bfs = boost::filesystem;
namespace backup
{

class Abstract_Command
{
protected:
    bfs::path running_path; // 프로그램 실행 위치 경로
    //stack<string>; // 취소 스택

public:
    // 실행 경로를 가진 argv[0]을 매개변수로 받는다.
    Abstract_Command(char* running_path);
    
    virtual void excute() = 0;
};

class Add_Command :public Abstract_Command
{
private:
    bfs::path root;      // 동기화 시작 경로
    bfs::path destination; // 동기화 목적지 경로

public:
    Add_Command(char* running_path, bfs::path source, bfs::path destination);

    virtual void excute() override;
};

class Delete_Command :public Abstract_Command
{
public:
    Delete_Command(char* running_path) : Abstract_Command(running_path){}

    virtual void excute() override;
};

class Print_Command :public Abstract_Command
{
public:
    Print_Command(char* running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

class Sync_Command :public Abstract_Command
{
public:
    Sync_Command(char* running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

class Help_Command :public Abstract_Command
{
public:
    Help_Command(char* running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

class Exit_Command :public Abstract_Command
{
public:
    Exit_Command(char* running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};
} // !namespace backup

#endif // !COMMAND_HPP

