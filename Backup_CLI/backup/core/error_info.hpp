#pragma once
#ifndef ERROR_INFO_HPP
#define ERROR_INFO_HPP

#include <exception>
#include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

namespace backup
{
	namespace core
	{

		class error_info : public std::exception
		{
		private:
			int index;
			bfs::path path;

		public:

			_NODISCARD virtual char const* what() const noexcept override;
		};

	} // !namespace core
} // !namespace backup
#endif // !ERROR_INFO_HPP
