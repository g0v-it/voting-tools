////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	15/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the utility_space::ExceptionBase abstract
//!	class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined EXCEPTION_BASE_H

# define	EXCEPTION_BASE_H

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	ExceptionBase
//!	The ExceptionBase abstract class is the base class for all exceptions
//!	classes.
//!
////////////////////////////////////////////////////////////////////////////////

class	ExceptionBase
	{
	private:

//! \property	FileName
//!	Name of the file where the exception was thrown. \n
//!	To be able to deal with all exceptions, including memory overflow, no
//!	memory is allocated and the pointer to the original string, set during
//!	exception creation, is kept until the exception is handled.
			const		char*		FileName;

//! \property	LineNumber
//!	Number of the line where the exception was thrown.
					std_uint	LineNumber;

//! \property	Exceptions
//!	Number of exceptions thrown, but not yet caught and handled.
//!
//! \note
//!	The mechanism used to count exceptions is not thread-safe.
		static	volatile	std_uint	Exceptions;

//! \property	UnknownExceptionName
//!	Default name of unknown exceptions. \n
//!	To be able to deal with all exceptions, including memory overflow, no
//!	memory is allocated and exception name is kept as a simple zero
//!	terminated string.
		static	const	char*	const	UnknownExceptionName;

			const	ExceptionBase&	operator = (const ExceptionBase&
							thisException)
							noexcept = delete;

			const	ExceptionBase&	operator = (ExceptionBase&&
							thisException)
							noexcept = delete;

	protected:

						ExceptionBase(const char*
							thisFileName,
							std_uint thisLineNumber)
							noexcept;

	public:

						ExceptionBase(const
							ExceptionBase&
							thisException) noexcept;

						ExceptionBase(ExceptionBase&&
							thisException) noexcept;

		virtual				~ExceptionBase(void) noexcept;

			const	char*		GetFileName(void) const
							noexcept;

				std_uint	GetLineNumber(void) const
							noexcept;

		virtual	const	char*		GetExceptionName(void) const
							noexcept;

		static		std_uint	GetExceptions(void) noexcept;

	};

}

# if	defined USE_INLINE
# include	"ExceptionBase.inl"
# endif

# endif
