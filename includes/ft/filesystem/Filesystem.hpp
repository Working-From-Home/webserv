#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "Path.hpp"

namespace ft { namespace filesystem {

// class path;
  
  void swap(path& lhs, path& rhs);

  inline bool operator==(const path& lhs, const path& rhs) {return lhs._path == rhs._path;}
  inline bool operator< (const path& lhs, const path& rhs) {return lhs._path < rhs._path;}
  inline bool operator==(const path& lhs, const std::string& rhs) {return lhs == path(rhs);}
  inline bool operator==(const std::string& lhs, const path& rhs) { return path(lhs) == rhs;}
  inline bool operator!=(const path& lhs, const path& rhs) { return !(lhs == rhs); }
  inline bool operator<=(const path& lhs, const path& rhs) { return !(rhs < lhs); }
  inline bool operator> (const path& lhs, const path& rhs) { return rhs < lhs; }
  inline bool operator>=(const path& lhs, const path& rhs) { return !(lhs < rhs); }
  inline path operator/ (const path& lhs, const path& rhs) { return path(lhs) /= rhs;}
  inline path	operator/ (const path& lhs, const std::string& rhs) { return path(lhs) /= rhs;}

  // template <class charT, class traits>
  // basic_ostream<charT, traits>&
  // operator<<(basic_ostream<charT, traits>& os, const path& p);

  // template <class charT, class traits>
  // basic_istream<charT, traits>&
  // operator>>(basic_istream<charT, traits>& is, path& p);

  // template <class Source>  
  //   path u8path(const Source& source);
  // template <class InputIterator>
  //   path u8path(InputIterator first, InputIterator last);

  // class filesystem_error;      
  // class directory_entry;

  // class directory_iterator;

  // // enable directory_iterator range-based for statements
  // directory_iterator begin(directory_iterator iter) ;
  // directory_iterator end(const directory_iterator&) ;

  // class recursive_directory_iterator;

  // // enable recursive_directory_iterator range-based for statements
  // recursive_directory_iterator begin(recursive_directory_iterator iter) ;
  // recursive_directory_iterator end(const recursive_directory_iterator&) ;

  // class file_status;

  // struct space_info
  // {
  //   uintmax_t capacity;
  //   uintmax_t free; 
  //   uintmax_t available;
  // };

  // enum class file_type;
  // enum class perms;
  // enum class copy_options;
  // enum class directory_options;

  // typedef chrono::time_point<trivial-clock>  file_time_type;

  // // operational functions

  // path absolute(const path& p, const path& base=current_path());

  // path canonical(const path& p, const path& base = current_path());
  // path canonical(const path& p, error_code& ec);
  // path canonical(const path& p, const path& base, error_code& ec);

  // void copy(const path& from, const path& to);
  // void copy(const path& from, const path& to, error_code& ec) ;
  // void copy(const path& from, const path& to, copy_options options);
  // void copy(const path& from, const path& to, copy_options options,  
  //        error_code& ec) ;

  // bool copy_file(const path& from, const path& to);
  // bool copy_file(const path& from, const path& to, error_code& ec) ;
  // bool copy_file(const path& from, const path& to, copy_options option);
  // bool copy_file(const path& from, const path& to, copy_options option,
  //                error_code& ec) ;

  // void copy_symlink(const path& existing_symlink, const path& new_symlink);
  // void copy_symlink(const path& existing_symlink, const path& new_symlink,
  //                   error_code& ec) ;

  // bool create_directories(const path& p);
  // bool create_directories(const path& p, error_code& ec) ;

  // bool create_directory(const path& p);
  // bool create_directory(const path& p, error_code& ec) ;

  // bool create_directory(const path& p, const path& attributes);
  // bool create_directory(const path& p, const path& attributes,
  //                       error_code& ec) ;

  // void create_directory_symlink(const path& to, const path& new_symlink);
  // void create_directory_symlink(const path& to, const path& new_symlink,
  //                               error_code& ec) ;

  // void create_hard_link(const path& to, const path& new_hard_link);
  // void create_hard_link(const path& to, const path& new_hard_link,
  //                       error_code& ec) ;

  // void create_symlink(const path& to, const path& new_symlink);
  // void create_symlink(const path& to, const path& new_symlink,
  //                     error_code& ec) ;

  // path current_path();
  // path current_path(error_code& ec);
  // void current_path(const path& p);
  // void current_path(const path& p, error_code& ec) ;

  // bool exists(file_status s) ;
  // bool exists(const path& p);
  // bool exists(const path& p, error_code& ec) ;

  // bool equivalent(const path& p1, const path& p2);
  // bool equivalent(const path& p1, const path& p2, error_code& ec) ;

  // uintmax_t file_size(const path& p);
  // uintmax_t file_size(const path& p, error_code& ec) ;

  // uintmax_t hard_link_count(const path& p);
  // uintmax_t hard_link_count(const path& p, error_code& ec) ;

  // bool is_block_file(file_status s) ;
  // bool is_block_file(const path& p);
  // bool is_block_file(const path& p, error_code& ec) ;

  // bool is_character_file(file_status s) ;
  // bool is_character_file(const path& p);
  // bool is_character_file(const path& p, error_code& ec) ;

  // bool is_directory(file_status s) ;
  // bool is_directory(const path& p);
  // bool is_directory(const path& p, error_code& ec) ;

  // bool is_empty(const path& p);
  // bool is_empty(const path& p, error_code& ec) ;

  // bool is_fifo(file_status s) ;
  // bool is_fifo(const path& p);
  // bool is_fifo(const path& p, error_code& ec) ;

  // bool is_other(file_status s) ;
  // bool is_other(const path& p);
  // bool is_other(const path& p, error_code& ec) ;

  // bool is_regular_file(file_status s) ; 
  // bool is_regular_file(const path& p);
  // bool is_regular_file(const path& p, error_code& ec) ;

  // bool is_socket(file_status s) ;
  // bool is_socket(const path& p);
  // bool is_socket(const path& p, error_code& ec) ;

  // bool is_symlink(file_status s) ;
  // bool is_symlink(const path& p);
  // bool is_symlink(const path& p, error_code& ec) ;

  // file_time_type  last_write_time(const path& p);
  // file_time_type  last_write_time(const path& p, error_code& ec) ;
  // void last_write_time(const path& p, file_time_type new_time);
  // void last_write_time(const path& p, file_time_type new_time,
  //                      error_code& ec) ;
                       
  // void permissions(const path& p, perms prms);
  // void permissions(const path& p, perms prms, error_code& ec) ;

  // path read_symlink(const path& p);
  // path read_symlink(const path& p, error_code& ec);

  // bool remove(const path& p);
  // bool remove(const path& p, error_code& ec) ;

  // uintmax_t remove_all(const path& p);
  // uintmax_t remove_all(const path& p, error_code& ec) ;

  // void rename(const path& from, const path& to);
  // void rename(const path& from, const path& to, error_code& ec) ;

  // void resize_file(const path& p, uintmax_t size);
  // void resize_file(const path& p, uintmax_t size, error_code& ec) ;

  // space_info space(const path& p);
  // space_info space(const path& p, error_code& ec) ;

  // file_status status(const path& p);
  // file_status status(const path& p, error_code& ec) ;

  // bool status_known(file_status s) ;

  // file_status symlink_status(const path& p);
  // file_status symlink_status(const path& p, error_code& ec) ;

  // path system_complete(const path& p);
  // path system_complete(const path& p, error_code& ec);

  // path temp_directory_path();
  // path temp_directory_path(error_code& ec);


} /* namespace filesystem */
} /* namespace ft */

#endif /* FILESYSTEM_HPP */
