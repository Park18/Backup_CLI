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
	Command_Line command_line; // ��ɾ�
	WORK work;

public:
	Abstract_Checker(Command_Line command_line) :command_line(command_line) {};

	bool check_instruction();

	// add, delete, print ���� �ٽ� ��ɾ�
	// TODO �޼ҵ� �̸� �ּ�����...
	bool has_work();

	bool has_option(std::string option);

	// �ǹٸ� �ɼ��̸� true, Ʋ�� �ɼ��̸� false
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


