#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "Command.hpp"
#include "Instruction.hpp"
#include "Core.hpp"

/***
 * @brief ���α׷� ���� Ŭ����
 */
namespace backup
{
class Process
{
private:
	backup::instruction::Command_Line* command_line;
	backup::instruction::Abstract_Checker* checker;
	backup::Abstract_Command* command;
	char* main_argv_zero;

public:
	Process(int argc, char* argv[]);

	/**
	 * ��ɾ� ó�� �޼ҵ�
	 */
	void input_commnad();

	bool check_command_line();

	/**
	 * @brief ��ɾ ���� Command* command�� �Ӽ��� �ٲٴ� �޼ҵ�
	 */
	void command_switch();

	/**
	 * @brief ���α׷� ���� �޼ҵ�
	 */
	void run();
};

} // !namespace backup


#endif // !PROCESS_HPP

