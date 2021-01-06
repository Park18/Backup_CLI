#include "Checker.hpp"

using namespace std;

bool backup::instruction::Abstract_Checker::check_instruction()
{
    return check_work() && check_option();
}

bool backup::instruction::Abstract_Checker::check_work()
{
    return this->command_line.at(0) == STR_WORK_GROUP[this->work];
}

bool backup::instruction::Abstract_Checker::has_option(std::string option)
{
    return find(this->command_line.begin(), this->command_line.end(), option) !=
        this->command_line.end();
}

bool backup::instruction::Abstract_Checker::check_path(std::string path_option)
{
    auto option_path = find(this->command_line.begin(), this->command_line.end(), path_option) + 1;
    bfs::path directory = *option_path;
    return bfs::is_directory(directory.generic_path());
}

backup::instruction::Add_Checker::Add_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::ADD;
}

bool backup::instruction::Add_Checker::check_option()
{
    bool result = (has_option(OPTION_ROOT) && check_path(OPTION_ROOT)) &&
        (has_option(OPTION_DESTINATION) && check_path(OPTION_DESTINATION));

    // TODO 인덱스 처리할 것인가/
    if (has_option(OPTION_POS))
        result;

    return result;
        
    //return (has_option(OPTION_ROOT) && has_option(OPTION_DESTINATION)) ||
    //    (has_option(OPTION_ROOT) && has_option(OPTION_DESTINATION) && has_option(OPTION_POS));
}

backup::instruction::Delete_Checker::Delete_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::DELETE;
}

bool backup::instruction::Delete_Checker::check_option()
{
    // TODO 인덱스 처리할 것인가?
    return has_option(OPTION_ALL) || has_option(OPTION_POS);
}

backup::instruction::Print_Checker::Print_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::PRINT;
}

bool backup::instruction::Print_Checker::check_option()
{
    return this->command_line.size() == 1 ? true : false;
}

backup::instruction::Sync_Checker::Sync_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::SYNC;
}

bool backup::instruction::Sync_Checker::check_option()
{
    return this->command_line.size() == 1 ? true : false;

}

backup::instruction::Help_Checker::Help_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::HELP;
}

bool backup::instruction::Help_Checker::check_option()
{
    return this->command_line.size() == 1 ? true : false;

}

backup::instruction::Exit_Checker::Exit_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::EXIT;
}

bool backup::instruction::Exit_Checker::check_option()
{
    return this->command_line.size() == 1 ? true : false;

}