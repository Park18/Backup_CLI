#ifndef PATH_MANAGER_HPP
#define PATH_MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>

#define MANAGEMENT_FILE "dir_path/path.txt"

namespace bfs = boost::filesystem;

namespace backup
{
namespace core
{
typedef std::vector<std::string> Path_List;

/***
 * @brief 동기화하기 위한 경로를 관리하는 클래스
 */
class Path_Manager
{
private:
	bfs::path management_file;	// 경로 관리 파일의 경로
	Path_List path_list;		// 경로 관리 리스트

public:
	Path_Manager(bfs::path execute_path);

	// TODO 왜 만들었는지 정확히 기억이 안남, 확인할 것
	bfs::path get_management_file();

	Path_List get_path_list();

	// management file
	void create_management_file();
	bool management_file_empty();

	// path list(vector)
	void push_back(bfs::path root, bfs::path destination);
	void insert(bfs::path root, bfs::path destination, int index);
	void erase(int index);
	void clear();
	void print();

	// loading
	void file_to_list();
	void list_to_file();

	// management line
	bfs::path get_root(std::string path_management_data);
	bfs::path get_destination(std::string path_management_data);
};

} // !namespace core
} // !namespace backup

#endif	//	!PATH_MANAGER_HPP