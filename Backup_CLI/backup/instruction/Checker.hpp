#ifndef CHECKER_HPP
#define CHECKER_HPP

#include <string>
#include "Command_Line.hpp"

namespace backup
{
namespace instruction
{

class Abstract_Checker
{
protected:
	Command_Line command_line; // 명령어
	WORK work;

public:
	Abstract_Checker(Command_Line command_line) :command_line(command_line) {};

	bool check_instruction();

	// add, delete, print 등의 핵심 명령어
	// TODO 메소드 이름 최선인지...
	bool has_work();

	bool has_option(std::string option);

	// 옳바른 옵션이면 true, 틀린 옵션이면 false
	virtual bool check_option() = 0;

	bool check_path(bfs::path directory);
};

class Add_Checker : public Abstract_Checker
{
public:
	Add_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

class Delete_Checker : public Abstract_Checker
{
public:
	Delete_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

class Print_Checker : public Abstract_Checker
{
public:		
	Print_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

class Sync_Checker : public Abstract_Checker
{
public:
	Sync_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

class Help_Checker : public Abstract_Checker
{
public:
	Help_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

class Exit_Checker : public Abstract_Checker
{
public:
	Exit_Checker(Command_Line command_line);

	virtual bool check_option() override;
};

} // !namepspace instruction
} // !namespace backup

#endif // !CHECKER_HPP


