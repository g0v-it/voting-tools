////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	20/10/2018
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
//!	Pack an array of sizeof(std_uint) bytes into a std_uint.
//!
//! \param	Value		Array of bytes to be packed.
//!
//! \throw	None.
//!
//! \returns	std_uint	The packed value;
//!
//! \note
//!	Bytes are packed from lower to higher part of the result, that is, first
//!	byte is stored into the least significant part of the result.
//!
//! \see	BYTE_BITS
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	Pack(const byte Value [sizeof(std_uint)]) noexcept
	{
	register	std_uint	Index;
	register	std_uint	Result;

	Result = 0;
	for (Index = 0; Index < sizeof(std_uint); ++Index)
		Result |= *Value++ << (Index * BYTE_BITS);
	return Result;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Unpack a std_uint into an array of sizeof(std_uint) bytes.
//!
//! \param	Value	std_uint to be unpacked.
//! \param	Result	Array that upon return will contain the unpacked bytes.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	Bytes are unpacked from lower to higher part of Value, that is, the
//!	least significant part of Value is stored into first byte of Result.
//!
//! \see	BYTE_BITS
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Unpack(std_uint Value, byte Result [sizeof(std_uint)]) noexcept
	{
	register	std_uint	Index;

	for (Index = 0; Index < sizeof(std_uint); ++Index)
		*Result++ = static_cast<byte>(Value >> (Index * BYTE_BITS));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of the file containing election parameters.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file
//!						containing election parameters.
//!
////////////////////////////////////////////////////////////////////////////////

CharString	MakeParametersPathName(const CharString& DirectoryPath)
			throw(FatalException)
	{
	return MakePathName(DirectoryPath, CharString(ELECTION_FILE_NAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of the file containing voters' data.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file
//!						containing voters' data.
//!
////////////////////////////////////////////////////////////////////////////////

CharString	MakeVotersPathName(const CharString& DirectoryPath)
			throw(FatalException)
	{
	return MakePathName(DirectoryPath, CharString(VOTERS_FILE_NAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of the file containing the votes.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file
//!						containing the votes.
//!
////////////////////////////////////////////////////////////////////////////////

CharString	MakeVotesPathName(const CharString& DirectoryPath)
			throw(FatalException)
	{
	return MakePathName(DirectoryPath, CharString(VOTES_FILE_NAME));
	}

}


