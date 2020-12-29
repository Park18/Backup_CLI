#include "Command.hpp"

using namespace std;	
using namespace backup::core;

backup::Abstract_Command::Abstract_Command(char* main_argv_zero)
{
	this->running_path = main_argv_zero;
	this->running_path = this->running_path.parent_path();
	this->running_path = this->running_path.generic_path();
}

backup::Add_Command::Add_Command(char* main_argv_zero, bfs::path source, bfs::path destination) : Abstract_Command(main_argv_zero)
{
	this->source = source;
	this->destination = destination;
}

void backup::Add_Command::excute()
{
	Path_Manager path_manager(this->running_path);

	if (!bfs::exists(path_manager.get_path_management_file()))
	{
		cout << "[�˸�] >> ���� ������ �����ϴ�. ������� ��θ� �߰��մϴ�.." << endl;
		path_manager.create_path_management_file();
	}

	if (!(bfs::exists(this->source) && bfs::exists(this->destination)))
	{
		cout << "[�˸�] >> �������� ���� ����Դϴ�." << endl;
		return;
	}

	// TODO ������ ���� �� list to flie ���� �ȵ�
	// ��� �׳� ������ �� �ȵǴ°� ����
	path_manager.push_back(this->source, this->destination);
	path_manager.list_to_file();
}

void backup::Delete_Command::excute()
{
	Path_Manager path_manager(this->running_path);
	
	try
	{
		if (path_manager.path_management_file_empty())
		{
			cout << "[�˸�] >> ������ ����ֽ��ϴ�." << endl;
			return;
		}

		cout << "[�˸�] >> ������ ���� ����� �ε����� �Է��� �ּ���." << endl;
		cout << "[index] << ";

		int delete_index;
		cin >> delete_index;

		path_manager.erase(delete_index);
	}
	catch (const std::exception&)
	{
		cout << "[�˸�] >> ���� ������ �����ϴ�. ������մϴ�." << endl;
		path_manager.create_path_management_file();
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
		cout << "[�˸�] >> ���� ������ �����ϴ�. ������մϴ�." << endl;
		path_manager.create_path_management_file();
	}
}

void backup::Sync_Command::excute()
{
	Path_Manager path_manager(this->running_path);

	if (path_manager.path_management_file_empty())
	{
		cout << "[�˸�] >> ������ ����ֽ��ϴ�." << endl;
		return;
	}

	try
	{
		cout << "[�˸�] >> ���� �׸��� ����ȭ �մϴ�." << endl << endl;
	
		{
			path_manager.print();

			for (auto path_management_data : path_manager.get_path_list())
				backup::core::sync::sync(path_manager.get_root(path_management_data), path_manager.get_destination(path_management_data));
		}
	
		cout << "[�˸�] >> ����ȭ�� �������ϴ�." << endl << endl;
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
