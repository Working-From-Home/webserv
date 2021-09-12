#include "ft/filesystem/filesystem.hpp"

#include "ft/filesystem/filesystem_error.hpp"
#include "ft/system_error.hpp"
#include "ft/error_code.hpp"

#include <unistd.h>

namespace ft { namespace filesystem {

void swap(path& lhs, path& rhs) throw() 
{
	path tmp(lhs);
	lhs = rhs;
	rhs = tmp;
}

bool operator==(const path& lhs, const path& rhs) throw() {return lhs._path == rhs._path;}
bool operator< (const path& lhs, const path& rhs) throw() {return lhs._path < rhs._path;}
bool operator!=(const path& lhs, const path& rhs) throw() { return !(lhs == rhs); }
bool operator<=(const path& lhs, const path& rhs) throw() { return !(rhs < lhs); }
bool operator> (const path& lhs, const path& rhs) throw() { return rhs < lhs; }
bool operator>=(const path& lhs, const path& rhs) throw() { return !(lhs < rhs); }
path operator/ (const path& lhs, const path& rhs) { return path(lhs) /= rhs;}
 
path current_path()
{
	error_code ec;
	path result = current_path(ec);
	if (ec.value())
		throw filesystem_error("current_path(): " + ec.message() , ec);
	return result;
}

path current_path(error_code& ec)
{
	std::string result;
	char cwd[PATH_MAX];
	if (::getcwd(cwd, sizeof(cwd)) != NULL)
	{
		result = cwd;
		ec.clear();
	}
	else
		ec = make_error_code();
	return path(result);
}

void current_path(const path& p)
{
	error_code ec;
	current_path(p, ec);
	if (ec.value())
		throw filesystem_error("current_path(const path&): " + ec.message(), p, ec);
}

void current_path(const path& p, error_code& ec) throw()
{
	if (::chdir(p.c_str()) ==  -1)
		ec = make_error_code();
	else
		ec.clear();
}


} /* namespace filesystem */
} /* namespace ft */