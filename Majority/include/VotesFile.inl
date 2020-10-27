////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	26/10/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	io_space::VotesFile class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

using	namespace	utility_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create a byte containg a vote and a random filler.
//!
//! \param	Vote		The vote.
//! \param	Generator	Reference to the random number generator used to
//!				generate random record fillers.
//!
//! \throw	None.
//!
//! \returns	byte		The random data filled vote.
//!
//! \see	MAXIMUM_VOTE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	byte	VotesFile::MakeVote(std_uint Vote, RandomGenerator& Generator)
			noexcept
	{
	return static_cast<byte>(Generator.Generate(BYTE_MAX /
		(MAXIMUM_VOTE + 1)) * (MAXIMUM_VOTE + 1) + Vote);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Extract the vote from a byte containing a vote and a random filler.
//!
//! \param	EncodedVote	The byte containing the vote and a random
//!				filler.
//!
//! \throw	None.
//!
//! \returns	std_uint	The actual vote.
//!
//! \see	MAXIMUM_VOTE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	VotesFile::GetVote(byte EncodedVote) noexcept
	{
	return EncodedVote % (MAXIMUM_VOTE + 1);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
//! \see	RANDOM_VOTES
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	VotesFile::VotesFile(void) throw(FatalException): File(), Candidates(0),
		Voters(0), MaximumVote(0), RecordLength(0), VotesBlocks(0),
		SignatureBlocks(Cryptography::ComputeBlocks(2 *
		SIGNATURE_LENGTH)), IndexGenerator(), Encoder(),
		RandomIndex(RANDOM_VOTES + 1)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor; if the file is still open, the function closes it and
//!	throws an exception.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_CLOSE_ERROR	If the File is open and an error
//!						occurs while closing it.
//! \throw	io_space::FILE_NOT_CLOSED	If the File is open.
//!
//! \returns	Not applicable.
//!
//! \note
//!	The exception could be thrown when the File is destroyed while
//!	processing another exception, thrown but not yet caught.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	VotesFile::~VotesFile(void) throw(FatalException, IOException)
	{
	}

}
