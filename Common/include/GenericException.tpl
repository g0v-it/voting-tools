////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	M. Fiorentini
//!
//! \date	19/04/2018
//!
//! \par	Function:
//!	Contains the definitions of methods of the
//!	utility_space::GenericException class template.
//!
////////////////////////////////////////////////////////////////////////////////

namespace utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisExceptionKind	Kind of the exception.
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

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	INLINE	GenericException<EXCEPTION_TYPE, NUMBER_OF_EXCEPTIONS>::
			GenericException(EXCEPTION_TYPE thisExceptionKind,
			const char* thisFileName, std_uint thisLineNumber)
			noexcept: ExceptionBase(thisFileName, thisLineNumber),
			ExceptionKind(thisExceptionKind)
		{
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor.
//!
//! \param	thisException	GenericException to be copied.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	INLINE	GenericException<EXCEPTION_TYPE, NUMBER_OF_EXCEPTIONS>::
			GenericException(const GenericException& thisException)
			noexcept:
			ExceptionBase(static_cast<const ExceptionBase &>
			(thisException)),
			ExceptionKind(thisException.ExceptionKind)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move constructor.
//!
//! \param	thisException	GenericException to be copied.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	INLINE	GenericException<EXCEPTION_TYPE, NUMBER_OF_EXCEPTIONS>::
			GenericException(GenericException&& thisException)
			noexcept:
			ExceptionBase(static_cast<ExceptionBase &>
			(thisException)),
			ExceptionKind(thisException.ExceptionKind)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the kind of the exception.
//!
//! \throw	None.
//!
//! \returns	EXCEPTION_TYPE	Exception kind.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	INLINE	EXCEPTION_TYPE	GenericException<EXCEPTION_TYPE,
					NUMBER_OF_EXCEPTIONS>::
					GetExceptionKind(void) const noexcept
		{
		return ExceptionKind;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the name of the exception.
//!
//! \throw	None.
//!
//! \returns	const	char*	Exception name.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	INLINE	const	char*	GenericException<EXCEPTION_TYPE,
					NUMBER_OF_EXCEPTIONS>::
					GetExceptionName(void) const noexcept
		{
		assert(static_cast<unsigned int>(ExceptionKind) <
			number_of_elements(ExceptionName));
		return ExceptionName [static_cast<unsigned int>(ExceptionKind)];
		}

}
