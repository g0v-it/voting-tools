////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/10/2018
//!
//! \par	Function:
//!	It contains the definitions of static attributes and non inline
//!	functions of the io_space::VotersFile class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"VotersFile.h"
# include	"Cryptography.h"
# include	"LocalUtility.h"
# include	"Vector.h"

# if !defined	USE_INLINE
# include	"VotersFile.inl"
# endif

namespace	io_space
{

using	namespace	utility_space;
using	namespace	application_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create a file containing for each voter the index of its data into the
//!	votes file.
//!
//! \param	thisPathName				Reference to the path
//!							name of the file.
//! \param	Voters					Number of voters.
//! \param	Key					Encryption key for the
//!							file.
//! \param	Generator				Reference to the random
//!							number generator used to
//!							sort voters and to
//!							generate random record
//!							fillers.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the file.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//! \see	MAXIMUM_BUFFER_SIZE
//! \see	MAXIMUM_RANDOM_NUMBER
//!
////////////////////////////////////////////////////////////////////////////////

void	VotersFile::Create(const CharString& thisPathName,
		register std_uint Voters,
		const byte Key [ENCRYPTION_KEY_LENGTH],
		register RandomGenerator& Generator)
		throw(FatalException, IOException)
	{
	register	std_uint		Index;
	register	std_uint		SwapIndex;
	register	std_uint		TempIndex;
			Cryptography		Encoder;
			Vector<std_uint>	IndexVector(Voters);
			byte			Buffer
						[ENCRYPTION_BLOCK_LENGTH];

	for (Index = 0; Index < Voters; ++Index)
		IndexVector.Append(Index);
	while (Index > 0)
		{
		SwapIndex = Generator.Generate(--Index);
		TempIndex = IndexVector [SwapIndex];
		IndexVector [SwapIndex] = IndexVector [Index];
		IndexVector [Index] = TempIndex;
		}
	Encoder.SetKey(Key);
	OpenBinary(thisPathName, OPEN_WRITE, MAXIMUM_BUFFER_SIZE);
	for (Index = 0; Index < Voters; ++Index)
		{
		Unpack(IndexVector [Index], Buffer);
		Unpack(Generator.Generate(MAXIMUM_RANDOM_NUMBER),
			Buffer + sizeof(std_uint));
		Encoder.Crypt(Buffer, Buffer);
		Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
		}
	Close();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read the index of all voters' data into the votes file.
//!
//! \param	thisPathName				Reference to the path
//!							name of the file.
//! \param	Voters					Number of voters
//! \param	VoterIndex				Reference to the array
//!							that upon return
//!							contains the indices of
//!							the voters.
//! \param	Key					Encryption key for the
//!							file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//! \throw	io_space::FILE_READ_ERROR		If the number of bytes
//!							read is less than
//!							expected.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the file.
//! \throw	application_space::INVALID_VOTERS_FILE_LENGTH	If the voters'
//!							file length is not
//!							correct.
//! \throw	application_space::CORRUPTED_VOTERS_FILE	If the voters'
//!							file contains invalid
//!							data.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	MAXIMUM_BUFFER_SIZE
//!
////////////////////////////////////////////////////////////////////////////////

void	VotersFile::Read(const CharString& thisPathName,
		register std_uint Voters, register Vector<std_uint>& VoterIndex,
		const byte Key [ENCRYPTION_KEY_LENGTH])
		throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Index;
	register	std_uint	Value;
			Cryptography	Encoder;
			byte		Buffer [ENCRYPTION_BLOCK_LENGTH];

	if (FileManager::GetInstance()->GetFileSize(thisPathName) !=
		Voters * ENCRYPTION_BLOCK_LENGTH)
		throw make_application_exception(INVALID_VOTERS_FILE_LENGTH);
	Encoder.SetKey(Key);
	VoterIndex.Clear();
	VoterIndex.Resize(Voters);
	OpenBinary(thisPathName, OPEN_READ, MAXIMUM_BUFFER_SIZE);
	for (Index = 0; Index < Voters; ++Index)
		{
		if (File::Read(Buffer, ENCRYPTION_BLOCK_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, thisPathName);
		Encoder.Decrypt(Buffer, Buffer);
		Value = Pack(Buffer);
		if (Value >= Voters)
			throw make_application_index_exception(
				CORRUPTED_VOTERS_FILE, Index);
		VoterIndex.Append(Value);
		}
	Close();
	}

}
