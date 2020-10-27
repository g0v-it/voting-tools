////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	03/05/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	voting program.
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
# include	"File.h"
# include	"Utility.h"
# include	"Hash.h"
# include	"State.h"
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
//! \throw	io_space::STDOUT_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	VOTE_USAGE_FORMAT
//! \see	NUMERIC_ERROR_OPTION
//! \see	CANDIDATE_KEY_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(VOTE_USAGE_FORMAT, NUMERIC_ERROR_OPTION,
		CANDIDATE_KEY_LENGTH, SIGNATURE_LENGTH) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for election voting.\n
//!	It stores the key of a candidate, along with its optional signature.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	CANDIDATE_RECORD_LENGTH
//! \see	CANDIDATE_KEY_OFFSET
//! \see	CANDIDATE_KEY_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	CANDIDATE_VOTE_SET_FORMAT
//! \see	ALL_CANDIDATES_VOTES_MESSAGE
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	CandidatesFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		std_uint	Candidate;
		CharString	DirectoryPath;
		StateInfo	ElectionState;
		File		CandidateFile;
		byte		CandidateData [CANDIDATE_KEY_LENGTH +
					SIGNATURE_LENGTH];
		byte		Key [CANDIDATE_KEY_LENGTH];
		byte		Signature [SIGNATURE_LENGTH];
		byte		Zero [CANDIDATE_KEY_LENGTH + SIGNATURE_LENGTH];

		HandleOptions(argc, argv);
		if (argc < 4 || argc > 5)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		GetState(DirectoryPath, ElectionState);
		Candidate = DecodeInteger(argv [2]);
		if (Candidate == 0 or Candidate > ElectionState.Candidates)
			throw make_application_exception(INVALID_CANDIDATE);
		DecodeHex(argv [3], Key, CANDIDATE_KEY_LENGTH);
		if (argc == 5)
			DecodeHex(argv [4], Signature, SIGNATURE_LENGTH);
		ignore_value(memset(Zero, 0, sizeof(Zero)));
		if (memcmp(Key, Zero, CANDIDATE_KEY_LENGTH) == 0)
			throw make_application_exception(INVALID_KEY);
		if (ElectionState.State != ELECTION_STARTED)
			throw make_application_exception(INVALID_STATE);
		CandidateFile.OpenBinary(MakeCandidatesPathName(DirectoryPath),
			OPEN_UPDATE);
		CandidateFile.Seek((Candidate - 1) * CANDIDATE_RECORD_LENGTH +
			CANDIDATE_KEY_OFFSET, FILE_SEEK_SET);
		CandidateFile.Lock(CANDIDATE_KEY_LENGTH + SIGNATURE_LENGTH);
		CandidateFile.Read(CandidateData,
			CANDIDATE_KEY_LENGTH + SIGNATURE_LENGTH, 1);
		if (memcmp(CandidateData, Zero,
			CANDIDATE_KEY_LENGTH + SIGNATURE_LENGTH) != 0)
			throw make_application_index_exception(
				CANDIDATE_VOTE_ALREADY_SET, Candidate - 1);
		CandidateFile.Seek((Candidate - 1) * CANDIDATE_RECORD_LENGTH +
			CANDIDATE_KEY_OFFSET, FILE_SEEK_SET);
		CandidateFile.Write(Key, CANDIDATE_KEY_LENGTH, 1);
		if (argc == 6)
			CandidateFile.Write(Signature, SIGNATURE_LENGTH, 1);
		CandidateFile.Seek((Candidate - 1) * CANDIDATE_RECORD_LENGTH +
			CANDIDATE_KEY_OFFSET, FILE_SEEK_SET);
		CandidateFile.Unlock(CANDIDATE_KEY_LENGTH + SIGNATURE_LENGTH);
		CandidateFile.Close();
		if (printf(CANDIDATE_VOTE_SET_FORMAT, Candidate) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (--ElectionState.MissingCandidates == 0)
			{
			if (printf(ALL_CANDIDATES_VOTES_MESSAGE) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			}
		else
			PrintMissingCandidatesVotes(ElectionState.
				MissingCandidates);
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
