#include "Command.hpp"

using namespace std;	
using namespace backup::core;

backup::Abstract_Command::Abstract_Command(char* running_path)
{
	this->running_path = running_path;
	this->running_path = this->running_path.parent_path();
	this->running_path = this->running_path.generic_path();
}

backup::Add_Command::Add_Command(char* running_path, bfs::path source, bfs::path destination) : Abstract_Command(running_path)
{
	this->root = source;
	this->destination = destination;
}

void backup::Add_Command::excute()
{
	Path_Manager path_manager(this->running_path);

	if (!bfs::exists(path_manager.get_management_file()))
	{
		cout << "[알림] >> 관리 파일이 없습니다. 재생성후 경로를 추가합니다.." << endl;
		path_manager.create_management_file();
	}

	if (!(bfs::exists(this->root) && bfs::exists(this->destination)))
	{
		cout << "[알림] >> 존재하지 않은 경로입니다." << endl;
		return;
	}

	// TODO 파일이 없을 때 list to flie 실행 안됨
	// 사실 그냥 실행이 잘 안되는거 같음
	path_manager.push_back(this->root, this->destination);
	path_manager.list_to_file();
}

void backup::Delete_Command::excute()
{
	Path_Manager path_manager(this->running_path);
	
	try
	{
		if (path_manager.management_file_empty())
		{
			cout << "[알림] >> 파일이 비어있습니다." << endl;
			return;
		}

		cout << "[알림] >> 삭제할 관리 목록의 인덱스를 입력해 주세요." << endl;
		cout << "[index] << ";

		int delete_index;
		cin >> delete_index;

		path_manager.erase(delete_index);
	}
	catch (const std::exception&)
	{
		cout << "[알림] >> 관리 파일이 없습니다. 재생성합니다." << endl;
		path_manager.create_management_file();
	}
}

void backup::Print_Command::excute()
{
	Path_Manager path_manager(this->running_path);

	try
	{
		path_manager.print();
	}
	catch (const std::exception&)
	{
		cout << "[알림] >> 관리 파일이 없습니다. 재생성합니다." << endl;
		path_manager.create_management_file();
	}
}

void backup::Sync_Command::excute()
{
	Path_Manager path_manager(this->running_path);

	if (path_manager.management_file_empty())
	{
		cout << "[알림] >> sync list is empty." << endl;
		return;
	}

	try
	{
		cout << "[알림] >> 다음 항목을 동기화 합니다." << endl << endl;
			
		path_manager.print();

		for (auto path_management_data : path_manager.get_path_list())
		{
			backup::core::Sync sync;
			sync.execute(path_manager.get_root(path_management_data), 
				path_manager.get_destination(path_management_data));
		}		
	
		cout << "[알림] >> 동기화가 끝났습니다." << endl << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}
}

void backup::Help_Command::excute()
{
}

void backup::Exit_Command::excute()
{
}
