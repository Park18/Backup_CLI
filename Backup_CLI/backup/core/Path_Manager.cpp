#include "Path_Manager.hpp"

using namespace std;

backup::core::Path_Manager::Path_Manager(bfs::path execute_path)
{
	this->management_file = execute_path.append(MANAGEMENT_FILE).generic_path();

	file_to_list();
}

bfs::path backup::core::Path_Manager::get_management_file()
{
	return this->management_file;
}

backup::core::Path_List backup::core::Path_Manager::get_path_list()
{
	return this->path_list;
}

void backup::core::Path_Manager::create_management_file()
{
	if (!bfs::is_directory(this->management_file.parent_path()))
		bfs::create_directory(this->management_file.parent_path());

	bfs::ofstream management_file(this->management_file);
	management_file.close();
}

bool backup::core::Path_Manager::management_file_empty()
{
	return bfs::file_size(this->management_file) == 0 ? true : false;
}

void backup::core::Path_Manager::push_back(bfs::path root, bfs::path destination)
{
	this->path_list.push_back(root.generic_string() + "-" + destination.generic_string());

	list_to_file();
}

void backup::core::Path_Manager::insert(bfs::path root, bfs::path destination, int index)
{
	this->path_list.insert(this->path_list.begin() + index, 
		root.generic_string() + "-" + destination.generic_string());

	list_to_file();
}

void backup::core::Path_Manager::erase(int index)
{
	try
	{
		this->path_list.erase(this->path_list.begin() + index);
		list_to_file();
	}
	catch (const std::exception& e)
	{
		// TODO 예외 처리(index 범위)
		cout << e.what() << endl;
	}
}

void backup::core::Path_Manager::clear()
{
	this->path_list.clear();

	list_to_file();
}

void backup::core::Path_Manager::print()
{
	for (int index = 0; index < this->path_list.size(); index++)
		cout << "[" << index << "] " << path_list.at(index) << endl;
}

void backup::core::Path_Manager::file_to_list()
{
	bfs::ifstream read_file(this->management_file);

	// TODO 파일이 비었을 때 무한으로 반복되는 현상
	string path_management_data;
	while (getline(read_file, path_management_data))
	{
		if (!path_management_data.empty())
			this->path_list.push_back(path_management_data);
	}
}

void backup::core::Path_Manager::list_to_file()
{
	bfs::ofstream write_file(this->management_file);

	for (auto path_management_data : this->path_list)
		write_file << path_management_data << endl;

	write_file.close();
}

bfs::path backup::core::Path_Manager::get_root(std::string management_line)
{
	bfs::path root = management_line.substr(0, management_line.find("-"));
	return root.generic_path();
}

bfs::path backup::core::Path_Manager::get_destination(std::string management_line)
{
	bfs::path destination = management_line.substr(management_line.find("-") + 1);
	return destination.generic_path();
}
