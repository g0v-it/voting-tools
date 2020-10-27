////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	07/07/2008
//!
//! \par	Function:
//!	Contains the definitions of static attributes of the
//!	utility_space::FatalException class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"FatalException.h"

namespace	utility_space
{

//! \property	FatalException::ExceptionName
//!	Names of the fatal exceptions.\n
//!	The order of the strings must correspond to that of the
//!	utility_space::FatalErrorType enumerated type.
template<>
const	char*	const	FatalException::ExceptionName [LAST_FATAL_EXCEPTION] =
	{
	"out of memory",
	"index out of bounds",
	"illegal argument",
	"illegal conversion",
	"invalid pointer",
	"illegal function call"
	};

}
