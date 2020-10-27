////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	03/09/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	noise generation program.
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
# include	"SystemManager.h"
# include	"RandomGenerator.h"
# include	"VotesFile.h"
# include	"Utility.h"
# include	"LocalUtility.h"

using	namespace	utility_space;
using	namespace	io_space;
using	namespace	application_space;
using	namespace	system_space;

static	void		Usage(void) throw(IOException);

static	std_uint	ReadInteger(const CharString& Line,
				std_uint& StartIndex, std_uint MaximumLength,
				ApplicationErrorType Error)
				throw(ApplicationException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	NOISE_USAGE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(NOISE_USAGE_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for noise generation votes. \n
//!	It keeps generating random noise, that is, changing the filler parts of
//!	randomly selected votes, until it is killed.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	MILLISECONDS_PER_SECOND
//! \def	MAXIMUM_NOISE_INTERVAL
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		register	std_uint	Iterations;
		register	std_uint	Voters;
		register	std_uint	TimeInterval;
				std_uint	Candidates;
				std_uint	MaximumVote;
				CharString	DirectoryPath;
				CharString	KeyPath;
				RandomGenerator	Generator;
				VotesFile	CurrentVotesFile;
				byte		VotersKey
							[ENCRYPTION_KEY_LENGTH];
				byte		VotesKey
							[ENCRYPTION_KEY_LENGTH];

		HandleOptions(argc, argv);
		if (argc < 4 or argc > 5)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		KeyPath = CharString(argv [2]);
		Iterations = DecodeInteger(argv [3]);
		if (argc == 5)
			{
			TimeInterval = DecodeInteger(argv [4]);
			if (TimeInterval == 0 or
				TimeInterval > MAXIMUM_NOISE_INTERVAL)
				throw make_application_exception(
					INVALID_INTERVAL);
			}
		else
			TimeInterval = 1;
		ReadKeys(KeyPath, VotersKey, VotesKey);
		ReadParameters(DirectoryPath, Candidates, Voters, MaximumVote,
			VotersKey, VotesKey);
		InitializeGenerator(Generator, VotersKey, VotesKey);
		CurrentVotesFile.Open(MakeVotesPathName(DirectoryPath),
			Candidates, Voters, MaximumVote, VotesKey);
		--Voters;
		TimeInterval *= MILLISECONDS_PER_SECOND;
		for (; Iterations > 0; --Iterations)
			{
			CurrentVotesFile.Modify(Generator.Generate(Voters),
				Generator);
			CurrentVotesFile.SystemFlush();
			SystemManager::GetInstance()->Sleep(TimeInterval);
			}
		CurrentVotesFile.Close();
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
