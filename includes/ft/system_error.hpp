#ifndef SYSTEM_ERROR_HPP
#define SYSTEM_ERROR_HPP

#include <errno.h>

namespace ft {
//   class error_category;
//   const error_category& generic_category() throw();
//   const error_category& system_category() throw();
 
  class error_code;
//   class error_condition;
  class system_error;
 
//   template<class T>
//     struct is_error_code_enum : public false_type {};
 
//   template<class T>
//     struct is_error_condition_enum : public false_type {};


// equivalent to enum class ... (c++98 don't have enum class)
struct errc{
	enum errcEnum {
		none						    	= 0,
		address_family_not_supported    	= EAFNOSUPPORT,
		address_in_use                    	= EADDRINUSE,
		address_not_available				= EADDRNOTAVAIL,
		already_connected					= EISCONN,
		argument_list_too_long				= E2BIG,
		argument_out_of_domain				= EDOM,
		bad_address							= EFAULT,
		bad_file_descriptor					= EBADF,
		bad_message							= EBADMSG,
		broken_pipe							= EPIPE,
		connection_aborted					= ECONNABORTED,
		connection_already_in_progress		= EALREADY,
		connection_refused					= ECONNREFUSED,
		connection_reset					= ECONNRESET,
		cross_device_link					= EXDEV,
		destination_address_required		= EDESTADDRREQ,
		device_or_resource_busy				= EBUSY,
		directory_not_empty					= ENOTEMPTY,
		executable_format_error				= ENOEXEC,
		file_exists							= EEXIST,
		file_too_large						= EFBIG,
		filename_too_long					= ENAMETOOLONG,
		function_not_supported				= ENOSYS,
		host_unreachable					= EHOSTUNREACH,
		identifier_removed					= EIDRM,
		illegal_byte_sequence				= EILSEQ,
		inappropriate_io_control_operation	= ENOTTY,
		interrupted							= EINTR,
		invalid_argument					= EINVAL,
		invalid_seek						= ESPIPE,
		io_error							= EIO,
		is_a_directory						= EISDIR,
		message_size						= EMSGSIZE,
		network_down						= ENETDOWN,
		network_reset						= ENETRESET,
		network_unreachable					= ENETUNREACH,
		no_buffer_space						= ENOBUFS,
		no_child_process					= ECHILD,
		no_link								= ENOLINK,
		no_lock_available					= ENOLCK,
		no_message_available				= ENODATA,
		no_message							= ENOMSG,
		no_protocol_option					= ENOPROTOOPT,
		no_space_on_device					= ENOSPC,
		no_stream_resources					= ENOSR,
		no_such_device_or_address			= ENXIO,
		no_such_device						= ENODEV,
		no_such_file_or_directory			= ENOENT,
		no_such_process						= ESRCH,
		not_a_directory						= ENOTDIR,
		not_a_socket						= ENOTSOCK,
		not_a_stream						= ENOSTR,
		not_connected						= ENOTCONN,
		not_enough_memory					= ENOMEM,
		not_supported						= ENOTSUP,
		operation_canceled					= ECANCELED,
		operation_in_progress				= EINPROGRESS,
		operation_not_permitted				= EPERM,
		operation_not_supported				= EOPNOTSUPP,
		operation_would_block				= EWOULDBLOCK,
		owner_dead							= EOWNERDEAD,
		permission_denied					= EACCES,
		protocol_error						= EPROTO,
		protocol_not_supported				= EPROTONOSUPPORT,
		read_only_file_system				= EROFS,
		resource_deadlock_would_occur		= EDEADLK,
		resource_unavailable_try_again		= EAGAIN,
		result_out_of_range					= ERANGE,
		state_not_recoverable				= ENOTRECOVERABLE,
		stream_timeout						= ETIME,
		text_file_busy						= ETXTBSY,
		timed_out							= ETIMEDOUT,
		too_many_files_open_in_system		= ENFILE,
		too_many_files_open					= EMFILE,
		too_many_links						= EMLINK,
		too_many_symbolic_link_levels		= ELOOP,
		value_too_large						= EOVERFLOW,
		wrong_protocol_type					= EPROTOTYPE,
	};
	errc(errcEnum e): _e(e) {}
	operator errcEnum() const throw(){
		return _e;
    }
    friend bool operator==(const errc& lhs, const errc& rhs){
      return lhs._e == rhs._e;
    }
private:
	errcEnum _e;
};
 
//   template<> struct is_error_condition_enum<errc> : true_type {};
 
  // non-member functions
  error_code make_error_code(errc e = errc::none) throw();
 
//   template<class charT, class traits>
//     basic_ostream<charT, traits>&
//       operator<<(basic_ostream<charT, traits>& os, const error_code& ec);
 
//   // non-member functions
//   error_condition make_error_condition(errc e) throw();
 
//   // comparison functions
//   bool operator==(const error_code& lhs, const error_code& rhs) throw();
//   bool operator==(const error_code& lhs, const error_condition& rhs) throw();
//   bool operator==(const error_condition& lhs, const error_condition& rhs) throw();
//   strong_ordering operator<=>(const error_code& lhs,
//                               const error_code& rhs) throw();
//   strong_ordering operator<=>(const error_condition& lhs,
//                               const error_condition& rhs) throw();
 
//   // system error support
//   template<class T>
//     inline constexpr bool is_error_code_enum_v = is_error_code_enum<T>::value;
//   template<class T>
//     inline constexpr bool is_error_condition_enum_v = is_error_condition_enum<T>::value;


} /* namespace ft */

#endif /* SYSTEM_ERROR_HPP */
