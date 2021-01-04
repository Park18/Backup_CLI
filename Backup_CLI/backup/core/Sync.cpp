#include "Sync.hpp"

using namespace std;

void backup::core::Sync::init(bfs::path root)
{
	// TODO try-catch 처리를 해야할까??
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
			bfs::path dest = destination;
			dest = dest.append(file.filename().string()).generic_path();
			bfs::copy_file(file.generic_path(), dest, bfs::copy_option::overwrite_if_exists);
		}
}

void backup::core::Sync::sync(bfs::path root, bfs::path destination)
{
	// 경로 "dest/root.filename()"이 없으면 root.filename() 디렉토리 생성
	// 예) root: C:/Root/A, dest: D:/Backup -> D:/Backup/A
	bfs::path dest = destination.append(root.filename().string()).generic_path();
	if (!bfs::exists(dest))
		bfs::create_directory(dest);

	// 복사해야 할 목록 초기화
	init(root.generic_path());

	// 폴더 복사 후 파일 복사, 파일 복사시 폴더가 존재하지 않으면 에러 발생
	copy_directory_group(destination.generic_path());
	copy_file_group(destination.generic_path());
}

void backup::core::Sync::execute(bfs::path root, bfs::path destination)
{
	sync(root.generic_path(), destination.generic_path());
}
