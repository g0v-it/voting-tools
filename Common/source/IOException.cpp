////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/04/2018
//!
//! \par	Function:
//! 	Contains the definitions of static attributes and non inline functions
//!	of the io_space::IOException class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"IOException.h"

# if	!defined USE_INLINE
# include	"IOException.inl"
# endif

namespace	utility_space
{

using	namespace	io_space;

//! \property	IOExceptionBase::ExceptionName
//!	Names of the I/O exceptions.\n
//!	The order of the strings must correspond to that of the
//!	io_space::IOErrorType enumerated type.
template<>
const	char*	const	IOExceptionBase::ExceptionName [LAST_IO_EXCEPTION] =
	{
	"file not closed",
	"file not open",
	"file already open",
	"illegal open mode",
	"invalid path name",
	"I/O error",
	"too many open files",
	"file close error",
	"file read error",
	"file write error",
	"file seek error",
	"end of file",
	"file does not exist",
	"file already exists",
	"file is a directory",
	"file is not a directory",
	"permission denied",
	"file lock causes a deadlock",
	"too many locks"
	};

}
