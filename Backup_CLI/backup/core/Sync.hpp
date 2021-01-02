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
class Sync
{
private:
	std::vector<bfs::path> directory_group;
	std::vector<bfs::path> file_group;

private:
	void init(bfs::path root);
	void copy_directory_group(bfs::path destination);
	void copy_file_group(bfs::path destination);
	void sync(bfs::path root, bfs::path destination);

public:
	void execute(bfs::path root, bfs::path destination);
};
} // !namespace core
} // !namespace backup	

#endif // !SYNC_HPP