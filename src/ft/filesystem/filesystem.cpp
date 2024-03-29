#include "ft/filesystem/filesystem.hpp"

#include "ft/filesystem/filesystem_error.hpp"
#include "ft/filesystem/file_status.hpp"
#include "ft/filesystem/file_type.hpp"
#include "ft/filesystem/directory_iterator.hpp"
#include "ft/system_error.hpp"
#include "ft/error_code.hpp"

#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
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
	if (ec)
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
	if (ec)
		throw filesystem_error("current_path(const path&): " + ec.message(), p, ec);
}

void current_path(const path& p, error_code& ec) throw()
{
	if (::chdir(p.c_str()) ==  -1)
		ec = make_error_code();
	else
		ec.clear();
}

path absolute(const path& p)
{
	error_code ec;
	path result = absolute(p, ec);
	if (ec)
		throw filesystem_error("absolute(const path&): " + ec.message(), p, ec);
	return result;
}

path absolute(const path& p, error_code& ec)
{
	path result = current_path(ec) / p;
	if (ec)
		result = path();
	return result;
}

bool status_known(file_status s) throw() 
{
	return s.type() != file_type::none;
}

static file_status stModeToFileStatus(mode_t mode)
{
	file_type type = file_type::unknown;
	if (S_ISREG(mode))
		type = file_type::regular;
	else if (S_ISDIR(mode))
		type = file_type::directory;
	else if (S_ISCHR(mode))
		type = file_type::character;
	else if (S_ISBLK(mode))
		type = file_type::block;
	else if (S_ISFIFO(mode))
		type = file_type::fifo;
	else if (S_ISLNK(mode))
		type = file_type::symlink;
	else if (S_ISSOCK(mode))
		type = file_type::socket;
	return file_status(type, mode & 0xfff);
}

file_status status(const path& p){
	error_code ec;
	file_status result = status(p, ec);
	if (result.type() == file_type::none)
		throw filesystem_error("status(const path& p=\""+ p.string() +"\"): " + ec.message(), p, ec);
	return result;
}

file_status status(const path& p, error_code& ec) throw(){
	struct stat st;
	if (::stat(p.c_str(), &st) == -1)
	{
		ec = make_error_code();
		if (ec.value() == errc::no_such_file_or_directory)
			return file_status(file_type::not_found);
		return file_status();
	}
	ec.clear();
	return stModeToFileStatus(st.st_mode);
}

bool exists(file_status s) throw(){
	return status_known(s) && s.type() != file_type::not_found;
}

bool exists(const path& p){
	return exists(status(p));
}

bool exists(const path& p, error_code& ec) throw(){
	file_status s = status(p, ec);
	if (status_known(s))
		ec.clear();
	return exists(s);
}


bool is_block_file(file_status s) throw()					{ return s.type() == file_type::block; }
bool is_block_file(const path& p)							{ return is_block_file(status(p)); }
bool is_block_file(const path& p, error_code& ec) throw()	{ return is_block_file(status(p, ec)); }

bool is_character_file(file_status s) throw() 					{ return s.type() == file_type::character; }
bool is_character_file(const path& p)							{ return is_character_file(status(p)); }	
bool is_character_file(const path& p, error_code& ec) throw()	{ return is_character_file(status(p, ec)); }

bool is_directory(file_status s) throw()				{ return s.type() == file_type::directory; }
bool is_directory(const path& p) 						{ return is_directory(status(p)); }
bool is_directory(const path& p, error_code& ec) throw(){ return is_directory(status(p, ec)); }

bool is_empty(const path& p){
	if (is_directory(p))
		throw std::runtime_error("is_empty not implemented for directory");
	return file_size(p) == 0;
}

bool is_empty(const path& p, error_code& ec) throw()
{
	if (is_directory(p, ec))
		ec = make_error_code(errc::owner_dead); // is_empty not implemented for directories
	else if (!ec)
	{
		bool result = file_size(p, ec) == 0;
		if (!ec)
			return result;
	}
	return false;
}

bool is_fifo(file_status s) throw()					{ return s.type() == file_type::fifo; }
bool is_fifo(const path& p)							{ return is_fifo(status(p)); }
bool is_fifo(const path& p, error_code& ec) throw()	{ return is_fifo(status(p, ec)); }

bool is_other(file_status s) throw() {
	return exists(s) && !is_regular_file(s) && !is_directory(s) && !is_symlink(s);
}
bool is_other(const path& p)						{ return is_other(status(p)); }
bool is_other(const path& p, error_code& ec) throw(){ return is_other(status(p, ec)); }

bool is_regular_file(file_status s) throw()					{ return s.type() == file_type::regular; } 
bool is_regular_file(const path& p)							{ return is_regular_file(status(p)); }
bool is_regular_file(const path& p, error_code& ec) throw()	{ return is_regular_file(status(p, ec)); }

bool is_socket(file_status s) throw()					{ return s.type() == file_type::socket; }
bool is_socket(const path& p)							{ return is_socket(status(p)); }
bool is_socket(const path& p, error_code& ec) throw()	{ return is_socket(status(p, ec)); }

bool is_symlink(file_status s) throw() { return s.type() == file_type::symlink; }
bool is_symlink(const path& p)							{ return is_symlink(status(p)); }
bool is_symlink(const path& p, error_code& ec) throw()	{ return is_symlink(status(p, ec)); }


uintmax_t file_size(const path& p)
{
	error_code ec;
	uintmax_t result = file_size(p, ec);
	if (ec)
		throw filesystem_error("file_size(const path& p=\""+ p.string() +"\"): " + ec.message(), p, ec);
	return result;
}

uintmax_t file_size(const path& p, error_code& ec) throw()
{
	struct stat st;
	if (::stat(p.c_str(), &st) == -1)
	{
		ec = make_error_code();
		return static_cast<uintmax_t>(-1);
	}
	ec.clear();
	return st.st_size;
}

uintmax_t hard_link_count(const path& p)
{
	error_code ec;
	uintmax_t result = hard_link_count(p, ec);
	if (ec)
		throw filesystem_error("hard_link_count(const path& p=\""+ p.string() +"\"): " + ec.message(), p, ec);
	return result;
}

uintmax_t hard_link_count(const path& p, error_code& ec) throw()
{
	struct stat st;
	if (::stat(p.c_str(), &st) == -1)
	{
		ec = make_error_code();
		return static_cast<uintmax_t>(-1);
	}
	ec.clear();
	return st.st_nlink;
}

directory_iterator begin(directory_iterator iter) throw()
{
	return iter;
}
directory_iterator end(const directory_iterator&) throw()
{
	return directory_iterator();
}


} /* namespace filesystem */
} /* namespace ft */
