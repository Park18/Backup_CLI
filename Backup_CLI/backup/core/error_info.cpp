#include "error_info.hpp"

backup::core::error_info::error_info(std::string error_context, bfs::path error_path)
{
	this->error_context = error_context + ", 오류 경로: " + error_path.string();
}

backup::core::error_info::error_info(std::string error_context, int valid_index)
{
	this->error_context = error_context + ", 유효 인덱스: " + boost::lexical_cast<std::string>(valid_index);
}

char const* backup::core::error_info::what() const noexcept
{
	return this->error_context.empty() ? "알 수 없는 오류" : this->error_context.c_str();
}