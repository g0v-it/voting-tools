////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	04/11/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	result computing program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<time.h>

# include	"Standard.h"
# include	"Parameter.h"
# include	"Message.h"
# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"ExceptionHandler.h"
# include	"GenericString.h"
# include	"CharacterManager.h"
# include	"SystemManager.h"
# include	"CandidateVote.h"
# include	"VotesFile.h"
# include	"Vector.h"
# include	"OrderedVector.h"
# include	"Utility.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;
using	namespace	application_space;
using	namespace	system_space;

static	void	Usage(void) throw(IOException);

static	void	ComputeResult(const CharString& DirectoryPath,
			register std_uint Candidates, register std_uint Voters,
			register std_uint MaximumVote,
			const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			const byte VotesKey [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException,
			ApplicationException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	RESULT_USAGE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(RESULT_USAGE_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute and write the results.
//!
//! \param	DirectoryPath				Reference to the
//!							directory path name.
//! \param	Candidates				Number of candidates.
//! \param	Voters					Number of voters
//! \param	MaximumVote				Maximum possible vote.
//! \param	VotersKey				Array that contains the
//!							encryption key of the
//!							voters' file.
//! \param	VotesKey				Array that contains the
//!							encryption key of the
//!							votes file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name of the
//!							voters' file or of the
//!							votes file is not valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the voters' file or
//!							the votes file does not
//!							exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							voters' file or the
//!							votes file or if one of
//!							their path names
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//! \throw	io_space::FILE_SEEK_ERROR		If the votes file cannot
//!							be seeked.
//! \throw	io_space::FILE_READ_ERROR		If the number of bytes
//!							read is less than
//!							expected.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing one of the
//!							files.
//! \throw	io_space::FILE_WRITE_ERROR		If writing on stdout
//!							fails.
//! \throw	application_space::INVALID_VOTERS_FILE_LENGTH	If the voters'
//!							file length is not
//!							correct.
//! \throw	application_space::CORRUPTED_VOTERS_FILE	If the voters'
//!							file contains invalid
//! \throw	application_space::INVALID_VOTES_FILE_LENGTH	If the votes
//!							file length is not
//!							correct.
//! \throw	application_space::CORRUPTED_VOTES_FILE	If the votes file
//!							contains invalid data.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	ELECTION_HEADER_FORMAT
//! \see	ALL_VOTERS_MESSAGE
//! \see	VOTERS_FORMAT
//! \see	RESULT_HEADER
//! \see	VOTES_HEADER
//! \see	VOTE_FIELD_LENGTH
//! \see	FILLER_FORMAT
//! \see	UNSIGNED_NUMBER_FORMAT
//! \see	CANDIDATE_RESULT_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	ComputeResult(const CharString& DirectoryPath,
			register std_uint Candidates, register std_uint Voters,
			register std_uint MaximumVote,
			const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			const byte VotesKey [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint		Index;
	register	std_uint		Candidate;
	register	std_uint		Value;
	register	std_uint		Rank;
			char			TimeBuffer [DATE_TIME_LENGTH];
			time_t			Time;
			VotesFile		CurrentVotesFile;
			CandidateVote		LocalVote(MaximumVote);
			Vector<std_uint>	CurrentVote;
			Vector<CandidateVote>	ElectionVote;
			Vector<std_uint>	OrderedIndex(Candidates);

	CurrentVotesFile.Open(MakeVotesPathName(DirectoryPath), Candidates,
		Voters, MaximumVote, VotesKey);
	ElectionVote.Resize(Candidates);
	ElectionVote.Append(LocalVote, Candidates);
	Time = time(nullptr);
	strftime(TimeBuffer, DATE_TIME_LENGTH, DATE_TIME_FORMAT,
		localtime(&Time));
	Value = 0;
	for (Index = 0; Index < Voters; ++Index)
		{
		CurrentVotesFile.Read(Index, CurrentVote);
		for (Candidate = 0; Candidate < Candidates; ++Candidate)
			if (CurrentVote [Candidate] != 0)
				break;
		if (Candidate < Candidates)
			{
			++Value;
			for (Candidate = 0; Candidate < Candidates; ++Candidate)
				ElectionVote [Candidate].
					IncrementCount(CurrentVote [Candidate]);
			}
		}
	CurrentVotesFile.Close();
	if (printf(ELECTION_HEADER_FORMAT, Candidates, Voters, MaximumVote,
		TimeBuffer) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	if (Voters == Value)
		{
		if (printf(ALL_VOTERS_MESSAGE) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	else
		if (printf(VOTERS_FORMAT, Value) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
	Value = (Value + 1) / 2;
	for (Candidate = 0; Candidate < Candidates; ++Candidate)
		ElectionVote [Candidate].ComputeLowerExtreme(Value);
	LocalVote.ComputeLowerExtreme(Value);
	if (printf(RESULT_HEADER) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	ignore_value(PrintCenteredHeader(CharString(VOTES_HEADER),
		(VOTE_FIELD_LENGTH + 1) * (MaximumVote + 1) - 1, 0));
	if (printf(FILLER_FORMAT, 1, CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	if (printf(FILLER_FORMAT, static_cast<int>(strlen(RESULT_HEADER)),
		CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	for (Index = 0; Index <= MaximumVote; ++Index)
		{
		if (printf(UNSIGNED_NUMBER_FORMAT, VOTE_FIELD_LENGTH, Index) <
			0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(FILLER_FORMAT, 1,
			CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	if (printf(FILLER_FORMAT, 1, CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	OrderedVector<CandidateVote>::SortIndices(ElectionVote, OrderedIndex);
	Rank = 0;
	for (Candidate = Candidates; Candidate > 0;)
		{
		Index = OrderedIndex [--Candidate];
		if (ElectionVote [Index] != LocalVote)
			Rank = Candidates - Candidate;
		LocalVote = ElectionVote [Index];
		if (printf(CANDIDATE_RESULT_FORMAT, Rank, Index,
			LocalVote.GetLowerExtreme()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		for (Value = 0; Value <= MaximumVote; ++Value)
			{
			if (printf(UNSIGNED_NUMBER_FORMAT, VOTE_FIELD_LENGTH,
				LocalVote.GetCounter(Value)) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			if (printf(FILLER_FORMAT, 1,
				CharacterManager<char>::GetSpace()) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			}
		if (printf(FILLER_FORMAT, 1,
			CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for computing the result of the election. \n
//!	If a time interval is specified, it keeps computing and printing the
//!	result at regular intervals, until it is killed, otherwise it prints the
//!	result only once.
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
//! \see	MAXIMUM_RESULT_INTERVAL
//! \see	MILLISECONDS_PER_MINUTE
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		register	std_uint	TimeInterval;
				std_uint	Candidates;
				std_uint	Voters;
				std_uint	MaximumVote;
				CharString	DirectoryPath;
				CharString	KeyPath;
				byte		VotersKey
							[ENCRYPTION_KEY_LENGTH];
				byte		VotesKey
							[ENCRYPTION_KEY_LENGTH];

		HandleOptions(argc, argv);
		if (argc < 3 or argc > 4)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		KeyPath = CharString(argv [2]);
		if (argc == 4)
			{
			TimeInterval = DecodeInteger(argv [3]);
			if (TimeInterval == 0 or
				TimeInterval > MAXIMUM_RESULT_INTERVAL)
				throw make_application_exception(
					INVALID_INTERVAL);
			TimeInterval *= MILLISECONDS_PER_MINUTE;
			}
		else
			TimeInterval = 0;
		ReadKeys(KeyPath, VotersKey, VotesKey);
		ReadParameters(DirectoryPath, Candidates, Voters, MaximumVote,
			VotersKey, VotesKey);
		for (;;)
			{
			ComputeResult(DirectoryPath, Candidates, Voters,
				MaximumVote, VotersKey, VotesKey);
			if (TimeInterval == 0)
				break;
			SystemManager::GetInstance()->Sleep(TimeInterval);
			}
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
