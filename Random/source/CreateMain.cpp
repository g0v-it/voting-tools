////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	16/04/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	creation program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>

# include	"Standard.h"
# include	"Parameter.h"
# include	"Message.h"
# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"ExceptionHandler.h"
# include	"GenericString.h"
# include	"FileManager.h"
# include	"File.h"
# include	"Utility.h"
# include	"LocalUtility.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

static	void	Usage(void) throw(IOException);

static	void	CreateFile(const CharString FilePath, register std_uint Records,
			std_uint RecordLength, register bool WriteIndex)
			throw(FatalException, IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	CREATE_USAGE_FORMAT
//! \see	NUMERIC_ERROR_OPTION
//! \see	MINIMUM_CANDIDATES
//! \see	MAXIMUM_CANDIDATES
//! \see	MINIMUM_GUARANTORS
//! \see	MAXIMUM_GUARANTORS
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(CREATE_USAGE_FORMAT, NUMERIC_ERROR_OPTION,
		MINIMUM_CANDIDATES, MAXIMUM_CANDIDATES, MINIMUM_GUARANTORS,
		MAXIMUM_GUARANTORS) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create a file, containing a given number of empty keys with zero hash
//!	values.
//!
//! \param	FilePath				Path name of the file.
//! \param	Records					Number of recors to be
//!							created.
//! \param	RecordLength				Length of a record in
//!							bytes.
//! \param	WriteIndex				Flag specifying whether
//!							the record number must
//!							be written, as a zero
//!							filled string of
//!							CANDIDATE_NUMBER_LENGTH
//!							characters at the
//!							beginning of each
//!							record.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT		If Recordlength is
//!							greater than
//!							MAXIMUM_RECORD_LENGTH.
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the file.
//! \throw	io_space::FILE_WRITE_ERROR		If writing on stdout
//!							fails.
//!
//! \returns	None.
//!
//! \note
//!	The file is created as a binary file.
//!
//! \see	MAXIMUM_RECORD_LENGTH
//! \see	CANDIDATE_NUMBER_LENGTH
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//! \see	CandidatesFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

static	void	CreateFile(const CharString FilePath, register std_uint Records,
			std_uint RecordLength, register bool WriteIndex)
			throw(FatalException, IOException)
	{
	register	std_uint	Index;
			File		NewFile;
			byte		Buffer [MAXIMUM_RECORD_LENGTH];

	if (RecordLength > MAXIMUM_RECORD_LENGTH)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);
	ignore_value(memset(Buffer, 0, RecordLength));
	NewFile.OpenBinary(FilePath, OPEN_WRITE);
	for (Index = 0; Index < Records; ++Index)
		{
		if (WriteIndex)
			ConvertInteger(Index, Buffer, CANDIDATE_NUMBER_LENGTH);
		NewFile.Write(Buffer, RecordLength, 1);
		}
	NewFile.Close();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for starting an election. \n
//!	It creates a directory for the election and two files:
//!	one for guarantors, one for voters, with their passwords and hashes.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	MINIMUM_CANDIDATES
//! \see	MAXIMUM_CANDIDATES
//! \see	MINIMUM_GUARANTORS
//! \see	MAXIMUM_GUARANTORS
//! \see	CANDIDATE_RECORD_LENGTH
//! \see	GUARANTOR_RECORD_LENGTH
//! \see	CREATE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		CharString	DirectoryPath;
		std_uint	Candidates;
		std_uint	Guarantors;

		HandleOptions(argc, argv);
		if (argc != 4)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		Candidates = DecodeInteger(argv [2]);
		Guarantors = DecodeInteger(argv [3]);
		if (Candidates < MINIMUM_CANDIDATES or
			Candidates > MAXIMUM_CANDIDATES)
			throw make_application_exception(
				INVALID_CANDIDATES_NUMBER);
		if (Guarantors < MINIMUM_GUARANTORS or
			Guarantors > MAXIMUM_GUARANTORS)
			throw make_application_exception(
				INVALID_GUARANTORS_NUMBER);
		FileManager::GetInstance()->CreateDirectory(DirectoryPath);
		CreateFile(MakeGuarantorsPathName(DirectoryPath), Guarantors,
			GUARANTOR_RECORD_LENGTH, false);
		CreateFile(MakeCandidatesPathName(DirectoryPath), Candidates,
			CANDIDATE_RECORD_LENGTH, true);
		if (printf(CREATE_FORMAT, Candidates, Guarantors) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
