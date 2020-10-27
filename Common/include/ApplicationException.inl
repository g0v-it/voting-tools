////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	17/04/2018
//!
//! \par	Function:
//!	Contains the definitions of inline functions of the
//!	application_space::ApplicationException class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	application_space
{

using	namespace	utility_space;


////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisExceptionKind	Kind of the expection
//! \param	thisFileName		Pointer to the name of the source file
//!					where exception was raised. The pointer
//!					must point to a zero terminated string,
//!					which is either constant, or never
//!					modified after creation, otherwise the
//!					behaviour is unpredictable.
//! \param	thisLineNumber		Number of the line where exception was
//!					raised.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ApplicationException::ApplicationException(ApplicationErrorType
		thisExceptionKind, const char* thisFileName,
		std_uint thisLineNumber) noexcept:
		ApplicationExceptionBase(thisExceptionKind, thisFileName,
		thisLineNumber), Index(0)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisExceptionKind	Kind of the expection
//! \param	thisIndex		Index of the record containing invalid
//!					data.
//! \param	thisFileName		Pointer to the name of the source file
//!					where exception was raised. The pointer
//!					must point to a zero terminated string,
//!					which is either constant, or never
//!					modified after creation, otherwise the
//!					behaviour is unpredictable.
//! \param	thisLineNumber		Number of the line where exception was
//!					raised.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ApplicationException::ApplicationException(ApplicationErrorType
		thisExceptionKind, std_uint thisIndex, const char* thisFileName,
		std_uint thisLineNumber) noexcept:
		ApplicationExceptionBase(thisExceptionKind, thisFileName,
		thisLineNumber), Index(thisIndex)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor.
//!
//! \param	thisException	Reference to the exception to be copied.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	ApplicationException::ApplicationException(const ApplicationException&
		thisException) noexcept:
		ApplicationExceptionBase(static_cast<const
		ApplicationExceptionBase&>(thisException)),
		Index(thisException.Index)
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

INLINE	ApplicationException::ApplicationException(ApplicationException&&
		thisException) noexcept:
		ApplicationExceptionBase(static_cast<ApplicationExceptionBase&>(
		thisException)), Index(thisException.Index)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns the index of the invalid record.
//!
//! \throw	None
//!
//! \returns	std_uint	Index of the invalid record.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	ApplicationException::GetIndex(void) const noexcept
	{
	return Index;
	}

}
