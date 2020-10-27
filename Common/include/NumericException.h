////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	26/07/2008
//!
//! \par	Function:
//!	Contains the declaration of the numeric_space::NumericException
//!	class, generated from the utility_space::GenericException class
//!	template, with enum type numeric_space::NumericErrorType.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined NUMERIC_EXCEPTION_H

# define	NUMERIC_EXCEPTION_H

# include	"GenericException.h"

namespace	numeric_space
{

using	namespace	utility_space;

////////////////////////////////////////////////////////////////////////////////
//! \enum	NumericErrorType
//!	Enumerated type for numeric exceptions.
//!
//! \note
//!	If the order is altered or if a new numeric exception is added, the
//!	initialization of the numeric_space::NumericException::ExceptionName
//!	array must be updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	NumericErrorType
		{
			//!	Overflow.
		NUMERIC_OVERFLOW,

			//!	Division by zero.
		DIVISION_BY_ZERO,

			//!	Argument out of function domain.
		DOMAIN_ERROR,

			//!	Attempt to invert a singular matrix.
		SINGULAR_MATRIX,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_NUMERIC_EXCEPTION
		};

////////////////////////////////////////////////////////////////////////////////
//! \class	NumericException
//!	Class for numeric exceptions, instance of
//!	utility_space::GenericException with EXCEPTION_TYPE equal to
//!	numeric_space::NumericErrorType and NUMBER_OF_EXCEPTIONS equal to
//!	numeric_space::LAST_NUMERIC_EXCEPTION.
//!
////////////////////////////////////////////////////////////////////////////////

typedef	GenericException<NumericErrorType, LAST_NUMERIC_EXCEPTION>
		NumericException;


////////////////////////////////////////////////////////////////////////////////
//! \def	make_numeric_exception(ErrorKind)
//!	Create a NumericException object, using current source file name and
//!	current line number.
//!
//! \param	ErrorKind	Enumerated value of type
//!				numeric_space::NumericErrorType.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_numeric_exception(ErrorKind)	\
			NumericException((ErrorKind), __FILE__, __LINE__)

}

# endif
