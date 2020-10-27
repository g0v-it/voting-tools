////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	15/04/2018
//!
//! \par	Function:
//!	Contains the definitions of inline functions of the
//!	utility_space::ExceptionBase abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisFileName	Pointer to the name of the source file where
//!				exception was raised. The pointer must point to
//!				a zero terminated constant string, which is
//!				either constant, or never modified after
//!				creation, otherwise the behaviour is
//!				unpredictable.
//! \param	thisLineNumber	Number of the line where exception was raised.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ExceptionBase::ExceptionBase(const char* thisFileName,
		std_uint thisLineNumber) noexcept: FileName(thisFileName),
		LineNumber(thisLineNumber)
	{
	++Exceptions;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor. \n
//!	The purpose of its definition (as protected) is to forbid instantiation
//!	of ExceptionBase through copying. Only derived classes can call this
//!	method from their copy constructors.
//!
//! \param	thisException	ExceptionBase to be copied.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ExceptionBase::ExceptionBase(const ExceptionBase& thisException)
		noexcept: FileName(thisException.FileName),
		LineNumber(thisException.LineNumber)
	{
	++Exceptions;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move constructor. \n
//!	The purpose of its definition (as protected) is to forbid instantiation
//!	of ExceptionBase through copying. Only derived classes can call this
//!	method from their move constructors.
//!
//! \param	thisException	ExceptionBase to be copied.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ExceptionBase::ExceptionBase(ExceptionBase&& thisException) noexcept:
		FileName(thisException.FileName),
		LineNumber(thisException.LineNumber)
	{
	++Exceptions;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the name of the source file where the exception was raised.
//!
//! \throw	None.
//!
//! \returns	const	char*	Pointer to a constant string.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	const	char*	ExceptionBase::GetFileName(void) const noexcept
	{
	return FileName;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the number of the line where the exception was raised.
//!
//! \throw	None.
//!
//! \returns	std_uint	The line number.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	ExceptionBase::GetLineNumber(void) const noexcept
	{
	return LineNumber;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the number of exceptions thrown, but not yet caught and handled.
//!
//! \throw	None.
//!
//! \returns	std_uint	The number of exceptions thrown, but not yet
//!				caught and handled.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	ExceptionBase::GetExceptions(void) noexcept
	{
	return Exceptions;
	}

}
