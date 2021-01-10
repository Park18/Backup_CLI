#include "Process.hpp"

using namespace std;
using namespace backup::instruction;

backup::Process::Process(int argc, char* argv[])
{
	this->command_line = new Command_Line(argc, argv);
	this->running_path = bfs::path(argv[0]).parent_path().generic_path();
}

backup::Process::~Process()
{
	delete this->command_line;
	delete this->command;
	delete this->checker;
}

bool backup::Process::check_instruction()
{
	if (this->command_line->size() == 0)
		return false;

	switch (this->command_line->get_work())
	{
	case instruction::WORK::ADD:
		this->checker = new Add_Checker(*this->command_line);
		break;
	
	case instruction::WORK::DELETE:
		this->checker = new Delete_Checker(*this->command_line);
		break;
	
	case instruction::WORK::PRINT:
		this->checker = new Print_Checker(*this->command_line);
		break;
	
	case instruction::WORK::SYNC:
		this->checker = new Sync_Checker(*this->command_line);
		break;
	
	case instruction::WORK::HELP:
		this->checker = new Help_Checker(*this->command_line);
		break;
	
	case instruction::WORK::EXIT:
		this->checker = new Exit_Checker(*this->command_line);
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
		this->command = new Add_Command(this->running_path,
										this->command_line->get_root(),
										this->command_line->get_destination());
		break;

	case instruction::WORK::DELETE:
		this->command = new Delete_Command(this->running_path,
										   this->command_line->get_pos());
		break;

	case instruction::WORK::PRINT:
		this->command = new Print_Command(this->running_path);
		break;

	case instruction::WORK::SYNC:
		this->command = new Sync_Command(this->running_path);
		break;

	case instruction::WORK::HELP:
		this->command = new Help_Command(this->running_path);
		break;

	case instruction::WORK::EXIT:
		this->command = new Exit_Command(this->running_path);
		break;
	}
}

void backup::Process::run(int argc)
{
	if (!check_instruction())
	{
		cout << "[¾Ë¸²] >> " << this->checker->what() << endl;
		return;
	}

	command_switch();
	command->excute();	
}
