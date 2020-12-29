#include "Checker.hpp"

using namespace std;

bool backup::instruction::Abstract_Checker::check_instruction()
{
    return has_work() && check_option();
}

bool backup::instruction::Abstract_Checker::has_work()
{
    //vector<string> command_line = this->command_line.get_command_line();
    return find(this->command_line.begin(), this->command_line.end(), STR_WORK_GROUP[this->work]) !=
        this->command_line.end();
    
    // 문자열 이용
    // return this->command_line.get_str_command_line().find(STR_WORK_GROUP[this->work]) != -1;
}

bool backup::instruction::Abstract_Checker::has_option(std::string option)
{
    //vector<string> command_line = this->command_line.get_command_line();
    return find(this->command_line.begin(), this->command_line.end(), option) !=
        this->command_line.end();

    // 문자열 이용
    // return (this->command_line.get_str_command_line().find(option) != -1);
}

bool backup::instruction::Abstract_Checker::check_path(bfs::path directory)
{
    return bfs::is_directory(directory);
}

backup::instruction::Add_Checker::Add_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::ADD;
}

bool backup::instruction::Add_Checker::check_option()
{
    return (has_option(OPTION_ROOT) && has_option(OPTION_DESTINATION)) ||
        (has_option(OPTION_ROOT) && has_option(OPTION_DESTINATION) && has_option(OPTION_POS));
}

backup::instruction::Delete_Checker::Delete_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::DELETE;
}

bool backup::instruction::Delete_Checker::check_option()
{
    return has_option(OPTION_ALL) || has_option(OPTION_POS);
}

backup::instruction::Print_Checker::Print_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::PRINT;
}

bool backup::instruction::Print_Checker::check_option()
{
    if (this->command_line.size() == 1 &&
        this->command_line.at(0) == STR_WORK_GROUP[this->work])
        return true;

    // 문자열 이용
    // if (this->command_line.get_str_command_line().size() == STR_WORK_GROUP[this->work].size())
    //     return true;

    return false;
}

backup::instruction::Sync_Checker::Sync_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::SYNC;
}

bool backup::instruction::Sync_Checker::check_option()
{
    if (this->command_line.size() == 1 &&
        this->command_line.at(0) == STR_WORK_GROUP[this->work])
        return true;

    // 문자열 이용
    // if (this->command_line.get_str_command_line().size() == STR_WORK_GROUP[this->work].size())
    //     return true;

    return false;
}

backup::instruction::Help_Checker::Help_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::HELP;
}

bool backup::instruction::Help_Checker::check_option()
{
    if (this->command_line.size() == 1 &&
        this->command_line.at(0) == STR_WORK_GROUP[this->work])
        return true;

    // 문자열 이용
    // if (this->command_line.get_str_command_line().size() == STR_WORK_GROUP[this->work].size())
    //     return true;

    return false;
}

backup::instruction::Exit_Checker::Exit_Checker(Command_Line command_line) : Abstract_Checker(command_line)
{
    this->work = WORK::EXIT;
}

bool backup::instruction::Exit_Checker::check_option()
{
    if (this->command_line.size() == 1 &&
        this->command_line.at(0) == STR_WORK_GROUP[this->work])
        return true;

    // 문자열 이용
    // if (this->command_line.get_str_command_line().size() == STR_WORK_GROUP[this->work].size())
    //     return true;

    return false;
}

