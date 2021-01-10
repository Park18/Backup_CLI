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
	bfs::path running_path;

private:
	bool check_instruction();

	void command_switch();


public:
	Process(int argc, char* argv[]);
	~Process();

	void run(int argc);
};

} // !namespace backup


#endif // !PROCESS_HPP

