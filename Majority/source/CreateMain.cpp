////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/10/2018
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
# include	"RandomGenerator.h"
# include	"VotersFile.h"
# include	"VotesFile.h"
# include	"Utility.h"
# include	"LocalUtility.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;
using	namespace	application_space;

static	void	Usage(void) throw(IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	CREATE_USAGE_FORMAT
//! \see	MINIMUM_CANDIDATES
//! \see	MAXIMUM_CANDIDATES
//! \see	MINIMUM_VOTERS
//! \see	MAXIMUM_VOTERS
//! \see	MINIMUM_VOTE
//! \see	MAXIMUM_VOTE
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(CREATE_USAGE_FORMAT, MINIMUM_CANDIDATES, MAXIMUM_CANDIDATES,
		MINIMUM_VOTERS, MAXIMUM_VOTERS, MINIMUM_VOTE, MAXIMUM_VOTE) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
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
//! \see	MINIMUM_VOTERS
//! \see	MAXIMUM_VOTERS
//! \see	MINIMUM_VOTE
//! \see	MAXIMUM_VOTE
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	CREATION_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		std_uint	Candidates;
		std_uint	Voters;
		std_uint	MaximumVote;
		char		EndOfLine;
		CharString	DirectoryPath;
		CharString	KeyPath;
		byte		VotersKey [ENCRYPTION_KEY_LENGTH];
		byte		VotesKey [ENCRYPTION_KEY_LENGTH];
		char		Buffer [4 * ENCRYPTION_KEY_LENGTH];
		VotersFile	CurrentVotersFile;
		VotesFile	CurrentVotesFile;
		RandomGenerator	Generator;
		File		ElectionFile;

		HandleOptions(argc, argv);
		if (argc != 6)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		Candidates = DecodeInteger(argv [2]);
		Voters = DecodeInteger(argv [3]);
		MaximumVote = DecodeInteger(argv [4]);
		KeyPath = CharString(argv [5]);
		if (Candidates < MINIMUM_CANDIDATES or
			Candidates > MAXIMUM_CANDIDATES)
			throw make_application_exception(
				INVALID_CANDIDATES_NUMBER);
		if (Voters < MINIMUM_VOTERS or Voters > MAXIMUM_VOTERS)
			throw make_application_exception(INVALID_VOTERS_NUMBER);
		if (MaximumVote < MINIMUM_VOTE or MaximumVote > MAXIMUM_VOTE)
			throw make_application_exception(INVALID_MAXIMUM_VOTE);
		ReadKeys(KeyPath, VotersKey, VotesKey);
		InitializeGenerator(Generator, VotersKey, VotesKey);
		FileManager::GetInstance()->CreateDirectory(DirectoryPath);
		CurrentVotersFile.Create(MakeVotersPathName(DirectoryPath),
			Voters, VotersKey, Generator);
		CurrentVotesFile.Create(MakeVotesPathName(DirectoryPath),
			Candidates, Voters, VotesKey, Generator);
		EndOfLine = CharacterManager<char>:: GetEOLN();
		ElectionFile.OpenText(MakeParametersPathName(DirectoryPath),
			OPEN_WRITE);
		ElectionFile.WriteNumber<char>(Candidates);
		ElectionFile.WriteCharacter<char>(EndOfLine);
		ElectionFile.WriteNumber<char>(Voters);
		ElectionFile.WriteCharacter<char>(EndOfLine);
		ElectionFile.WriteNumber<char>(MaximumVote);
		ElectionFile.WriteCharacter<char>(EndOfLine);
		EncodeKey(VotersKey, Buffer, Generator);
		ElectionFile.Write(Buffer, 1, 4 * ENCRYPTION_KEY_LENGTH);
		ElectionFile.WriteCharacter<char>(EndOfLine);
		EncodeKey(VotesKey, Buffer, Generator);
		ElectionFile.Write(Buffer, 1, 4 * ENCRYPTION_KEY_LENGTH);
		ElectionFile.WriteCharacter<char>(EndOfLine);
		ElectionFile.Close();
		if (printf(CREATE_FORMAT, Candidates, Voters, MaximumVote) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
