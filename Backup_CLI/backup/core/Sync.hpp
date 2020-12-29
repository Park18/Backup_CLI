#pragma once
#ifndef SYNC_HPP
#define SYNC_HPP

#include <iostream>
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
namespace bfs = boost::filesystem;

namespace backup
{
namespace core
{

//TODO 메서드 분활
/**
 * @brief 동기화 메소드
 * @details 재귀함수, source와 dest의 각각 파일의 수정한 날짜 비교, 다르면 source의 것으로 백업한다.
 * @param boost::filesystem::path source 원본 경로
 * @param boost::filesystem::path deest 복사본 경로
 */
void sync(const bfs::path &root, const bfs::path &dest/*, boost::system::error_code*/);

class Sync
{
private:
	std::vector<bfs::path> directoriy_group;
	std::vector<bfs::path> file_group;

private:
	void init(bfs::path root);
	void copy_directory_group(bfs::path destination);
	void copy_file_group(bfs::path& destination);
	void sync(bfs::path& destination);

public:
	void execute(bfs::path& root, bfs::path& destination);
};
} // !namespace core
} // !namespace backup	

#endif // !SYNC_HPP