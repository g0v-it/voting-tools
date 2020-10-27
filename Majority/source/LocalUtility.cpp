////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	20/10/2018
//!
//!	Contains the definitions of application specific non inline utility
//!	functions.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"NumericException.h"
# include	"FileManager.h"
# include	"File.h"
# include	"CharacterManager.h"
# include	"SystemManager.h"
# include	"Cryptography.h"
# include	"LocalUtility.h"

# if	!defined USE_INLINE
# include	"LocalUtility.inl"
# endif

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;
using	namespace	data_structure_space;
using	namespace	system_space;

static	void		ReadKey(register File& KeysFile,
				register byte Key [ENCRYPTION_KEY_LENGTH])
				throw(FatalException, IOException,
				ApplicationException);

static	std_uint	ReadNumber(register File& ParametersFile,
				std_uint RecordIndex) throw(FatalException,
				IOException, ApplicationException);

static	bool		ReadEncodedKey(File& ParametersFile,
				std_uint RecordIndex,
				const byte Key [ENCRYPTION_KEY_LENGTH])
				throw(FatalException, IOException,
				ApplicationException);

static	std_uint	MixKeys(register const byte VotersKey
				[ENCRYPTION_KEY_LENGTH], register const byte
				VotesKey [ENCRYPTION_KEY_LENGTH],
				register std_uint Seed [ENCRYPTION_KEY_LENGTH])
				noexcept;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read an encryption key from a file.
//!
//! \param	KeysFile				Reference to the file.
//! \param	Key					Array that upon return
//!							will contain the key.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the KeysFile is not
//!							opened in read or
//!							read-write or update
//!							mode.
//! \throw	io_space::FILE_READ_ERROR		If no character is read
//!							and end of file is not
//!							reached.
//! \throw	io_space::FILE_SEEK_ERROR		If the file cannot be
//!							seeked and latest
//!							operation on the same
//!							file was a write.
//! \throw	io_space::END_OF_FILE			If reading past last
//!							character of the file.
//!
//! \throw	application_space::INVALID_HEX_STRING	If the file does not
//!							contain a valid
//!							hexadecimal string.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	HEXADECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

static	void	ReadKey(register File& KeysFile,
			register byte Key [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Value;
	register	std_uint	Index;

	try
		{
		for (Index = 0; Index < ENCRYPTION_KEY_LENGTH; ++Index)
			{
			Value = CharacterManager<char>::
				CharToHexNumber(KeysFile.ReadCharacter<char>());
			*Key++ = Value * HEXADECIMAL_BASE +
				CharacterManager<char>::
				CharToHexNumber(KeysFile.ReadCharacter<char>());
			}
		}
	catch (FatalException Exc)
		{
		assert(Exc.GetExceptionKind() == ILLEGAL_CONVERSION);
		throw make_application_exception(INVALID_HEX_STRING);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read a number in decimal format from a file.
//!
//! \param	ParametersFile				Reference to the file.
//! \param	RecordIndex				Index of the record in
//!							the file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the KeyFile is not
//!							opened in read or
//!							read-write or update
//!							mode.
//! \throw	io_space::FILE_READ_ERROR		If no character is read
//!							and end of file is not
//!							reached.
//! \throw	io_space::FILE_SEEK_ERROR		If the file cannot be
//!							seeked and latest
//!							operation on the same
//!							file was a write.
//! \throw	io_space::END_OF_FILE			If reading past last
//!							character of the file.
//! \throw	application_space::CORRUPTED_PARAMETERS_FILE	If the line is
//!							empty or it contains
//!							characters that are not
//!							decimal digits or if the
//!							value cannot cannot be
//!							represented as a
//!							std_uint.
//!
//! \returns	std_uint				The number read.
//!
//! \note
//!	The function reads all characters that are valid decimal digits, up to
//!	first non digit character, that is read and pushed back into the file
//!	buffer.
//!
////////////////////////////////////////////////////////////////////////////////

static	std_uint	ReadNumber(register File& ParametersFile,
				std_uint RecordIndex) throw(FatalException,
				IOException, ApplicationException)
	{
	std_uint	Index;
	std_uint	Value;
	std_uint	Length;
	CharString	Line;

	ParametersFile.ReadLine<char>(Line);
	Length = Line.GetLength();
	Index = 0;
	try
		{
		Line.ToNumber(Value, Index, Length);
		}
	catch (FatalException Exc)
		{
		assert(Exc.GetExceptionKind() == ILLEGAL_CONVERSION);
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, RecordIndex);
		}
	catch (NumericException Exc)
		{
		assert(Exc.GetExceptionKind() == NUMERIC_OVERFLOW);
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, RecordIndex);
		}
	if (Index != Length)
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, RecordIndex);
	return Value;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read a key from a file, and check it. \n
//!	The key has been mixed with random bytes and encoded with itself.
//!
//! \param	ParametersFile				Reference to the file.
//! \param	RecordIndex				Index of the record in
//!							the file.
//! \param	Key					The expected key.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the KeyFile is not
//!							opened in read or
//!							read-write or update
//!							mode.
//! \throw	io_space::FILE_READ_ERROR		If no character is read
//!							and end of file is not
//!							reached.
//! \throw	io_space::FILE_SEEK_ERROR		If the file cannot be
//!							seeked and latest
//!							operation on the same
//!							file was a write.
//! \throw	io_space::END_OF_FILE			If reading past last
//!							character of the file.
//! \throw	application_space::CORRUPTED_PARAMETERS_FILE	If the line does
//!							not contains exactly 4 *
//!							ENCRYPTION_KEY_LENGTH
//!							hexadecimal digits or if
//!							it contains extra
//!							characters.
//!
//! \returns	bool					True, if the key is
//!							correct.
//!
//! \note
//!	The function reads a line from the file, expecting it to contain only
//!	the encoded key.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

static	bool	ReadEncodedKey(File& ParametersFile, std_uint RecordIndex,
			register const byte Key [ENCRYPTION_KEY_LENGTH])
			throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Index;
			byte		Buffer [2 * ENCRYPTION_KEY_LENGTH];
			CharString	Line;
			Cryptography	Encoder;

	ParametersFile.ReadLine<char>(Line);
	try
		{
		DecodeHex(Line.GetString(), Buffer, 2 * ENCRYPTION_KEY_LENGTH);
		}
	catch (ApplicationException Exc)
		{
		assert(Exc.GetExceptionKind() == INVALID_HEX_LENGTH or
			Exc.GetExceptionKind() == INVALID_HEX_STRING);
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, RecordIndex);
		}
printf("B1=");
for (Index = 0; Index < 16; ++Index)
	printf(" %02x", Buffer [Index * 2]);
printf("\n");
	Encoder.SetKey(Key);
	for (Index = 0; Index < 2 * ENCRYPTION_KEY_LENGTH /
		ENCRYPTION_BLOCK_LENGTH; ++Index)
		Encoder.Decrypt(Buffer + Index * ENCRYPTION_BLOCK_LENGTH,
			Buffer + Index * ENCRYPTION_BLOCK_LENGTH);
printf("B2=");
for (Index = 0; Index < 16; ++Index)
	printf(" %02x", Buffer [Index * 2]);
printf("\n");
printf("K=");
for (Index = 0; Index < 16; ++Index)
	printf(" %02x", Key [Index]);
printf("\n");
	for (Index = 0; Index < ENCRYPTION_KEY_LENGTH; ++Index)
		if (Key [Index] != Buffer [2 * Index])
			return false;
	return true;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Prepare the seeds for a random number generator, computing the exclusive
//!	or of two keys.
//!
//! \param	VotersKey	Array that contains the encryption key of the
//!				voters' file.
//! \param	VotesKey	Array that contains the encryption key of the
//!				votes file.
//! \param	Seed		Array that upon return contains the exclusive or
//!				of the keys, concatenated to itself as many time
//!				 as necessary
//!
//! \throw	None.
//!
//! \returns	std_uint	The exclusive or of all the elements of both
//!				keys.
//!
//! \note
//!	THe returned value is in the range [0 .. BYTE_MAX].
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	LINEAR_GENERATORS
//!
////////////////////////////////////////////////////////////////////////////////

static	std_uint	MixKeys(register const byte VotersKey
				[ENCRYPTION_KEY_LENGTH], register const byte
				VotesKey [ENCRYPTION_KEY_LENGTH],
				register std_uint Seed [ENCRYPTION_KEY_LENGTH])
				noexcept
	{
	register	std_uint	Index;
	register	std_uint	Result;

	Result = 0;
	for (Index = 0; Index < ENCRYPTION_KEY_LENGTH; ++Index)
		Result ^= Seed [Index] = *VotersKey++ ^ *VotesKey++;
	for (; Index < LINEAR_GENERATORS; ++Index)
		Seed [Index] = Seed [Index % ENCRYPTION_KEY_LENGTH];
	return Result;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read the parameters of an election from a file, checking the encryption
//!	keys.
//!
//! \param	DirectoryPath				Reference to the
//!							directory path name.
//! \param	Candidates				Reference to the
//!							variable that upon
//!							return will contain the
//!							number of candidates.
//! \param	Voters					Reference to the
//!							variable that upon
//!							return will contain the
//!							number of voters.
//! \param	MaximumVote				Reference to the
//!							variable that upon
//!							return will contain the
//!							maximum vote.
//! \param	VotersKey				Encryption key for the
//!							voters' file.
//! \param	VotesKey				Encryption key for the
//!							votes file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the parameters file
//!							does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							parameters file or if
//!							the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//! \throw	io_space::FILE_READ_ERROR		If the number of bytes
//!							read is less than
//!							expected and end of file
//!							is not reached.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the keys file.
//! \throw	io_space::END_OF_FILE			If reading past last
//!							character of the file.
//! \throw	application_space::CORRUPTED_PARAMETERS_FILE	If a line is
//!							empty or it contains
//!							characters that are not
//!							decimal digits or if a
//!							value is outside the
//!							valid range or if there
//!							are extra caracters in
//!							the file.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
//! \fileformat
//! \see	ParametersFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

void	ReadParameters(const CharString& DirectoryPath, std_uint& Candidates,
		std_uint& Voters, std_uint& MaximumVote,
		const byte VotersKey [ENCRYPTION_KEY_LENGTH],
		const byte VotesKey [ENCRYPTION_KEY_LENGTH])
		throw(FatalException, IOException, ApplicationException)
	{
	File	ParametersFile;

	ParametersFile.OpenText(MakeParametersPathName(DirectoryPath),
		OPEN_READ);
	Candidates = ReadNumber(ParametersFile, 0);
	if (Candidates < MINIMUM_CANDIDATES or Candidates > MAXIMUM_CANDIDATES)
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, 0);
	Voters = ReadNumber(ParametersFile, 1);
	if (Voters < MINIMUM_VOTERS or Voters > MAXIMUM_VOTERS)
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, 1);
	MaximumVote = ReadNumber(ParametersFile, 2);
	if (MaximumVote < MINIMUM_VOTE or MaximumVote > MAXIMUM_VOTE)
		throw make_application_index_exception(
			CORRUPTED_PARAMETERS_FILE, 2);
	if (not ReadEncodedKey(ParametersFile, 4, VotersKey))
		throw make_application_exception(INVALID_VOTERS_KEY);
	if (not ReadEncodedKey(ParametersFile, 4, VotesKey))
		throw make_application_exception(INVALID_VOTES_KEY);
	try
		{
		ignore_value(ParametersFile.ReadCharacter<char>());
		}
	catch (IOException Exc)
		{
		if (Exc.GetExceptionKind() == END_OF_FILE)
			{
			ParametersFile.Close();
			return;
			}
		throw;
		}
	throw make_application_index_exception(CORRUPTED_PARAMETERS_FILE, 3);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read the encryption keys from a file.
//!
//! \param	KeyPath					Path name of the file.
//! \param	VotersKey				Array that upon return
//!							will contain the
//!							encryption key of the
//!							voters' file.
//! \param	VotesKey				Array that upon return
//!							will contain the
//!							encryption key of the
//!							votes' file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the keys file does
//!							not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							keys file or if the path
//!							name corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//! \throw	io_space::FILE_READ_ERROR		If the number of bytes
//!							read is less than
//!							expected and end of file
//!							is not reached.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the keys file.
//! \throw	application_space::INVALID_KEY_FILE_FORMAT	If the format of
//!							the key file is not
//!							valid.
//! \throw	application_space::INVALID_HEX_STRING	If the file does not
//!							contain a valid
//!							hexadecimal string.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	ReadKeys(const CharString& KeyPath,
		byte VotersKey [ENCRYPTION_KEY_LENGTH],
		byte VotesKey [ENCRYPTION_KEY_LENGTH])
		throw(FatalException, IOException, ApplicationException)
	{
	File	KeysFile;

	if (FileManager::GetInstance()->GetFileSize(KeyPath) !=
		4 * ENCRYPTION_KEY_LENGTH + 2)
		throw make_application_exception(INVALID_KEY_FILE_FORMAT);
	KeysFile.OpenText(KeyPath, OPEN_READ);
	ReadKey(KeysFile, VotersKey);
	try
		{
		if (KeysFile.ReadCharacter<char>() !=
			CharacterManager<char>::GetSpace())
			throw make_application_exception(
				INVALID_KEY_FILE_FORMAT);
		}
	catch (IOException Exc)
		{
		if (Exc.GetExceptionKind() == END_OF_FILE)
			throw make_application_exception(
				INVALID_KEY_FILE_FORMAT);
		throw;
		}
	ReadKey(KeysFile, VotesKey);
	try
		{
		if (KeysFile.ReadCharacter<char>() !=
			CharacterManager<char>::GetEOLN())
			throw make_application_exception(
				INVALID_KEY_FILE_FORMAT);
		}
	catch (IOException Exc)
		{
		if (Exc.GetExceptionKind() == END_OF_FILE)
			throw make_application_exception(
				INVALID_KEY_FILE_FORMAT);
		throw;
		}
	KeysFile.Close();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Encode an encryption key in hexadecimal format. \n
//!	The key if first mixed with random bytes, then encoded using the key
//!	itself and the result is converted to hexadecimal notation.
//!
//! \param	Key		Array that contains the key.
//! \param	Buffer		Array that will contain the encoded key
//! \param	Generator	Reference to the random number generator used to
//!				generate random bytes.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	EncodeKey(register const byte Key [ENCRYPTION_KEY_LENGTH],
		char Buffer [4 * ENCRYPTION_KEY_LENGTH],
		register RandomGenerator& Generator) noexcept
	{
	register	std_uint	Index;
	register	byte*		p;
			byte		KeyBuffer [2 * ENCRYPTION_KEY_LENGTH];
			Cryptography	Encoder;

	Encoder.SetKey(Key);
	p = KeyBuffer;
	for (Index = 0; Index < ENCRYPTION_KEY_LENGTH; ++Index)
		{
		*p++ = Key [Index];
		*p++ = Generator.Generate(BYTE_MAX);
		}
	for (Index = 0; Index < 2 * ENCRYPTION_KEY_LENGTH /
		ENCRYPTION_BLOCK_LENGTH; ++Index)
		Encoder.Crypt(KeyBuffer + Index * ENCRYPTION_BLOCK_LENGTH,
			KeyBuffer + Index * ENCRYPTION_BLOCK_LENGTH);
	p = KeyBuffer;
	EncodeHex(KeyBuffer, Buffer, 2 * ENCRYPTION_KEY_LENGTH);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Initialize a RandomGenerator
//!
//! \param	Generator	Reference to the RandomGenerator.
//! \param	VotersKey	Array that contains the encryption key of the
//!				voters' file.
//! \param	VotesKey	Array that contains the encryption key of the
//!				votes file.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	LINEAR_GENERATORS
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	InitializeGenerator(register RandomGenerator& Generator,
		register const byte VotersKey [ENCRYPTION_KEY_LENGTH],
		register const byte VotesKey [ENCRYPTION_KEY_LENGTH]) noexcept
	{
	register	std_uint	Index;
	register	std_uint	Seed;
	register	std_uint	Value;
			std_uint	SelectorSeed [LINEAR_GENERATORS];

	Seed = MixKeys(VotersKey, VotesKey, SelectorSeed);
	Seed ^= Value = static_cast<std_uint>(SystemManager::GetInstance()->
		GetApplicationTime() %
		(static_cast<std_ulong>(STD_UINT_MAX) + 1));
	for (Index = 1; Index < LINEAR_GENERATORS; Index += 2)
		SelectorSeed [Index] ^= Value;
	Seed ^= Value = static_cast<std_uint>(SystemManager::GetInstance()->
		GetApplicationCPUTime() %
		(static_cast<std_ulong>(STD_UINT_MAX) + 1));
	for (Index = 0; Index < LINEAR_GENERATORS; Index += 2)
		SelectorSeed [Index] ^= Value;
	Generator.SetSeeds(Seed, SelectorSeed);
	for (Index = LINEAR_GENERATORS * (Seed + BYTE_MAX); Index-- > 0;)
		ignore_value(Generator.Generate(BYTE_MAX));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Initialize a RandomGenerator
//!
//! \param	Generator	Reference to the RandomGenerator.
//! \param	VotersKey	Array that contains the encryption key of the
//!				voters' file.
//! \param	VotesKey	Array that contains the encryption key of the
//!				votes file.
//! \param	Voter		Index of a voter.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	The random generator is initialized using only the keys and the voter
//!	index, so that it generates the same sequence of numbers for each voter.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	LINEAR_GENERATORS
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	InitializeGenerator(register RandomGenerator& Generator,
		register const byte VotersKey [ENCRYPTION_KEY_LENGTH],
		register const byte VotesKey [ENCRYPTION_KEY_LENGTH],
		register std_uint Voter) noexcept
	{
	std_uint	Seed;
	std_uint	SelectorSeed [LINEAR_GENERATORS];

	Seed = MixKeys(VotersKey, VotesKey, SelectorSeed);
	Generator.SetSeeds(Seed ^ Voter, SelectorSeed);
	}

}
