#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Core.hpp"

namespace bfs = boost::filesystem;
namespace backup
{

class Abstract_Command
{
protected:
    bfs::path running_path;                     // 프로그램 실행 위치 경로
    backup::core::Path_Manager* path_manager;   // 기본 생성자 만들기 싫어서.. 포인터로..

public:
    Abstract_Command(bfs::path running_path);
    
    virtual void excute() = 0;
};

class Add_Command :public Abstract_Command
{
private:
    bfs::path root;      // 동기화 시작 경로
    bfs::path destination; // 동기화 목적지 경로
    int index;

public:
    Add_Command(bfs::path running_path, bfs::path root, bfs::path destination, int index)
        : Abstract_Command(running_path), root(root), destination(destination), index(index) {};

    virtual void excute() override;
};

class Delete_Command :public Abstract_Command
{
private:
    int index;
    int delte_mode;

public:
    Delete_Command(bfs::path running_path, int index)
        : Abstract_Command(running_path), index(index){}

    virtual void excute() override;
};

class Print_Command :public Abstract_Command
{
public:
    Print_Command(bfs::path running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

class Sync_Command :public Abstract_Command
{
public:
    Sync_Command(bfs::path running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

class Help_Command :public Abstract_Command
{
public:
    Help_Command(bfs::path running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};

// TODO 필요 없는 클래스 삭제 예정
class Exit_Command :public Abstract_Command
{
public:
    Exit_Command(bfs::path running_path) : Abstract_Command(running_path) {}

    virtual void excute() override;
};
} // !namespace backup

#endif // !COMMAND_HPP

