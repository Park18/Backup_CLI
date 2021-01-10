#pragma once
#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <iterator>

namespace bfs = boost::filesystem;

namespace backup
{
namespace instruction
{

static std::string STR_WORK_GROUP[] = {
	"add",
	"delete",
	"print",
	"sync",
	"help",
	"exit"
};

static enum WORK
{
	ADD = 0,
	DELETE,
	PRINT,
	SYNC,
	HELP,
	EXIT,
	UNKNOWN
};

// define command line option
#define OPTION_ALL "-A"
#define OPTION_ROOT "-R"
#define OPTION_DESTINATION "-D"
#define OPTION_POS "-P"

#define	DELIMITER ' '

class Command_Line
{
private:
	std::vector<std::string> command_line; // 명령문은 단어 단위로 나눈 벡터

public:
	Command_Line(std::string command_line);
	Command_Line(int argc, char* argv[]);

	void set_command_line(std::string command_line);
	void set_command_line(int argc, char* argv[]);

	std::vector<std::string> get_command_line();

	// comand line token
	WORK get_work();
	bfs::path get_root();
	bfs::path get_destination();
	int get_pos();

	// command line(vector)
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();
	int size();
	std::string at(int index);
};

} // !namespace instruction
} // !namespace backupo

#endif // !COMMAND_LINE_HPP
