////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/04/2018
//!
//! \par	Function:
//!	Contains the definitions of inline functions of the
//!	io_space::IOException class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisExceptionKind		Kind of the expection
//! \param	thisPathName			Reference to the CharString
//!						containing the name of the File
//!						whose operation caused the
//!						error, or empty if the operation
//!						was not attempted on an open
//!						File.
//! \param	thisFileName			Pointer to the name of the
//!						source file where exception was
//!						raised. The pointer must point
//!						to a zero terminated string,
//!						which is either constant, or
//!						never modified after creation,
//!						otherwise the behaviour is
//!						unpredictable.
//! \param	thisLineNumber			Number of the line where
//!						exception was raised.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	IOException::IOException(IOErrorType thisExceptionKind,
		const CharString& thisPathName, const char* thisFileName,
		std_uint thisLineNumber) throw(FatalException):
		GenericException<IOErrorType,
		LAST_IO_EXCEPTION>(thisExceptionKind, thisFileName,
		thisLineNumber), PathName(thisPathName)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor.
//!
//! \param	thisException			Reference to the exception to be
//!						copied.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	IOException::IOException(const IOException& thisException)
		throw(FatalException): GenericException<IOErrorType,
		LAST_IO_EXCEPTION>(static_cast<const
		GenericException<IOErrorType,
		LAST_IO_EXCEPTION>&>(thisException)),
		PathName(thisException.PathName)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move constructor.
//!
//! \param	thisException			Reference to the exception to be
//!						copied.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	IOException::IOException(IOException&& thisException)
		throw(FatalException): GenericException<IOErrorType,
		LAST_IO_EXCEPTION>(static_cast<GenericException<IOErrorType,
		LAST_IO_EXCEPTION>&>(thisException)),
		PathName(thisException.PathName)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns the path name of the File on which the error occurred.
//!
//! \throw	None
//!
//! \returns	const	CharString&	Path name.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	const	CharString&	IOException::GetPathName(void) const noexcept
	{
	return PathName;
	}

}
