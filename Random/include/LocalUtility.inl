////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	18/04/2018
//!
//! \par	Function:
//!	Contains the definitions of the application specific inline
//!	utility_space functions.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the exclusive or of two keys.
//!
//! \param	SourceKey	First key, unchanged.
//! \param	TargetKey	Second keythat upon return will contain the
//!				exclusive or of te two keys.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	If the two keys overlap in any way, the value stored in TargetKey is
//!	unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	MixKeys(register const byte SourceKey [KEY_LENGTH],
			register byte TargetKey [KEY_LENGTH]) noexcept
	{
	register	std_uint	ByteIndex;

	for (ByteIndex = 0; ByteIndex < KEY_LENGTH; ++ByteIndex)
		*TargetKey++ ^= *SourceKey++;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of the file containing candidates' data.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file
//!						containing candidates' data.
//!
//! \see	CANDIDATES_FILE_NAME
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CharString	MakeCandidatesPathName(const CharString& DirectoryPath)
				throw(FatalException)
	{
	return MakePathName(DirectoryPath, CharString(CANDIDATES_FILE_NAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of the file containing guarantors' data.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file
//!						containing guarantors' data.
//!
//! \see	GUARANTORS_FILE_NAME
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CharString	MakeGuarantorsPathName(const CharString& DirectoryPath)
				throw(FatalException)
	{
	return MakePathName(DirectoryPath, CharString(GUARANTORS_FILE_NAME));
	}

}
