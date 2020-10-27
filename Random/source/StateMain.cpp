////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	26/04/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	state state inspection program.
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
# include	"CharacterManager.h"
# include	"Vector.h"
# include	"OrderedVector.h"
# include	"File.h"
# include	"LocalUtility.h"
# include	"State.h"
# include	"Key.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	HashedVote
//!	Represents a candidate's hashed vote.
//!
//! \see	VOTE_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

struct	VoteContainer
	{
	public:

//! property	Vote
//!	The hashed vote.
			bool		EmptyKey;

//! property	Vote
//!	The hashed vote.
			byte		HashedVote [VOTE_LENGTH];

					VoteContainer(void) noexcept = default;

					VoteContainer(bool thisEmptyKey,
						const byte thisHashedVote
						[VOTE_LENGTH]) noexcept;

		static	CompareType	Compare(const VoteContainer&
						FirstArgument, const
						VoteContainer& SecondArgument)
						noexcept;

	};

static	void	Usage(void) throw(IOException);

static	void	PrintGuarantorsData(const CharString DirectoryPath,
			register std_uint Guarantors, register bool PrintKey)
			throw(FatalException, IOException);

static	void	PrintCandidatesData(const CharString DirectoryPath,
			register const StateInfo& ElectionState,
			register bool PrintVote,
			register Vector<VoteContainer>& Vote)
			throw(FatalException, IOException);

static	void	PrintResult(const CharString DirectoryPath,
			register const StateInfo& ElectionState,
			register const Vector<VoteContainer>& Vote)
			throw(FatalException, IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor
//!
//! \param	thisEmptyKey	flag indicating whether the key is empty.
//! \param	thisHashedVote	Hashed vote.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	VoteContainer::VoteContainer(bool thisEmptyKey,
		const byte thisHashedVote [VOTE_LENGTH]) noexcept:
		EmptyKey(thisEmptyKey), HashedVote()
	{
	ignore_value(memcpy(HashedVote, thisHashedVote, VOTE_LENGTH));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparison function for votes.
//!
//! \param	FirstArgument	Reference to first operand for comparison.
//! \param	SecondArgument	Reference to second operand for comparison.
//!
//! \throw	None.
//!
//! \returns	CompareType	Comparison result, that is:
//!				- COMPARE_LESS, if first operand vote is less
//!					than second operand vote;
//!				- COMPARE_GREATER, if first operand vote is
//!					greater than second operand vote;
//!				- COMPARE_EQUAL, otherwise.
//!				.
//!
////////////////////////////////////////////////////////////////////////////////

CompareType	VoteContainer::Compare(const VoteContainer& FirstArgument,
			const VoteContainer& SecondArgument) noexcept
	{
	int	Value;

	Value = memcmp(FirstArgument.HashedVote, SecondArgument.HashedVote,
		VOTE_LENGTH);
	if (Value == 0)
		return COMPARE_EQUAL;
	return Value > 0? COMPARE_GREATER: COMPARE_LESS;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Print on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	STATE_USAGE_MESSAGE
//! \see	NUMERIC_ERROR_OPTION
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(STATE_USAGE_MESSAGE, NUMERIC_ERROR_OPTION) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout guarantors' data.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	Guarantors				The number of
//!							guarantors.
//! \param	PrintKey				Flag indicating whether
//!							guarantors' keys shall
//!							be printed.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name of the
//!							directory is not valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access the
//!							guarantor file.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the guarantors file
//!							does not exist.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading the guarantors
//!							file.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the guarantors
//!							file.
//! \throw	io_space::FILE_WRITE_ERROR		If writing on stdout
//!							fails.
//!
//! \returns	None.
//!
//! \see	GUARANTORS_HEADER_FORMAT
//! \see	GUARANTOR_NUMBER_HEADER
//! \see	NUMBER_HEADER
//! \see	KEY_HEADER
//! \see	HASH_HEADER
//! \see	SIGNATURE_HEADER
//! \see	GUARANTOR_NUMBER_LENGTH
//! \see	UNSIGNED_NUMBER_FORMAT
//! \see	STRING_FORMAT
//! \see	GUARANTOR_RECORD_LENGTH
//! \see	GUARANTOR_HASH_OFFSET
//! \see	GUARANTOR_SIGNATURE_OFFSET
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

static	void	PrintGuarantorsData(const CharString DirectoryPath,
			register std_uint Guarantors, register bool PrintKey)
			throw(FatalException, IOException)
	{
	register	std_uint	Index;
			byte		Buffer [GUARANTOR_RECORD_LENGTH];
			byte		Zero [GUARANTOR_RECORD_LENGTH];
			char		OutputBuffer
						[2 * GUARANTOR_RECORD_LENGTH];
			CharString	PathName;
			File		GuarantorFile;

	if (printf(GUARANTORS_HEADER_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(GUARANTOR_NUMBER_HEADER),
		GUARANTOR_NUMBER_LENGTH, 0);
	if (PrintKey)
		{
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		Index = PrintCenteredHeader(CharString(KEY_HEADER),
			2 * KEY_LENGTH, Index);
		}
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(HASH_HEADER), 2 * HASH_LENGTH,
		Index);
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(SIGNATURE_HEADER),
		2 * SIGNATURE_LENGTH, Index);
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	ignore_value(memset(Zero, 0, sizeof(Zero)));
	PathName = MakeGuarantorsPathName(DirectoryPath);
	GuarantorFile.OpenBinary(PathName, OPEN_READ);
	for (Index = 0; Index < Guarantors;)
		{
		if (GuarantorFile.Read(Buffer, GUARANTOR_RECORD_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		if (printf(UNSIGNED_NUMBER_FORMAT, GUARANTOR_NUMBER_LENGTH,
			++Index) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (PrintKey)
			{
			if (memcmp(Buffer, Zero, KEY_LENGTH) == 0)
				ignore_value(memset(OutputBuffer,
					CharacterManager<char>::GetMinusSign(),
					2 * KEY_LENGTH));
			else
				EncodeHex(Buffer, OutputBuffer, KEY_LENGTH);
			if (putchar(CharacterManager<char>::GetSpace()) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			if (printf(STRING_FORMAT, 2 * KEY_LENGTH,
				OutputBuffer) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			}
		if (memcmp(Buffer + GUARANTOR_HASH_OFFSET, Zero, HASH_LENGTH) ==
			0)
			ignore_value(memset(OutputBuffer,
				CharacterManager<char>::GetMinusSign(),
				2 * HASH_LENGTH));
		else
			EncodeHex(Buffer + GUARANTOR_HASH_OFFSET, OutputBuffer,
				HASH_LENGTH);
		OutputBuffer [2 * HASH_LENGTH] =
			CharacterManager<char>::GetSpace();
		if (memcmp(Buffer + GUARANTOR_SIGNATURE_OFFSET, Zero,
			SIGNATURE_LENGTH) == 0)
			ignore_value(memset(OutputBuffer + 2 * HASH_LENGTH + 1,
				CharacterManager<char>::GetMinusSign(),
				2 * SIGNATURE_LENGTH));
		else
			EncodeHex(Buffer + GUARANTOR_SIGNATURE_OFFSET,
				OutputBuffer + 2 * HASH_LENGTH + 1,
				SIGNATURE_LENGTH);
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(STRING_FORMAT,
			2 * HASH_LENGTH + 1 + 2 * SIGNATURE_LENGTH,
			OutputBuffer) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	GuarantorFile.Close();
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout candidates' data.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	ElectionState				Reference to the
//!							variable that contains
//!							the state of the
//!							election.
//! \param	PrintVote				Flag indicating whether
//!							candidate' votes shall
//!							be printed.
//! \param	Vote					Vector that upon return
//!							will contain candidates'
//!							votes, in candidate
//!							index order, if
//!							PrintVote is true.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name of the
//!							directory is not valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access an
//!							election data file.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If an election data file
//!							does not exist.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading an election data
//!							file.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing an election data
//!							file.
//! \throw	io_space::FILE_WRITE_ERROR		If writing on stdout
//!							fails.
//!
//! \returns	None.
//!
//! \note
//!	If PrintVote is true, candidates' votes will be appended to the Vote
//!	vector, otherwise the Vote Vector will be unchanged.
//!
//! \see	CANDIDATES_HEADER_FORMAT
//! \see	CANDIDATE_NUMBER_HEADER
//! \see	CANDIDATE_NUMBER_LENGTH
//! \see	NUMBER_HEADER
//! \see	KEY_HEADER
//! \see	MIXED_HEY_HEADER
//! \see	SIGNATURE_HEADER
//! \see	VOTE_HEADER
//! \see	UNSIGNED_NUMBER_FORMAT
//! \see	STRING_FORMAT
//! \see	CANDIDATE_RECORD_LENGTH
//! \see	CANDIDATE_KEY_OFFSET
//! \see	CANDIDATE_SIGNATURE_OFFSET
//! \see	CANDIDATE_VOTE_OFFSET
//! \see	CANDIDATE_KEY_LENGTH
//! \see	KEY_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	VOTE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	CandidatesFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

static	void	PrintCandidatesData(const CharString DirectoryPath,
			register const StateInfo& ElectionState,
			register bool PrintVote,
			register Vector<VoteContainer>& Vote)
			throw(FatalException, IOException)
	{
	register	std_uint	Index;
	register	bool		EmptyKey;
			byte		Buffer [CANDIDATE_RECORD_LENGTH];
			byte		Zero [CANDIDATE_RECORD_LENGTH];
			byte		GuarantorsKey [KEY_LENGTH];
			char		OutputBuffer
						[2 * CANDIDATE_RECORD_LENGTH];
			CharString	PathName;
			File		CandidateFile;

	if (printf(CANDIDATES_HEADER_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(CANDIDATE_NUMBER_HEADER),
		CANDIDATE_NUMBER_LENGTH, 0);
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(KEY_HEADER),
		2 * KEY_LENGTH, Index);
	if (PrintVote)
		{
		ComputeKey(DirectoryPath, ElectionState.Guarantors,
			GuarantorsKey);
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		Index = PrintCenteredHeader(CharString(MIXED_KEY_HEADER),
			2 * KEY_LENGTH, Index);
		}
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(SIGNATURE_HEADER),
		2 * SIGNATURE_LENGTH, Index);
	if (PrintVote)
		{
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		Index = PrintCenteredHeader(CharString(VOTE_HEADER),
			2 * VOTE_LENGTH, Index);
		}
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	ignore_value(memset(Zero, 0, sizeof(Zero)));
	PathName = MakeCandidatesPathName(DirectoryPath);
	CandidateFile.OpenBinary(PathName, OPEN_READ);
	for (Index = 0; Index < ElectionState.Candidates; ++Index)
		{
		if (CandidateFile.Read(Buffer, CANDIDATE_RECORD_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		if (printf(UNSIGNED_NUMBER_FORMAT, CANDIDATE_NUMBER_LENGTH,
			Index) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		EmptyKey = memcmp(Buffer + CANDIDATE_KEY_OFFSET, Zero,
			CANDIDATE_KEY_LENGTH) == 0;
		if (EmptyKey)
			ignore_value(memset(OutputBuffer,
				CharacterManager<char>::GetMinusSign(),
				2 * KEY_LENGTH));
		else
			EncodeHex(Buffer, OutputBuffer, KEY_LENGTH);
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(STRING_FORMAT, 2 * KEY_LENGTH, OutputBuffer) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (PrintVote)
			{
			MixKeys(GuarantorsKey, Buffer);
			EncodeHex(Buffer, OutputBuffer, KEY_LENGTH);
			if (putchar(CharacterManager<char>::GetSpace()) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			if (printf(STRING_FORMAT, 2 * KEY_LENGTH,
				OutputBuffer) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			}
		if (memcmp(Buffer + CANDIDATE_SIGNATURE_OFFSET, Zero,
			SIGNATURE_LENGTH) == 0)
			ignore_value(memset(OutputBuffer,
				CharacterManager<char>::GetMinusSign(),
				2 * SIGNATURE_LENGTH));
		else
			EncodeHex(Buffer + CANDIDATE_SIGNATURE_OFFSET,
				OutputBuffer, SIGNATURE_LENGTH);
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(STRING_FORMAT, 2 * SIGNATURE_LENGTH, OutputBuffer) <
			0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (PrintVote)
			{
			EncodeHex(Buffer + CANDIDATE_VOTE_OFFSET, OutputBuffer,
				VOTE_LENGTH);
			if (putchar(CharacterManager<char>::GetSpace()) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			if (printf(STRING_FORMAT, 2 * VOTE_LENGTH,
				OutputBuffer) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			Vote.Append(VoteContainer(EmptyKey,
				Buffer + CANDIDATE_VOTE_OFFSET));
			}
		if (putchar(CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	CandidateFile.Close();
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write election result.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	ElectionState				Reference to the
//!							variable that contains
//!							the state of the
//!							election.
//! \param	Vote					Vector containing
//!							candidates' votes, in
//!							candidate index order.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If Vote does not contain
//!							at least Candidates
//!							elements.
//! \throw	io_space::FILE_WRITE_ERROR		If writing on stdout
//!							fails.
//!
//! \returns	None.
//!
//! \see	RESULT_HEADER_FORMAT
//! \see	CANDIDATE_NUMBER_HEADER
//! \see	CANDIDATE_NUMBER_LENGTH
//! \see	NUMBER_HEADER
//! \see	VOTE_HEADER
//! \see	UNSIGNED_NUMBER_FORMAT
//! \see	STRING_FORMAT
//! \see	VOTE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	PrintResult(const CharString DirectoryPath,
			register const StateInfo& ElectionState,
			register const Vector<VoteContainer>& Vote)
			throw(FatalException, IOException)
	{
	register	std_uint		Index;
	register	std_uint		Placement;
			char			OutputBuffer [2 * VOTE_LENGTH];
			CharString		PathName;
			Vector<std_uint>	IndexVector(ElectionState.
							Candidates);

	PathName = MakeCandidatesPathName(DirectoryPath);
	OrderedVector<VoteContainer>::SortIndices(Vote, IndexVector,
		VoteContainer::Compare);
	if (printf(RESULT_HEADER_FORMAT) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(PLACEMENT_HEADER),
		CANDIDATE_NUMBER_LENGTH, 0);
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(CANDIDATE_NUMBER_HEADER),
		CANDIDATE_NUMBER_LENGTH, Index);
	if (putchar(CharacterManager<char>::GetSpace()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Index = PrintCenteredHeader(CharString(VOTE_HEADER),
		2 * VOTE_LENGTH, Index);
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Placement = 0;
	for (Index = ElectionState.Candidates; Index > 0;)
		{
		--Index;
		if (ElectionState.MissingCandidates !=
			ElectionState.Candidates and
			Vote [IndexVector [Index]].EmptyKey)
			continue;
		if (printf(UNSIGNED_NUMBER_FORMAT, CANDIDATE_NUMBER_LENGTH,
			++Placement) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (printf(UNSIGNED_NUMBER_FORMAT, CANDIDATE_NUMBER_LENGTH,
			IndexVector [Index] + 1) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		EncodeHex(Vote [IndexVector [Index]].HashedVote, OutputBuffer,
			VOTE_LENGTH);
		if (printf(STRING_FORMAT, 2 * VOTE_LENGTH, OutputBuffer) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (putchar(CharacterManager<char>::GetEOLN()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		}
	if (putchar(CharacterManager<char>::GetEOLN()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for election state inspection.
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
//! \see	ELECTION_CREATED_FORMAT
//! \see	ELECTION_STARTED_MESSAGE
//! \see	ELECTION_CLOSED_MESSAGE
//! \see	ELECTION_TERMINATED_MESSAGE
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		CharString	DirectoryPath;
		StateInfo	ElectionState;

		HandleOptions(argc, argv);
		if (argc != 2)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		GetState(DirectoryPath, ElectionState);
		if (printf(ELECTION_CREATED_FORMAT, ElectionState.Candidates,
			ElectionState.Guarantors) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));

		Vector<VoteContainer>	Vote(ElectionState.Candidates);

		switch (ElectionState.State)
			{
			case ELECTION_CREATED:
				PrintGuarantorsData(DirectoryPath,
					ElectionState.Guarantors, false);
				PrintMissingGuarantorsHash(ElectionState.
					MissingGuarantors);
				break;
			case ELECTION_STARTED:
				if (printf(ELECTION_STARTED_MESSAGE) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				PrintGuarantorsData(DirectoryPath,
					ElectionState.Guarantors, false);
				PrintCandidatesData(DirectoryPath,
					ElectionState, false, Vote);
				PrintMissingCandidatesVotes(ElectionState.
					MissingCandidates);
				break;
			case ELECTION_CLOSED:
				PrintGuarantorsData(DirectoryPath,
					ElectionState.Guarantors, true);
				PrintCandidatesData(DirectoryPath,
					ElectionState, false, Vote);
				if (printf(ELECTION_CLOSED_MESSAGE,
					ElectionState.MissingGuarantors) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				PrintNotVotingCandidates(ElectionState.
					MissingCandidates);
				break;
			case ELECTION_TERMINATED:
				if (printf(ELECTION_TERMINATED_MESSAGE) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				PrintGuarantorsData(DirectoryPath,
					ElectionState.Guarantors, true);
				PrintCandidatesData(DirectoryPath,
					ElectionState, true, Vote);
				PrintNotVotingCandidates(ElectionState.
					MissingCandidates);
				PrintResult(DirectoryPath, ElectionState, Vote);
				break;
			}
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
