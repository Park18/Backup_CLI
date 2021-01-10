#include "Command_Line.hpp"

using namespace std;

backup::instruction::Command_Line::Command_Line(std::string command_line)
{
	set_command_line(command_line);
}

backup::instruction::Command_Line::Command_Line(int argc, char* argv[])
{
	set_command_line(argc, argv);
}

void backup::instruction::Command_Line::set_command_line(std::string command_line)
{
	// 토큰 분리 방법
	// command_line을 구획 구분자로 분류하여 token을 생성한다.
	// 1. std::getline()
	// 2. >> 연산자
	// 3. boost tokenizer -> boost 라이브러리 에러
	// https://psychoria.tistory.com/666

	std::string token;
	stringstream ss(command_line);

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
	auto root = find(this->command_line.begin(), this->command_line.end(), OPTION_ROOT) + 1;

	return bfs::path(*root);
}

bfs::path backup::instruction::Command_Line::get_destination()
{
	auto destination = find(this->command_line.begin(), this->command_line.end(), OPTION_DESTINATION) + 1;

	return bfs::path(*destination);
}

int backup::instruction::Command_Line::get_pos()
{
	// 옵션 P를 찾지 못했을 때 -1을 반환해야 하는데
	// find() + 1 로 계산할 경우 에러가 발생함
	// 옵션 A를 찾는 함수를 제작 안했기 때문에 이렇게 해결함
	auto pos = find(this->command_line.begin(), this->command_line.end(), OPTION_POS);

	if (pos == this->command_line.end())
		return -1;

	// string to int
	// 1. std::stringstream
	// 2. std::stoi
	// 3. boost::lexical_cast<"int or double">
	// https://psychoria.tistory.com/709
	return boost::lexical_cast<int>(*(pos + 1));
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
