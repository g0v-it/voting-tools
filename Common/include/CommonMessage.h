////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	10/10/2018
//!
//! \par	Function:
//!	Contains the definitions of the common messages of election handling
//!	programs.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	COMMON_MESSAGE_H

# define	COMMON_MESSAGE_H

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	ExceptionMessage	Exception handling messages
//!	Definitions of messages used to handle an exception.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	FATAL_EXCEPTION_FORMAT
//!	Format used to write a fatal exception.
# define	FATAL_EXCEPTION_FORMAT	"Fatal error: %s\n"

//! \def	IO_EXCEPTION_FORMAT
//!	Format used to write an IO exception.
# define	IO_EXCEPTION_FORMAT	"I/O error: %s on file %s\n"

//! \def	APPLICATION_EXCEPTION_FORMAT
//!	Format used to write an application exception without record index.
# define	APPLICATION_EXCEPTION_FORMAT \
	"Application error: %s\n"

//! \def	APPLICATION_EXCEPTION_INDEX_FORMAT
//!	Format used to write an application exception with record index.
# define	APPLICATION_EXCEPTION_INDEX_FORMAT \
	"Application error: %s on record %u\n"

//! \def	NUMERIC_EXCEPTION_FORMAT
//!	Format used to write the numeric code of an exception.
# define	NUMERIC_EXCEPTION_FORMAT \
	"Error: %u\n"

//! \def	NUMERIC_IO_EXCEPTION_FORMAT
//!	Format used to write the numeric code of an I/O exception.
# define	NUMERIC_IO_EXCEPTION_FORMAT \
	"Error: %u on file %s\n"

//! \def	TERMINATION_MESSAGE
//!	Message used to announce program termination.
# define	TERMINATION_MESSAGE	"Program terminated\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	CommonGenericFormat	Common generic formats
//!	Definitions of formats used by various functions.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	FILLER_FORMAT
//!	Format of output filler of variable length.
# define	FILLER_FORMAT		"%*c"

//! \def	UNSIGNED_NUMBER_FORMAT
//!	Format used to print unsigned numbers.
# define	UNSIGNED_NUMBER_FORMAT	"%*u"

//! \def	STRING_FORMAT
//!	Format used to print output strings.
# define	STRING_FORMAT		"%.*s"

//! \def	DATE_TIME_FORMAT
//!	Format used to print date and time strings.
# define	DATE_TIME_FORMAT	"%d:%m:%Y at %H:%M:%S"

//! \def	DATE_TIME_LENGTH
//!	Maximum length of a string representing date and time.
# define	DATE_TIME_LENGTH	30

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	Options	Options
//!	Definitions of options.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	NUMERIC_ERROR_OPTION
//!	OPtion used to get numeric error messages.
# define	NUMERIC_ERROR_OPTION	"--numeric-errors"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

# endif
