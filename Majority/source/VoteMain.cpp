////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/10/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	voting program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>

# include	"Standard.h"
# include	"Message.h"
# include	"FatalException.h"
# include	"NumericException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"ExceptionHandler.h"
# include	"GenericString.h"
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

static	void		Usage(void) throw(IOException);

static	std_uint	ReadInteger(const CharString& Line,
				std_uint& StartIndex, std_uint MaximumLength,
				ApplicationErrorType Error)
				throw(ApplicationException);

static	void		HandleVotes(const CharString& DirectoryPath,
				register std_uint Candidates,
				register std_uint Voters,
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
//! \see	VOTE_USAGE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(VOTE_USAGE_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a part of a String to a std_uint, starting at a given position
//!	and converting at most a given number of characters. \n
//!	The part of the string starting at StartIndex is converted, up to
//!	MaximumLength characters or to first non numeric character.
//!
//! \param	Line					Reference to the string
//!							to be converted.
//! \param	StartIndex				Starting index for the
//!							conversion. Valid range
//!							is
//!							[0 .. Line.GetLength() -
//!							1].
//!							On exit it is updated
//!							with the index of first
//!							not converted character.
//! \param	MaximumLength				The maximum length, that
//!							is, the maximum number
//!							of characters to be
//!							converted.
//! \param	Error					The value of the
//!							exception to be thrown
//!							in case of error.
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If StartIndex is not
//!							smaller than the string
//!							length.
//! \throw	application_space::Error		If the string is empty
//!							or it does not start
//!							with a digit or the
//!							converted string cannot
//!							be represented as a
//!							std_uint.
//!
//! \returns	std_uint				The converted value.
//!
//! \note
//!	If the function throws an exception, the value of StartIndex is
//!	undefined.
//!
////////////////////////////////////////////////////////////////////////////////

static	std_uint	ReadInteger(const CharString& Line,
				std_uint& StartIndex, std_uint MaximumLength,
				ApplicationErrorType Error)
				throw(ApplicationException)
	{
	std_uint	Value;

	try
		{
		Line.ToNumber(Value, StartIndex, MaximumLength);
		}
	catch (FatalException Exc)
		{
		assert(Exc.GetExceptionKind() == ILLEGAL_CONVERSION);
		throw make_application_exception(Error);
		}
	catch (NumericException Exc)
		{
		assert(Exc.GetExceptionKind() == NUMERIC_OVERFLOW);
		throw make_application_exception(Error);
		}
	return Value;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle the votes.
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
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing one of the
//!							files.
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
//! \throw	application_space::INVALID_VOTER	If the number of the
//!							voter is not valid.
//! \throw	application_space::INVALID_VOTE		If a vote is not valid.
//! \throw	application_space::MISSING_VOTER	If some vote is missing.
//! \throw	application_space::MISSING_SIGNATURE	If the signature is
//!							missing.
//! \throw	application_space::INVALID_VOTE_FORMAT	If there is not exactly
//!							one space among votes
//!							and between last vote
//!							and the signature.
//!
//! \returns	None.
//!
//! \note
//!	The random generator used to select the votes whose random parts is
//!	changed when a real vote is inserted must depend only upon the keys and
//!	the real voter, so that it generates the same sequence of numbers for
//!	each voter.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	VOTE_SET_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	HandleVotes(const CharString& DirectoryPath,
			register std_uint Candidates, register std_uint Voters,
			register std_uint MaximumVote,
			const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			const byte VotesKey [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint		VoteIndex;
	register	std_uint		LineIndex;
	register	std_uint		LineLength;
	register	std_uint		SingleVote;
			CharString		Line;
			File			InputFile;
			File			OutputFile;
			VotersFile		CurrentVotersFile;
			VotesFile		CurrentVotesFile;
			Vector<std_uint>	VoterIndex;
			RandomGenerator		FillerGenerator;
			RandomGenerator		IndexGenerator;
			VoteData		CurrentVote;

	InitializeGenerator(FillerGenerator, VotersKey, VotesKey);
	CurrentVotersFile.Read(MakeVotersPathName(DirectoryPath), Voters,
		VoterIndex, VotersKey);
	CurrentVotesFile.Open(MakeVotesPathName(DirectoryPath), Candidates,
		Voters, MaximumVote, VotesKey);
	InputFile.OpenInput();
	OutputFile.OpenOutput();
	for (;;)
		{
		try
			{
			InputFile.ReadLine<char>(Line);
			}
		catch (IOException Exc)
			{
			if (Exc.GetExceptionKind() == END_OF_FILE and
				Line.IsEmpty())
				break;
			throw;
			}
		try
			{
			LineLength = Line.GetLength();
			if (LineLength  == 0)
				throw make_application_exception(
					INVALID_VOTE_FORMAT);
			LineIndex = 0;
			CurrentVote.Voter = ReadInteger(Line, LineIndex,
				LineLength, INVALID_VOTER);
			if (CurrentVote.Voter == 0 or
				CurrentVote.Voter > Voters)
				throw make_application_exception(INVALID_VOTER);
			--CurrentVote.Voter;
			CurrentVote.Vote.Clear();
			if (LineIndex >= LineLength)
				throw make_application_exception(MISSING_VOTES);
			if (Line [LineIndex++] !=
				CharacterManager<char>::GetSpace())
				throw make_application_exception(
					INVALID_VOTE_FORMAT);
			for (VoteIndex = 0; VoteIndex < Candidates; ++VoteIndex)
				{
				SingleVote = ReadInteger(Line, LineIndex,
					LineLength, INVALID_VOTE);
				if (SingleVote > MaximumVote)
					throw make_application_exception(
						INVALID_VOTE);
				CurrentVote.Vote.Append(SingleVote);
				if (LineIndex >= LineLength)
					throw make_application_exception(
						VoteIndex == Candidates - 1?
						MISSING_SIGNATURE:
						MISSING_VOTES);
				if (Line [LineIndex++] !=
					CharacterManager<char>::GetSpace())
					throw make_application_exception(
						INVALID_VOTE_FORMAT);
				}
			DecodeHex(Line.GetString() + LineIndex,
				CurrentVote.Signature, SIGNATURE_LENGTH);
			}
		catch (ApplicationException Exc)
			{
			ExceptionHandler::GetInstance().
				HandleApplicationException(Exc);
			continue;
			}
		CurrentVotesFile.WriteVote(CurrentVote, VotersKey, VotesKey,
			FillerGenerator);
		if (fprintf(stdout, VOTE_SET_FORMAT, CurrentVote.Voter + 1) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		OutputFile.Flush();
		}
	InputFile.Close();
	OutputFile.Close();
	CurrentVotesFile.Close();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for collecting votes. \n
//!	It keeps reading from standard input and writing confimation or error
//!	messages on standard output, until it is killed or the end of standard
//!	input is reached.
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
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		std_uint	Candidates;
		std_uint	Voters;
		std_uint	MaximumVote;
		CharString	DirectoryPath;
		CharString	KeyPath;
		byte		VotersKey [ENCRYPTION_KEY_LENGTH];
		byte		VotesKey [ENCRYPTION_KEY_LENGTH];

		HandleOptions(argc, argv);
		if (argc != 3)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		KeyPath = CharString(argv [2]);
		ReadKeys(KeyPath, VotersKey, VotesKey);
		ReadParameters(DirectoryPath, Candidates, Voters, MaximumVote,
			VotersKey, VotesKey);
		HandleVotes(DirectoryPath, Candidates, Voters, MaximumVote,
			VotersKey, VotesKey);
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
