////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	20/10/2018
//!
//! \par	Function:
//!	Contains the declaration of the application specific utility_space
//!	functions.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	LOCAL_UTILITY_H

# define	LOCAL_UTILITY_H

# include	"Parameter.h"
# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"GenericString.h"
# include	"RandomGenerator.h"
# include	"Utility.h"

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;
using	namespace	data_structure_space;

std_uint	Pack(const byte Value [sizeof(std_uint)]) noexcept;

void		Unpack(std_uint Value, byte Result [sizeof(std_uint)]) noexcept;

void		ReadParameters(const CharString& DirectoryPath,
			std_uint& Candidates, std_uint& Voters,
			std_uint& MaximumVote,
			const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			const byte VotesKey [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException,
			ApplicationException);

void		ReadKeys(const CharString& KeyPath,
			register byte VotersKey [ENCRYPTION_KEY_LENGTH],
			register byte VotesKey [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException,
			ApplicationException);

void		EncodeKey(register const byte Key [ENCRYPTION_KEY_LENGTH],
			char Buffer [4 * ENCRYPTION_KEY_LENGTH],
			register RandomGenerator& Generator) noexcept;

void		InitializeGenerator(register RandomGenerator& Generator,
			register const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			register const byte VotesKey [ENCRYPTION_KEY_LENGTH])
			noexcept;

void		InitializeGenerator(register RandomGenerator& Generator,
			register const byte VotersKey [ENCRYPTION_KEY_LENGTH],
			register const byte VotesKey [ENCRYPTION_KEY_LENGTH],
			register std_uint Voter) noexcept;

CharString	MakeParametersPathName(const CharString& DirectoryPath)
			throw(FatalException);

CharString	MakeVotersPathName(const CharString& DirectoryPath)
			throw(FatalException);

CharString	MakeVotesPathName(const CharString& DirectoryPath)
			throw(FatalException);

}

# if	defined USE_INLINE
# include	"LocalUtility.inl"
# endif

# endif
