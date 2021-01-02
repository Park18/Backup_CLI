#include "Sync.hpp"

using namespace std;

// TODO �Լ��� �� �۰� �����
// 1. ��� "dest/root.filename()"�� ������ root.filename() ���丮 ����
// 2. source�� ���� ����, ������ vector�� ����
// 3. ���� ������ ������ sync(��������, dest/source.filename()) ȣ�� (���� ���� �ݺ�)
// 4. ���� ������ ���̻� ������ ���ϵ� ����
void backup::core::sync(const bfs::path& root, const bfs::path& destination)
{
	// 1. ��� "dest/root.filename()"�� ������ root.filename() ���丮 ����
	// ��) root: C:/A, dest: D:/Backup -> D:/Backup/A
	bfs::path dest = destination.generic_path();
	if (!bfs::exists(dest /= root.filename()))
		bfs::create_directory(dest.generic_path());

	// 2. source�� ���� ����, ������ vector�� ����
	vector<bfs::path> directoriy_group;
	vector<bfs::path> file_group;
	
	for(auto copy_path : bfs::directory_iterator(root))
	{
		if (bfs::is_directory(copy_path.path().generic_path()))
			directoriy_group.push_back(copy_path.path().generic_path());

		else
			file_group.push_back(copy_path.path().generic_path());
	}

	// 3. ���� ������ �ִٸ� ����Լ��� sync ȣ��
	if (!directoriy_group.empty())
	{
		for (int index = 0; index < directoriy_group.size(); index++)
		{
			sync(directoriy_group[index], dest);
		}
	}
	
	// 4. ���� ����
	if (!file_group.empty())
	{
		for (int index = 0; index < file_group.size(); index++)
		{
			dest = destination;
			dest /= root.filename() /= file_group[index].filename();
			bfs::copy_file(file_group[index], dest, bfs::copy_option::overwrite_if_exists);
		}
	}
}

void backup::core::Sync::init(bfs::path root)
{
	try
	{
		for (auto copy_path : bfs::directory_iterator(root))
		{
			if (bfs::is_directory(copy_path.path().generic_path()))
				this->directory_group.push_back(copy_path.path().generic_path());

			else
				this->file_group.push_back(copy_path.path().generic_path());
		}

	}
	catch (bfs::filesystem_error& e)
	{
		cout << e.what() << endl;
	}
}

void backup::core::Sync::copy_directory_group(bfs::path destination)
{
	if (!this->directory_group.empty())
		for (auto directory : directory_group)
		{
			Sync a; 
			a.sync(directory.generic_path(), destination);
		}
		
}

void backup::core::Sync::copy_file_group(bfs::path destination)
{
	if (!this->file_group.empty())
		for (auto file : this->file_group)
		{
			// TODO �ݺ����� ����Ǹ鼭 append()�� ���� destination�� ������
			// ��) ~~~/a.txt -> ~~~/a.txt/b.txt
			bfs::path dest = destination;
			dest = dest.append(file.filename().string()).generic_path();
			bfs::copy_file(file.generic_path(), dest, bfs::copy_option::overwrite_if_exists);
		}
}

void backup::core::Sync::sync(bfs::path root, bfs::path destination)
{
	// ��� "dest/root.filename()"�� ������ root.filename() ���丮 ����
	// ��) root: C:/Root/A, dest: D:/Backup -> D:/Backup/A
	bfs::path dest = destination.append(root.filename().string()).generic_path();
	if (!bfs::exists(dest))
		bfs::create_directory(dest);

	// �����ؾ� �� ��� �ʱ�ȭ
	init(root.generic_path());

	// ���� ���� �� ���� ����, ���� ����� ������ �������� ������ ���� �߻�
	copy_directory_group(destination.generic_path());
	copy_file_group(destination.generic_path());
}

void backup::core::Sync::execute(bfs::path root, bfs::path destination)
{
	sync(root.generic_path(), destination.generic_path());
}
