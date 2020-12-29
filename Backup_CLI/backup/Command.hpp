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
    bfs::path running_path; // ���α׷� ���� ��ġ ���
    //stack<string>; // ��� ����

public:
    // ���� ��θ� ���� argv[0]�� �Ű������� �޴´�.
    Abstract_Command(char* main_argv_zero);
    
    virtual void excute() = 0;

    // TODO ���� ������
    //virtual void cancle() = 0;
};

class Add_Command :public Abstract_Command
{
private:
    bfs::path source;      // ����ȭ ���� ���
    bfs::path destination; // ����ȭ ������ ���

public:
    Add_Command(char* main_argv_zero, bfs::path source, bfs::path destination);

    virtual void excute() override;
};

class Delete_Command :public Abstract_Command
{
public:
    Delete_Command(char* main_argv_zero) : Abstract_Command(main_argv_zero){}

    virtual void excute() override;
};

class Print_Command :public Abstract_Command
{
public:
    Print_Command(char* main_argv_zero) : Abstract_Command(main_argv_zero) {}

    virtual void excute() override;
};

class Sync_Command :public Abstract_Command
{
public:
    Sync_Command(char* main_argv_zero) : Abstract_Command(main_argv_zero) {}

    virtual void excute() override;
};

class Help_Command :public Abstract_Command
{
public:
    Help_Command(char* main_argv_zero) : Abstract_Command(main_argv_zero) {}

    virtual void excute() override;
};

class Exit_Command :public Abstract_Command
{
public:
    Exit_Command(char* main_argv_zero) : Abstract_Command(main_argv_zero) {}

    virtual void excute() override;
};
} // !namespace backup

#endif // !COMMAND_HPP

