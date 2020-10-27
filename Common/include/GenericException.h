////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	19/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the utility_space::GenericException class
//!	template.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined GENERIC_EXCEPTION_H

# define	GENERIC_EXCEPTION_H

# include	"ExceptionBase.h"

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	GenericException
//!	GenericException is a template class, derived from
//!	utility_space::ExceptionBase, which can be used to define exception
//!	classes.
//!
//! \tparam	EXCEPTION_TYPE		Template parameter EXCEPTION_TYPE can be
//!					any enumerated data type.
//! \tparam	NUMBER_OF_EXCEPTIONS	Template parameter NUMBER_OF_EXCEPTIONS
//!					must be the number of exceptions in
//!					EXCEPTION_TYPE.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename EXCEPTION_TYPE, unsigned int NUMBER_OF_EXCEPTIONS>
	class	GenericException: public ExceptionBase
	{
	private:

//! \property	ExceptionKind
//!	Kind of the exception.
			EXCEPTION_TYPE	ExceptionKind;

//! \property	ExceptionName
//!	Names of the exceptions. \n
//!	To be able to deal with all exceptions, including memory overflow, no
//!	memory is allocated and exception names are kept as a simple table of
//!	zero terminated strings.
		static	const	char*	const	ExceptionName
							[NUMBER_OF_EXCEPTIONS];

		const	GenericException&	operator = (const
							GenericException&
							thisException)
							noexcept = delete;

		const	GenericException&	operator = (GenericException&&
							thisException)
							noexcept = delete;

	public:

					GenericException(EXCEPTION_TYPE
						thisExceptionKind,
						const char* thisFileName,
						std_uint thisLineNumber)
						noexcept;

					GenericException(const GenericException&
						thisException) noexcept;

					GenericException(GenericException&&
						thisException) noexcept;

			EXCEPTION_TYPE	GetExceptionKind(void) const noexcept;

		const	char*		GetExceptionName(void) const noexcept;

	};

}

# include	"GenericException.tpl"

# endif
