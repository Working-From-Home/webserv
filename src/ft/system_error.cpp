#include "FilesystemError.hpp"
#include "FilesystemError.hpp"

namespace ft{

error_code make_error_code(errc e) throw() {
	return error_code(e);
}

} /*namespace ft */
