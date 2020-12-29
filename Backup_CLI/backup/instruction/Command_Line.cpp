#include "Command_Line.hpp"

using namespace std;

backup::instruction::Command_Line::Command_Line(std::string str_command_line)
{
	set_command_line(str_command_line);
}

backup::instruction::Command_Line::Command_Line(int argc, char* argv[])
{
	set_command_line(argc, argv);
}

void backup::instruction::Command_Line::set_command_line(string str_command_line)
{
	// 토큰 분리 방법
	// command_line을 구획 구분자로 분류하여 token을 생성한다.
	// 1. std::getline()
	// 2. >> 연산자
	// 3. boost tokenizer -> boost 라이브러리 에러
	// https://psychoria.tistory.com/666

	string token;
	stringstream ss(str_command_line);

	while (getline(ss, token, DELIMITER))
		this->command_line.push_back(token);
}

void backup::instruction::Command_Line::set_command_line(int argc, char* argv[])
{
	for (int index = 1; index < argc; index++)
		this->command_line.push_back(argv[index]);
}

std::vector<std::string> backup::instruction::Command_Line::get_command_line()
{
	return this->command_line;
}

std::string backup::instruction::Command_Line::get_str_command_line()
{
	string str_command_line;

	for (string part_of_context : this->command_line)
		str_command_line.append(part_of_context + " ");

	return str_command_line;
}

backup::instruction::WORK backup::instruction::Command_Line::get_work()
{
	if (this->command_line.at(0) == STR_WORK_GROUP[WORK::ADD])
		return WORK::ADD;
	else if (this->command_line.at(0) == STR_WORK_GROUP[WORK::DELETE])
		return WORK::DELETE;
	else if (this->command_line.at(0) == STR_WORK_GROUP[WORK::PRINT])
		return WORK::PRINT;
	else if (this->command_line.at(0) == STR_WORK_GROUP[WORK::SYNC])
		return WORK::SYNC;
	else if (this->command_line.at(0) == STR_WORK_GROUP[WORK::HELP])
		return WORK::HELP;
	else if (this->command_line.at(0) == STR_WORK_GROUP[WORK::EXIT])
		return WORK::EXIT;
	else
		return WORK::UNKNOWN;
}

bfs::path backup::instruction::Command_Line::get_root()
{
	auto option_root_index = find(this->command_line.begin(), this->command_line.end(), OPTION_ROOT);

	return bfs::path(*(option_root_index + 1));
}

bfs::path backup::instruction::Command_Line::get_destination()
{
	auto option_destination_index = find(this->command_line.begin(), this->command_line.end(), OPTION_DESTINATION);

	return bfs::path(*(option_destination_index + 1));
}

int backup::instruction::Command_Line::get_pos()
{
	auto option_pos_index = find(this->command_line.begin(), this->command_line.end(), OPTION_POS);

	if (option_pos_index == this->command_line.end())
		return -1;

	// string to int
	// 1. std::stringstream
	// 2. std::stoi
	// 3. boost::lexical_cast<"int or double">
	// https://psychoria.tistory.com/709
	return boost::lexical_cast<int>(*(option_pos_index + 1));
}

std::vector<std::string>::iterator backup::instruction::Command_Line::begin()
{	
	return this->command_line.begin();
}

std::vector<std::string>::iterator backup::instruction::Command_Line::end()
{
	return this->command_line.end();
}

int backup::instruction::Command_Line::size()
{
	return this->command_line.size();
}

std::string backup::instruction::Command_Line::at(int index)
{
	return this->command_line.at(index);
}
