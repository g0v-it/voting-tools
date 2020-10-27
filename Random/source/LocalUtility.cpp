////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	18/04/2018
//!
//!	Contains the definitions of application specific non inline utility
//!	functions.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>

# include	"Standard.h"
# include	"Message.h"
# include	"CharacterManager.h"
# include	"File.h"
# include	"LocalUtility.h"

# if	!defined USE_INLINE
# include	"LocalUtility.inl"
# endif

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a number to a zero filled string in decimal format.
//!
//! \param	Value	Value to be converted.
//! \param	Buffer	Pointer to the buffer that upon return will contain the
//!			string.
//! \param	Length	Length of the string.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	If Buffer does not point to an array of at least Length char, the
//!	behaviour is undefined.
//!
//! \see	DECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

void	ConvertInteger(register std_uint Value, register byte* Buffer,
		register std_uint Length) noexcept
	{
	while (Length > 0)
		{
		Buffer [--Length] = CharacterManager<char>::NumberToChar(Value %
			DECIMAL_BASE);
		Value /= DECIMAL_BASE;
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message to show the number of guarantors that still
//!	have to communicate their hashed key.
//!
//! \param	MissingGuarantors		The number of guarantors that
//!						still have to communicate their
//!						hashed key.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	MISSING_GUARANTORS_HASH_FORMAT
//! \see	SINGLE_MISSING_GUARANTOR_HASH_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	PrintMissingGuarantorsHash(std_uint MissingGuarantors)
		throw(IOException)
	{
	if (printf(MissingGuarantors > 1? MISSING_GUARANTORS_HASH_FORMAT:
		SINGLE_MISSING_GUARANTOR_HASH_FORMAT, MissingGuarantors) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message to show the number of guarantors that still
//!	have to communicate their key.
//!
//! \param	MissingGuarantors		The number of guarantors that
//!						still have to communicate their
//!						key.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	MISSING_GUARANTORS_KEY_FORMAT
//! \see	SINGLE_MISSING_GUARANTOR_KEY_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	PrintMissingGuarantorsKey(std_uint MissingGuarantors) throw(IOException)
	{
	if (printf(MissingGuarantors > 1? MISSING_GUARANTORS_KEY_FORMAT:
		SINGLE_MISSING_GUARANTOR_KEY_FORMAT, MissingGuarantors) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message to show the number of candidates that still
//!	have to communicate their vote.
//!
//! \param	MissingCandidates		The number of candidates that
//!						still have to communicate their
//!						vote.
//!
//! \throw	io_space::STDOUT_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	MISSING_CANDIDATES_VOTE_FORMAT
//! \see	SINGLE_MISSING_CANDIDATE_VOTE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	PrintMissingCandidatesVotes(std_uint MissingCandidates)
		throw(IOException)
	{
	if (printf(MissingCandidates > 1? MISSING_CANDIDATES_VOTE_FORMAT:
		SINGLE_MISSING_CANDIDATE_VOTE_FORMAT, MissingCandidates) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message to show the number of candidates that did not
//!	vote.
//!
//! \param	MissingCandidates		The number of candidates that
//!						did not vote.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	NOT_VOTING_CANDIDATES_FORMAT
//! \see	SINGLE_NOT_VOTING_CANDIDATE_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	PrintNotVotingCandidates(std_uint MissingCandidates) throw(IOException)
	{
	if (printf(MissingCandidates > 1? NOT_VOTING_CANDIDATES_FORMAT:
		SINGLE_NOT_VOTING_CANDIDATE_FORMAT, MissingCandidates) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message to show the exclusive-ored guarantors' key.
//!
//! \param	Key				The key to be printed.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	KEY_LENGTH
//! \see	GUARANTORS_KEY_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

void	PrintGuarantorsKey(const byte Key [KEY_LENGTH]) throw(IOException)
	{
	char	Buffer [2 * KEY_LENGTH];

	EncodeHex(Key, Buffer, KEY_LENGTH);
	if (printf(GUARANTORS_KEY_FORMAT, 2 * KEY_LENGTH, Buffer) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

}
