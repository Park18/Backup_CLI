#include "error_info.hpp"

backup::core::error_info::error_info(std::string error_context, bfs::path error_path)
{
	this->error_context = error_context + ", ���� ���: " + error_path.string();
}

backup::core::error_info::error_info(std::string error_context, int valid_index)
{
	this->error_context = error_context + ", ��ȿ �ε���: " + boost::lexical_cast<std::string>(valid_index);
}

char const* backup::core::error_info::what() const noexcept
{
	return this->error_context.empty() ? "�� �� ���� ����" : this->error_context.c_str();
}