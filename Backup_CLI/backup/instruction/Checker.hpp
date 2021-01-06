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
	Command_Line command_line;
	WORK work;

public:
	Abstract_Checker(Command_Line command_line) :command_line(command_line) {};

	bool check_instruction();
	
	// part of check_instruction()
	// right: true, wrong: false
	bool check_work();
	virtual bool check_option() = 0;
	bool has_option(std::string option);
	bool check_path(std::string path_option);
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


