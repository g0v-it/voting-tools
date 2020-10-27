////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	26/07/2008
//!
//! \par	Function:
//!	Contains the definitions of static attributes of the
//!	numeric_space::NumericException class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"NumericException.h"

namespace	utility_space
{

using	namespace	numeric_space;

//! \property	NumericException::ExceptionName
//!	Names of the numeric exceptions.\n
//!	The order of the strings must correspond to that of the
//!	numeric_space::NumericErrorType enumerated type.
template<>
const	char*	const	NumericException::ExceptionName
				[LAST_NUMERIC_EXCEPTION] =
	{
	"overflow",
	"division by zero",
	"argument out of function domain",
	"singular matrix"
	};

}
