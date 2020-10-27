////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	10/12/2018
//!
//! \par	Function:
//! 	Contains the declaration of the utility_space::ExceptionHandler
//!	singleton class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined EXCEPTION_HANDLER_H

# define	EXCEPTION_HANDLER_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	ExceptionHandler
//!	The ExceptioHandler singleton class is a simple exception handler. \n
//!	Exceptions are handler by printing a message, which can be a string or
//!	a numeric code and exiting.
//!
//! \note
//!	Only fatal, I/O and application exceptions are handler; numeric
//!	exceptions are always handled internally by the programs.
//!
////////////////////////////////////////////////////////////////////////////////

class	ExceptionHandler
	{
	private:

//! \property	NumericMessage
//!	Flag indicating whether error messages shall be limited to a numeric
//!	code.
			bool			NumericMessage;

//! \property	Instance
//!	Singleton class instance.
		static	ExceptionHandler	Instance;

						ExceptionHandler(void) noexcept;

						ExceptionHandler(const
							ExceptionHandler&
							thisException)
							noexcept = delete;

						ExceptionHandler(
							ExceptionHandler&&
							thisException)
							noexcept = delete;

						~ExceptionHandler(void)
							noexcept;

			ExceptionHandler&	operator = (const
							ExceptionHandler&
							thisException)
							noexcept = delete;

		const	ExceptionHandler&	operator = (ExceptionHandler&&
							thisException)
							noexcept = delete;

			void			HandleFatalException(const
							FatalException& Exc)
							noexcept;

			void			HandleIOException(const
							IOException& Exc)
							noexcept;

	public:

			void			SetNumericMessage(bool
							thisNumericMessage)
							noexcept;

			void			HandleApplicationException(const
							ApplicationException&
							Exc) throw(IOException);

		[[noreturn]]	void		HandleException(const
							ExceptionBase&
							thisException) noexcept;

		static	ExceptionHandler&	GetInstance(void) noexcept;

	};


}

# if	defined USE_INLINE
# include	"ExceptionHAndler.inl"
# endif

# endif
