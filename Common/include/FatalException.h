////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	07/07/2008
//!
//! \par	Function:
//!	Contains the declaration of the utility_space::FatalException
//!	class, generated from the utility_space::GenericException class
//!	template, with enum type utility_space::FatalErrorType.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined FATAL_EXCEPTION_H

# define	FATAL_EXCEPTION_H

# include	"GenericException.h"

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \enum	FatalErrorType
//!	Enumerated type for fatal exceptions.
//!
//! \note
//!	If the order is altered or if a new fatal exception is added, the
//!	initialization of the utility_space::FatalException::ExceptionName array
//!	must be updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	FatalErrorType
		{
			//!	Out of memory.
		OUT_OF_MEMORY,

			//!	Vector index out of bounds.
		INDEX_OUT_OF_BOUNDS,

			//!	Illegal argument.
		ILLEGAL_ARGUMENT,

			//!	Illegal conversion.
		ILLEGAL_CONVERSION,

			//!	Null pointer.
		INVALID_POINTER,

			//!	Illegal function call.
		ILLEGAL_FUNCTION_CALL,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_FATAL_EXCEPTION
		};

////////////////////////////////////////////////////////////////////////////////
//! \class	FatalException
//!	Class for fatal exceptions, instance of utility_space::GenericException
//!	with EXCEPTION_TYPE equal to utility_space::FatalErrorType
//!	and NUMBER_OF_EXCEPTIONS equal to utility_space::LAST_FATAL_EXCEPTION.
//!
////////////////////////////////////////////////////////////////////////////////

typedef	GenericException<FatalErrorType, LAST_FATAL_EXCEPTION>	FatalException;


////////////////////////////////////////////////////////////////////////////////
//! \def	make_fatal_exception(ErrorKind)
//!	Create a FatalException object, using current source file name and
//!	current line number.
//!
//! \param	ErrorKind	Enumerated value of type
//!				utility_space::FatalErrorType.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_fatal_exception(ErrorKind)	\
			FatalException((ErrorKind), __FILE__, __LINE__)

}

# endif
