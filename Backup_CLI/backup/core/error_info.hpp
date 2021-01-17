#pragma once
#ifndef ERROR_INFO_HPP
#define ERROR_INFO_HPP

#include <exception>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace bfs = boost::filesystem;

namespace backup
{
namespace core
{

class error_info : public std::exception
{
private:
	std::string error_context;

public:
	error_info() {}
	error_info(std::string error_context) : error_context(error_context) {}
	error_info(std::string error_context, bfs::path error_path);
	error_info(std::string error_context, int valid_index);

	_NODISCARD virtual char const* what() const noexcept override;
};

} // !namespace core
} // !namespace backup
#endif // !ERROR_INFO_HPP
