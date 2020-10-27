////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/04/2018
//!
//! \par	Function:
//! 	Contains the declaration of the io_space::IOExceptionBase class,
//!	generated from utility_space::GenericException class template,
//!	with EXCEPTION_TYPE equal to io_space::IOErrorType and
//!	NUMBER_OF_EXCEPTIONS equal to io_space::LAST_IO_EXCEPTION, and of the
//!	io_space::IOException class, derived from the io_space::IOExceptionBase
//!	class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined IO_EXCEPTION_H

# define	IO_EXCEPTION_H

# include	"GenericException.h"
# include	"GenericString.h"

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \enum	IOErrorType
//!	Define enumerated type for I/O exceptions.
//!
//! \note
//!	If the order is altered or if a new I/O exception is added, the
//!	initialization of the io_space::IOExceptionBase::ExceptionName array
//!	must be updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	IOErrorType
		{
			//!	File object destroyed without having closed the
			//!	file.
		FILE_NOT_CLOSED,

			//!	Operation attemped on a file not open.
		FILE_NOT_OPEN,

			//!	Open attemped on a file already open.
		FILE_ALREADY_OPEN,

			//!	Invalid open mode.
		FILE_INVALID_OPEN_MODE,

			//!	Illegal path name.
		FILE_INVALID_PATH_NAME,

			//!	Attempt to open too many files.
		TOO_MANY_OPEN_FILES,

			//!	I/O error.
		FILE_IO_ERROR,

			//!	Error when closing a file.
		FILE_CLOSE_ERROR,

			//!	File read error.
		FILE_READ_ERROR,

			//!	File write error.
		FILE_WRITE_ERROR,

			//!	File seek error.
		FILE_SEEK_ERROR,

			//!	Read after end of file.
		END_OF_FILE,

			//!	Attempt to open a file that does not exist.
		FILE_DOES_NOT_EXIST,

			//!	Attempt to create a file that already exists.
		FILE_ALREADY_EXISTS,

			//!	The path refers to a directory.
		FILE_IS_A_DIRECTORY,

			//!	The path does not refer to a directory.
		FILE_NOT_A_DIRECTORY,

			//!	Attempt to open a file without having the
			//!	required permissions.
		FILE_PERMISSION_DENIED,

			//!	Attempt to lock a file that would cause a
			//!	deadlock.
		FILE_DEADLOCK,

			//!	Too many locks open.
		TOO_MANY_LOCKS,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_IO_EXCEPTION
		};

////////////////////////////////////////////////////////////////////////////////
//! \class	IOExceptionBase
//!	Parent class for I/O exceptions, instance of
//!	utility_space::GenericException, with EXCEPTION_TYPE equal to
//!	io_space::IOErrorType and NUMBER_OF_EXCEPTIONS equal to
//!	io_space::LAST_IO_EXCEPTION.
//!
//! \see	io_space::IOException
//!
////////////////////////////////////////////////////////////////////////////////

typedef	GenericException<IOErrorType, LAST_IO_EXCEPTION>	IOExceptionBase;

////////////////////////////////////////////////////////////////////////////////
//! \class IOException
//!	Class for I/O exceptions, derived from io_space::IOExceptionBase.
//!
////////////////////////////////////////////////////////////////////////////////

class	IOException: public IOExceptionBase
	{
	private:

//! \property	PathName
//!	Path name of the file on which the error occurred.
			CharString	PathName;

		const	IOException&	operator = (const IOException&
						thisException) noexcept =
						delete;

		const	IOException&	operator = (IOException&& thisException)
						noexcept = delete;

	public:

					IOException(IOErrorType
						thisExceptionKind,
						const CharString& thisPathName,
						const char* thisFileName,
						std_uint thisLineNumber)
						throw(FatalException);

					IOException(const IOException&
						thisException)
						throw(FatalException);

					IOException(IOException&&
						thisException)
						throw(FatalException);

		const	CharString&	GetPathName(void) const noexcept;

	};

////////////////////////////////////////////////////////////////////////////////
//! \def	make_IO_exception(ErrorKind, PathName)
//!	Create an io_space::IOException object, using current source file name
//!	and current line number.
//!
//! \param	ErrorKind	Enumerated value of type io_space::IOErrorType.
//! \param	PathName	Reference to the CharString containing the name
//!				of the file whose operation caused the error, or
//!				empty if the operation was not attempted on an
//!				open file.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_IO_exception(ErrorKind, PathName)	\
			IOException((ErrorKind), (PathName), __FILE__, __LINE__)

}

# if	defined USE_INLINE
# include	"IOException.inl"
# endif

# endif
