////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	09/05/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	closing program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>

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
# include	"Hash.h"
# include	"Key.h"
# include	"State.h"
# include	"LocalUtility.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;
using	namespace	application_space;

static	void	Usage(void) throw(IOException);

static	void	ComputeVotes(const CharString& DirectoryPath,
			const StateInfo& ElectionState)
			throw(FatalException, IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::STDOUT_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	CLOSE_USAGE_FORMAT
//! \see	NUMERIC_ERROR_OPTION
//! \see	KEY_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(CLOSE_USAGE_FORMAT, NUMERIC_ERROR_OPTION, KEY_LENGTH) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the actual votes.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	ElectionState				Reference to the
//!							variable that contains
//!							the state of the
//!							election.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If an election file does
//!							does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or to change the
//!							permissions or if the
//!							path name corresponds to
//!							a directory.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading an election data
//!							file.
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing the candidates
//!							file.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing an election data
//!							file.
//! \throw	io_space::FILE_SEEK_ERROR		If an election data file
//!							cannot be seeked.
//! \throw	io_space::STDOUT_WRITE_ERROR		If writing on stdout
//!							fails.
//!
//! \returns	None.
//!
//! \see	COMPUTING_VOTES_MESSAGE
//! \see	VOTES_COMPUTED_MESSAGE
//! \see	CANDIDATE_RECORD_LENGTH
//! \see	CANDIDATE_KEY_OFFSET
//! \see	CANDIDATE_KEY_LENGTH
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//! \see	CandidatesFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

static	void	ComputeVotes(const CharString& DirectoryPath,
			const StateInfo& ElectionState)
			throw(FatalException, IOException)
	{
	register	std_uint	Index;
			CharString	PathName;
			File		CandidateFile;
			byte		CandidateKey [KEY_LENGTH];
			byte		Zero [CANDIDATE_KEY_LENGTH];
			byte		Hash [HASH_LENGTH];
			byte		GuarantorsKey [KEY_LENGTH];

	if (printf(COMPUTING_VOTES_MESSAGE) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	FileManager::GetInstance()->
		SetReadOnly(MakeGuarantorsPathName(DirectoryPath));
	ComputeKey(DirectoryPath, ElectionState.Guarantors, GuarantorsKey);
	ignore_value(memset(Zero, 0, sizeof(Zero)));
	PathName = MakeCandidatesPathName(DirectoryPath);
	CandidateFile.OpenBinary(PathName, OPEN_UPDATE);
	CandidateFile.Lock(ElectionState.Candidates * CANDIDATE_RECORD_LENGTH);
	for (Index = 0; Index < ElectionState.Candidates; ++Index)
		{
		CandidateFile.Seek(Index * CANDIDATE_RECORD_LENGTH,
			FILE_SEEK_SET);
		if (CandidateFile.Read(CandidateKey, KEY_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		MixKeys(GuarantorsKey, CandidateKey);
		ComputeHash(CandidateKey, Hash);
		CandidateFile.Seek(Index * CANDIDATE_RECORD_LENGTH +
			CANDIDATE_VOTE_OFFSET, FILE_SEEK_SET);
		CandidateFile.Write(Hash, HASH_LENGTH, 1);
		}
	CandidateFile.Seek(0, FILE_SEEK_SET);
	CandidateFile.Unlock(ElectionState.Candidates *
		CANDIDATE_RECORD_LENGTH);
	CandidateFile.Close();
	FileManager::GetInstance()->SetReadOnly(PathName);
	PrintGuarantorsKey(GuarantorsKey);
	if (printf(VOTES_COMPUTED_MESSAGE) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for election voting.\n
//!	It stores the key of a guarantor, checking the its hash value.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	GUARANTOR_RECORD_LENGTH
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	GUARANTOR_KEY_SET_FORMAT
//! \see	ALL_GUARANTORS_KEYS_MESSAGE
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		std_uint	Guarantor;
		CharString	DirectoryPath;
		CharString	PathName;
		StateInfo	ElectionState;
		File		GuarantorFile;
		byte		Key [KEY_LENGTH];
		byte		LocalKey [KEY_LENGTH];
		byte		Hash [HASH_LENGTH];
		byte		LocalHash [HASH_LENGTH];
		byte		Zero [KEY_LENGTH];

		HandleOptions(argc, argv);
		if (argc != 4)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		GetState(DirectoryPath, ElectionState);
		Guarantor = DecodeInteger(argv [2]);
		if (Guarantor == 0 or Guarantor > ElectionState.Guarantors)
			throw make_application_exception(INVALID_GUARANTOR);
		DecodeHex(argv [3], LocalKey, KEY_LENGTH);
		ignore_value(memset(Zero, 0, sizeof(Zero)));
		if (memcmp(LocalKey, Zero, KEY_LENGTH) == 0)
			throw make_application_exception(INVALID_KEY);
		ComputeHash(LocalKey, LocalHash);
		if (ElectionState.State != ELECTION_STARTED and
			ElectionState.State != ELECTION_CLOSED)
			throw make_application_exception(INVALID_STATE);
		PathName = MakeGuarantorsPathName(DirectoryPath);
		GuarantorFile.OpenBinary(PathName, OPEN_UPDATE);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		GuarantorFile.Lock(GUARANTOR_RECORD_LENGTH);
		if (GuarantorFile.Read(Key, KEY_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		if (memcmp(Key, Zero, KEY_LENGTH) != 0)
			throw make_application_index_exception(
				GUARANTOR_KEY_ALREADY_SET, Guarantor - 1);
		if (GuarantorFile.Read(Hash, HASH_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		if (memcmp(Hash, LocalHash, HASH_LENGTH) != 0)
			throw make_application_index_exception(
				GUARANTOR_HASH_MISMATCH, Guarantor - 1);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		GuarantorFile.Write(LocalKey, KEY_LENGTH, 1);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		GuarantorFile.Unlock(GUARANTOR_RECORD_LENGTH);
		GuarantorFile.Close();
		if (printf(GUARANTOR_KEY_SET_FORMAT, Guarantor) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (--ElectionState.MissingGuarantors == 0)
			{
			if (printf(ALL_GUARANTORS_KEYS_MESSAGE) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			if (ElectionState.MissingCandidates == 0)
				{
				if (printf(ALL_CANDIDATES_VOTES_MESSAGE) < 0)
					throw make_IO_exception(
						FILE_WRITE_ERROR,
						CharString(
						DEFAULT_STDOUT_PATHNAME));
				}
			else
				PrintNotVotingCandidates(ElectionState.
					MissingCandidates);
			ComputeVotes(DirectoryPath, ElectionState);
			}
		else
			PrintMissingGuarantorsKey(ElectionState.
				MissingGuarantors);
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
