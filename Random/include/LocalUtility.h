////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	18/04/2018
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
# include	"NumericException.h"
# include	"GenericString.h"
# include	"Utility.h"

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;
using	namespace	data_structure_space;

void		MixKeys(register const byte SourceKey [KEY_LENGTH],
			register byte TargetKey [KEY_LENGTH]) noexcept;

void		ConvertInteger(register std_uint Value, register byte* Buffer,
			register std_uint Length) noexcept;

CharString	MakeCandidatesPathName(const CharString& DirectoryPath)
			throw(FatalException);

CharString	MakeGuarantorsPathName(const CharString& DirectoryPath)
			throw(FatalException);

void		PrintMissingGuarantorsHash(std_uint MissingGuarantors)
			throw(IOException);

void		PrintMissingGuarantorsKey(std_uint MissingGuarantors)
			throw(IOException);

void		PrintMissingCandidatesVotes(std_uint MissingCandidates)
			throw(IOException);

void		PrintNotVotingCandidates(std_uint MissingCandidates)
			throw(IOException);

void		PrintGuarantorsKey(const byte Key [KEY_LENGTH])
			throw(IOException);

}

# if	defined USE_INLINE
# include	"LocalUtility.inl"
# endif

# endif
