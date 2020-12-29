#include "Process.hpp"

using namespace std;
using namespace backup::instruction;

backup::Process::Process(int argc, char* argv[])
{
	this->command_line = new Command_Line(argc, argv);
	main_argv_zero = argv[0];
}

void backup::Process::input_commnad()
{
	// TODO 버퍼 초기화 넣으면 명령어 먹통되는 버그
	//cin.ignore();

	string command_line;
	getline(cin, command_line);

	this->command_line->set_command_line(command_line);
}

bool backup::Process::check_command_line()
{
	switch (this->command_line->get_work())
	{
	case instruction::WORK::ADD:
		this->checker = new Add_Checker(this->command_line->get_str_command_line());
		break;
	
	case instruction::WORK::DELETE:
		this->checker = new Delete_Checker(this->command_line->get_str_command_line());
		break;
	
	case instruction::WORK::PRINT:
		this->checker = new Print_Checker(this->command_line->get_str_command_line());
		break;
	
	case instruction::WORK::SYNC:
		this->checker = new Sync_Checker(this->command_line->get_str_command_line());
		break;
	
	case instruction::WORK::HELP:
		this->checker = new Help_Checker(this->command_line->get_str_command_line());
		break;
	
	case instruction::WORK::EXIT:
		this->checker = new Exit_Checker(this->command_line->get_str_command_line());
		break;
	
	default:
		return false;
	}

	return this->checker->check_instruction();
}

void backup::Process::command_switch()
{
	switch (this->command_line->get_work())
	{
	case instruction::WORK::ADD:
		this->command = new Add_Command(this->main_argv_zero,
										this->command_line->get_root(),
										this->command_line->get_destination());
		break;

	case instruction::WORK::DELETE:
		this->command = new Add_Command(this->main_argv_zero,
			this->command_line->get_root(),
			this->command_line->get_destination());
		break;

	case instruction::WORK::PRINT:
		this->command = new Print_Command(this->main_argv_zero);
		break;

	case instruction::WORK::SYNC:
		this->command = new Sync_Command(this->main_argv_zero);
		break;

	case instruction::WORK::HELP:
		this->command = new Help_Command(this->main_argv_zero);
		break;

	case instruction::WORK::EXIT:
		this->command = new Exit_Command(this->main_argv_zero);
		break;
	}
}

void backup::Process::run()
{
	while(true)
	{
		input_commnad();

		if (!check_command_line())
		{
			cout << "[알림] >> 잘못된 명령어 입니다." << endl;
			continue;
		}
		
		command_switch();
		command->excute();
	}
}
