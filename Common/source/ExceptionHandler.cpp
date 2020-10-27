////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	10/12/2018
//!
//! \par	Function:
//! 	Contains the definitions of static attributes and non inline functions
//!	of the utility_space::ExceptionHandler singleton class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"CommonMessage.h"
# include	"File.h"
# include	"ExceptionHandler.h"

# include	<stdlib.h>
# include	<stdio.h>
# include	<typeinfo>

# if	!defined USE_INLINE
# include	"ExceptionHandler.inl"
# endif

//! \def	FATAL_ERRORS_OFFSET
//!	Offset for fatal errors numeric code.
# define	FATAL_ERRORS_OFFSET		1000

//! \def	IO_ERRORS_OFFSET
//!	Offset for I/O errors numeric code.
# define	IO_ERRORS_OFFSET		2000

//! \def	APPLICATION_ERRORS_OFFSET
//!	Offset for application errors numeric code.
# define	APPLICATION_ERRORS_OFFSET	3000

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;

ExceptionHandler	ExceptionHandler::Instance;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle a fatal exception, writing a message on stdout.
//!
//! \param	Exc	Reference to the exception.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	NUMERIC_EXCEPTION_FORMAT
//! \see	FATAL_ERRORS_OFFSET
//! \see	FATAL_EXCEPTION_FORMAT
//!
////////////////////////////////////////////////////////////////////////////////

void	ExceptionHandler::HandleFatalException(const FatalException& Exc)
		noexcept
	{
	if (NumericMessage)
		ignore_value(fprintf(stdout, NUMERIC_EXCEPTION_FORMAT,
			static_cast<std_uint>(Exc.GetExceptionKind()) +
			FATAL_ERRORS_OFFSET));
	else
		ignore_value(fprintf(stdout, FATAL_EXCEPTION_FORMAT,
			Exc.GetExceptionName()));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle an I/O exception, writing a message on stdout.
//!
//! \param	Exc	Reference to the exception.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	IO_ERRORS_OFFSET
//! \see	NUMERIC_IO_EXCEPTION_FORMAT
//! \see	IO_EXCEPTION_FORMAT
//!
////////////////////////////////////////////////////////////////////////////////

void	ExceptionHandler::HandleIOException(const IOException& Exc) noexcept
	{
	if (NumericMessage)
		ignore_value(fprintf(stdout, NUMERIC_IO_EXCEPTION_FORMAT,
			static_cast<std_uint>(Exc.GetExceptionKind()) +
			IO_ERRORS_OFFSET, Exc.GetPathName().GetString()));
	else
		ignore_value(fprintf(stdout, IO_EXCEPTION_FORMAT,
			Exc.GetExceptionName(), Exc.GetPathName().GetString()));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle an application exception, writing a message on stdout.
//!
//! \param	Exc	Reference to the exception.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	APPLICATION_ERRORS_OFFSET
//! \see	NUMERIC_EXCEPTION_FORMAT
//! \see	APPLICATION_EXCEPTION_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	ExceptionHandler::HandleApplicationException(const ApplicationException&
		Exc) throw(IOException)
	{
	if (NumericMessage)
		{
		if (fprintf(stdout, NUMERIC_EXCEPTION_FORMAT,
			static_cast<std_uint>(Exc.GetExceptionKind()) +
			APPLICATION_ERRORS_OFFSET) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	else
		switch (Exc.GetExceptionKind())
			{
			case CORRUPTED_CANDIDATES_FILE:
			case CORRUPTED_GUARANTORS_FILE:
			case CORRUPTED_PARAMETERS_FILE:
			case CORRUPTED_VOTERS_FILE:
			case CANDIDATE_HASH_MISMATCH:
			case GUARANTOR_HASH_MISMATCH:
			case GUARANTOR_KEY_ALREADY_SET:
			case CANDIDATE_VOTE_ALREADY_SET:
				if (fprintf(stdout,
					APPLICATION_EXCEPTION_INDEX_FORMAT,
					Exc.GetExceptionName(),
					Exc.GetIndex() + 1) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				break;
			default:
				if (fprintf(stdout,
					APPLICATION_EXCEPTION_FORMAT,
					Exc.GetExceptionName()) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				break;
			}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle an exception by writing a message and exiting.
//!
//! \param	thisException	Reference to the exception to be handled.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
//! \see	TERMINATION_MESSAGE
//!
////////////////////////////////////////////////////////////////////////////////

void	ExceptionHandler::HandleException(const ExceptionBase& thisException)
		noexcept
	{
	if (typeid(thisException) == typeid(FatalException&))
		HandleFatalException(static_cast<const FatalException&>(
			thisException));
	if (typeid(thisException) == typeid(IOException&))
		HandleIOException(static_cast<const IOException&>(
			thisException));
	if (typeid(thisException) == typeid(ApplicationException&))
		try
			{
			HandleApplicationException(static_cast<const
				ApplicationException&>(thisException));
			}
		catch (const FatalException& Exc)
			{
			HandleFatalException(Exc);
			}
	ignore_value(fprintf(stdout, TERMINATION_MESSAGE));
	exit(EXIT_SUCCESS);
	}

}
