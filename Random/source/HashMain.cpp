////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	15/05/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the hash
//!	computation program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>

# include	"Standard.h"
# include	"Parameter.h"
# include	"Message.h"
# include	"ApplicationException.h"
# include	"ExceptionHandler.h"
# include	"Utility.h"
# include	"File.h"
# include	"Hash.h"

using	namespace	utility_space;
using	namespace	application_space;

static	void	Usage(void) throw(IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::STDOUT_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	HASH_USAGE_FORMAT
//! \see	NUMERIC_ERROR_OPTION
//! \see	KEY_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(HASH_USAGE_FORMAT, NUMERIC_ERROR_OPTION, KEY_LENGTH) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for hash computation.\n
//!	It computes the hash of a key.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	HASH_VALUE_MESSAGE
//! \see	STRING_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		byte	Key [KEY_LENGTH];
		byte	Hash [HASH_LENGTH];
		char	Buffer [2 * HASH_LENGTH];

		HandleOptions(argc, argv);
		if (argc != 2)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DecodeHex(argv [1], Key, KEY_LENGTH);
		ComputeHash(Key, Hash);
		EncodeHex(Hash, Buffer, HASH_LENGTH);
		if (printf(HASH_VALUE_MESSAGE) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(STRING_FORMAT, 2 * HASH_LENGTH, Buffer) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
