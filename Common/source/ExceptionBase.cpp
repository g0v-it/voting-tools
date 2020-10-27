////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	15/04/2018
//!
//! \par	Function:
//!	Contains the definitions of non inline functions of the
//!	utility_space::ExceptionBase abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"ExceptionBase.h"

# if	!defined USE_INLINE
# include	"ExceptionBase.inl"
# endif

namespace	utility_space
{

//! \property	ExceptionBase::Exceptions
//!	Number of exceptions thrown, but not yet caught and handled.
//!
//! \note
//!	The mechanism used to count exceptions is not thread-safe.
volatile	std_uint	ExceptionBase::Exceptions;

//! \property	ExceptionBase::UnknownExceptionName
//!	Default name of unknown exceptions.
const	char*	const	ExceptionBase::UnknownExceptionName = "unknown";

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

ExceptionBase::~ExceptionBase(void) noexcept
	{
	--Exceptions;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns the default name of unknown exceptions.
//!
//! \throw	None.
//!
//! \returns	const	char*	Exception name.
//!
////////////////////////////////////////////////////////////////////////////////

const	char*	ExceptionBase::GetExceptionName(void) const noexcept
	{
	return UnknownExceptionName;
	}

}
