#ifndef PROCESS_HPP
#define PROCESS_HPP

#include "Command.hpp"
#include "Instruction.hpp"
#include "Core.hpp"

/***
 * @brief 프로그램 실행 클래스
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
	 * 명령어 처리 메소드
	 */
	void input_commnad();

	bool check_command_line();

	/**
	 * @brief 명령어에 따라 Command* command의 속성을 바꾸는 메소드
	 */
	void command_switch();

	/**
	 * @brief 프로그램 실행 메소드
	 */
	void run();
};

} // !namespace backup


#endif // !PROCESS_HPP

