////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	27/04/2018
//!
//! \par	Function:
//!	Contains the definition of the function used to check the state of an
//!	election.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<string.h>

# include	"Standard.h"
# include	"Parameter.h"
# include	"FileManager.h"
# include	"File.h"
# include	"LocalUtility.h"
# include	"Hash.h"
# include	"State.h"

namespace	application_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the state of an election.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	CurrentState				Reference to the
//!							variable that upon
//!							return will contain the
//!							state of the election
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
//! \throw	application_space::INVALID_CANDIDATES_NUMBER
//!							If the number of
//!							candidates is not valid.
//! \throw	application_space::INVALID_GUARANTORS_NUMBER
//!							If the number of
//!							guarantors is not valid.
//! \throw	application_space::INVALID_CANDIDATES_FILE_LENGTH
//!							If the file containing
//!							candidates data has
//!							invalid length.
//! \throw	application_space::INVALID_GUARANTORS_FILE_LENGTH
//!							If the file containing
//!							guarantors data has
//!							invalid length.
//! \throw	application_space::CORRUPTED_CANDIDATES_FILE
//!							If the file containing
//!							candidates data is
//!							corrupted.
//! \throw	application_space::CORRUPTED_GUARANTORS_FILE
//!							If the file containing
//!							guarantors data is
//!							corrupted.
//! \throw	application_space::CANDIDATE_HASH_MISMATCH
//!							If the hash of the key
//!							of a candidate is not
//!							correct.
//! \throw	application_space::GUARANTOR_HASH_MISMATCH
//!							If the hash of the key
//!							of a guarantor is not
//!							correct.
//!
//! \returns	None.
//!
//! \see	MAXIMUM_RECORD_LENGTH
//! \see	CANDIDATE_RECORD_LENGTH
//! \see	GUARANTOR_RECORD_LENGTH
//! \see	GUARANTOR_HASH_OFFSET
//! \see	GUARANTOR_SIGNATURE_OFFSET
//! \see	CANDIDATE_KEY_OFFSET
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	CANDIDATE_NUMBER_LENGTH
//! \see	CANDIDATE_KEY_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	VOTE_LENGTH
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//! \see	CandidatesFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

void	GetState(const CharString DirectoryPath, StateInfo& CurrentState)
		throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Records;
	register	std_uint	Index;
	register	std_uint	MissingKeys;
	register	bool		ZeroKey;
	register	bool		ZeroHash;
	register	bool		ZeroSignature;
	register	bool		ZeroVote;
			std_uint	FirstKeyIndex;
			CharString	PathName;
			File		ElectionFile;
			byte		Buffer [MAXIMUM_RECORD_LENGTH];
			byte		Zero [MAXIMUM_RECORD_LENGTH];
			byte		Hash [HASH_LENGTH];
			byte		IndexBuffer [CANDIDATE_NUMBER_LENGTH];

	ignore_value(memset(Zero, 0, sizeof(Zero)));
	PathName = MakeGuarantorsPathName(DirectoryPath);
	Records = FileManager::GetInstance()->GetFileSize(PathName);
	if (Records % GUARANTOR_RECORD_LENGTH != 0)
		throw make_application_exception(
			INVALID_CANDIDATES_FILE_LENGTH);
	CurrentState.Guarantors = Records /= GUARANTOR_RECORD_LENGTH;
	CurrentState.MissingGuarantors = MissingKeys = 0;
	FirstKeyIndex = Records;
	if (Records < MINIMUM_GUARANTORS or Records > MAXIMUM_GUARANTORS)
		throw make_application_exception(INVALID_GUARANTORS_NUMBER);
	ElectionFile.OpenBinary(PathName, OPEN_READ);
	for (Index = 0; Index < Records; ++Index)
		{
		if (ElectionFile.Read(Buffer, GUARANTOR_RECORD_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		ZeroKey = memcmp(Buffer, Zero, KEY_LENGTH) == 0;
		ZeroHash = memcmp(Buffer + GUARANTOR_HASH_OFFSET, Zero,
			HASH_LENGTH) == 0;
		ZeroSignature = memcmp(Buffer + GUARANTOR_SIGNATURE_OFFSET,
			Zero, SIGNATURE_LENGTH) == 0;
		if (ZeroKey)
			++MissingKeys;
		else
			{
			if (ZeroHash)
				throw make_application_index_exception(
					CORRUPTED_GUARANTORS_FILE, Index);
			if (FirstKeyIndex != Records)
				FirstKeyIndex = Index;
			ComputeHash(Buffer, Hash);
			if (memcmp(Buffer + GUARANTOR_HASH_OFFSET, Hash,
				HASH_LENGTH) != 0)
				throw make_application_index_exception(
					GUARANTOR_HASH_MISMATCH, Index);
			}
		if (ZeroHash)
			{
			++CurrentState.MissingGuarantors;
			if (not (ZeroKey and ZeroSignature))
				throw make_application_index_exception(
					CORRUPTED_GUARANTORS_FILE, Index);
			}
		}
	ElectionFile.Seek(0, FILE_SEEK_SET);
	ElectionFile.Close();
	if (CurrentState.MissingGuarantors == 0)
		{
		CurrentState.State = ELECTION_STARTED;
		CurrentState.MissingGuarantors = MissingKeys;
		if (MissingKeys < CurrentState.Guarantors)
			CurrentState.State = MissingKeys == 0?
				ELECTION_TERMINATED: ELECTION_CLOSED;
		}
	else
		{
		CurrentState.State = ELECTION_CREATED;
		if (MissingKeys < CurrentState.Guarantors)
			throw make_application_index_exception(
				CORRUPTED_GUARANTORS_FILE, FirstKeyIndex);
		}
	PathName = MakeCandidatesPathName(DirectoryPath);
	Records = FileManager::GetInstance()->GetFileSize(PathName);
	if (Records % CANDIDATE_RECORD_LENGTH != 0)
		throw make_application_exception(
			INVALID_CANDIDATES_FILE_LENGTH);
	CurrentState.Candidates = Records /= CANDIDATE_RECORD_LENGTH;
	CurrentState.MissingCandidates = 0;
	if (Records < MINIMUM_CANDIDATES or Records > MAXIMUM_CANDIDATES)
		throw make_application_exception(INVALID_CANDIDATES_NUMBER);
	ElectionFile.OpenBinary(PathName, OPEN_READ);
	for (Index = 0; Index < Records; ++Index)
		{
		if (ElectionFile.Read(Buffer, CANDIDATE_RECORD_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		ConvertInteger(Index, IndexBuffer, CANDIDATE_NUMBER_LENGTH);
		if (memcmp(Buffer, IndexBuffer, CANDIDATE_NUMBER_LENGTH) != 0)
			throw make_application_index_exception(
				CORRUPTED_CANDIDATES_FILE, Index);
		ZeroKey = memcmp(Buffer + CANDIDATE_KEY_OFFSET, Zero,
			CANDIDATE_KEY_LENGTH) == 0;
		ZeroSignature = memcmp(Buffer + CANDIDATE_SIGNATURE_OFFSET,
			Zero, SIGNATURE_LENGTH) == 0;
		ZeroVote = memcmp(Buffer + CANDIDATE_VOTE_OFFSET, Zero,
			VOTE_LENGTH) == 0;
		if (CurrentState.State == ELECTION_CREATED and
			not (ZeroKey and ZeroSignature))
			throw make_application_index_exception(
				CORRUPTED_CANDIDATES_FILE, Index);
		if ((CurrentState.State != ELECTION_TERMINATED) != ZeroVote)
			throw make_application_index_exception(
				CORRUPTED_CANDIDATES_FILE, Index);
		if (ZeroKey)
			{
			++CurrentState.MissingCandidates;
			if (not ZeroSignature)
				throw make_application_index_exception(
					CORRUPTED_CANDIDATES_FILE, Index);
			}
		}
	ElectionFile.Seek(0, FILE_SEEK_SET);
	ElectionFile.Close();
	}

}
