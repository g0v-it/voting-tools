////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	26/10/2018
//!
//! \par	Function:
//!	It contains the definitions of static attributes and non inline
//!	functions of the io_space::VotesFile class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"VotesFile.h"

# if !defined	USE_INLINE
# include	"VotesFile.inl"
# endif

namespace	io_space
{

using	namespace	utility_space;
using	namespace	application_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write the votes and the signature of a voter.
//!
//! \param	CurrentVote			Reference to struct containing
//!						the data of the vote.
//! \param	FillerGenerator			Reference to the random number
//!						generator used to create random
//!						record fillers.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//! \throw	io_space::FILE_SEEK_ERROR	If the File cannot be seeked.
//! \throw	io_space::FILE_WRITE_ERROR	If an error occurs while
//!						writing.
//!
//! \returns	None.
//!
//! \see	SIGNATURE_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::WriteSingleVote(register const VoteData& CurrentVote,
		register RandomGenerator& FillerGenerator)
		throw(FatalException, IOException)
	{
	register	std_uint	Index;
			byte		Buffer [ENCRYPTION_BLOCK_LENGTH];

	Seek(CurrentVote.Voter * RecordLength, FILE_SEEK_SET);
	for (Index = 0; Index < CurrentVote.Vote.GetPresent(); Index)
		{
		Buffer [Index % ENCRYPTION_BLOCK_LENGTH] =
			MakeVote(CurrentVote.Vote [Index], FillerGenerator);
		if (++Index % ENCRYPTION_BLOCK_LENGTH == 0)
			{
			Encoder.Crypt(Buffer, Buffer);
			File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
			}
		}
	if ((Index %= ENCRYPTION_BLOCK_LENGTH) != 0)
		{
		while (Index != ENCRYPTION_BLOCK_LENGTH)
			Buffer [Index++] = MakeVote(0, FillerGenerator);
		Encoder.Crypt(Buffer, Buffer);
		File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
		}
	for (Index = 0; Index < 2 * SIGNATURE_LENGTH;)
		{
		Buffer [Index++ % ENCRYPTION_BLOCK_LENGTH] =
			CurrentVote.Signature [Index];
		Buffer [Index++ % ENCRYPTION_BLOCK_LENGTH] =
			FillerGenerator.Generate(BYTE_MAX);
		if (Index % ENCRYPTION_BLOCK_LENGTH == 0)
			{
			Encoder.Crypt(Buffer, Buffer);
			File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
			}
		}
	if ((Index %= ENCRYPTION_BLOCK_LENGTH) != 0)
		{
		while (Index != ENCRYPTION_BLOCK_LENGTH)
			Buffer [Index++] = FillerGenerator.Generate(BYTE_MAX);
		Encoder.Crypt(Buffer, Buffer);
		File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create a file containing for the votes.
//!
//! \param	thisPathName				Reference to the path
//!							name of the file.
//! \param	thisCandidates				Number of candidates.
//! \param	Voters					Number of voters.
//! \param	Key					Encryption key for the
//!							file.
//! \param	Generator				Reference to the random
//!							number generator used to
//!							create random record
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
//! \see	SIGNATURE_LENGTH
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::Create(const CharString& thisPathName,
		register std_uint thisCandidates, register std_uint Voters,
		const byte Key [ENCRYPTION_KEY_LENGTH],
		register RandomGenerator& Generator)
		throw(FatalException, IOException)
	{
	register	std_uint	Index;
	register	std_uint	BufferIndex;
			Cryptography	Encoder;
			byte		Buffer [ENCRYPTION_BLOCK_LENGTH];

	VotesBlocks = Cryptography::ComputeBlocks(Candidates = thisCandidates);
	Encoder.SetKey(Key);
	OpenBinary(thisPathName, OPEN_WRITE, MAXIMUM_BUFFER_SIZE);
	for (; Voters > 0; --Voters)
		{
		for (Index = 0; Index++ < VotesBlocks;)
			{
			for (BufferIndex = 0;
				BufferIndex < ENCRYPTION_BLOCK_LENGTH;)
				Buffer [BufferIndex++] = MakeVote(0, Generator);
			Encoder.Crypt(Buffer, Buffer);
			File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
			}
		for (Index = 0; Index++ < SignatureBlocks;)
			{
			for (BufferIndex = 0;
				BufferIndex < ENCRYPTION_BLOCK_LENGTH;)
				{
				Buffer [BufferIndex++] = 0;
				Buffer [BufferIndex++] =
					Generator.Generate(BYTE_MAX);
				}
			Encoder.Crypt(Buffer, Buffer);
			File::Write(Buffer, ENCRYPTION_BLOCK_LENGTH, 1);
			}
		}
	Close();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the votes file for reading and writing.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisCandidates				Number of candidates.
//! \param	thisVoters				Number of voters.
//! \param	thisMaximumVote				Maximum possible vote.
//! \param	Key					Encryption key for the
//!							file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
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
//! \throw	application_space::INVALID_VOTES_FILE_LENGTH	If the file
//!							length is not correct.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_BLOCK_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::Open(const CharString& thisPathName, std_uint thisCandidates,
		std_uint thisVoters, std_uint thisMaximumVote,
		const byte Key [ENCRYPTION_KEY_LENGTH])
		throw(FatalException, IOException, ApplicationException)
	{
	VotesBlocks = Cryptography::ComputeBlocks(Candidates = thisCandidates);
	RecordLength =
		ENCRYPTION_BLOCK_LENGTH * (VotesBlocks + SignatureBlocks);
	Voters = thisVoters;
	MaximumVote = thisMaximumVote;
	if (FileManager::GetInstance()->GetFileSize(thisPathName) !=
		Voters * RecordLength)
		throw make_application_exception(INVALID_VOTES_FILE_LENGTH);
	OpenBinary(thisPathName, OPEN_UPDATE, MAXIMUM_BUFFER_SIZE);
	Encoder.SetKey(Key);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read the votes of a voter.
//!
//! \param	Voter					The index of the voter.
//! \param	Vote					Reference to the Vector
//!							that upon return will
//!							contain the votes.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_NOT_OPEN			If the File is not
//!							opened.
//! \throw	io_space::FILE_SEEK_ERROR		If the File cannot be
//!							seeked.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading.
//! \throw	application_spec::CORRUPTED_VOTES_FILE	If the file contains
//!							votes greater than
//!							MaximumVote.
//!
//! \returns	None.
//!
//! \see	SIGNATURE_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//! \see	SIGNATURE_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::Read(std_uint Voter, register Vector<std_uint>& Vote)
		throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Index;
	register	std_uint	Value;
			byte		Buffer [ENCRYPTION_BLOCK_LENGTH];

	Seek(Voter * RecordLength, FILE_SEEK_SET);
	Vote.Clear();
	Vote.Resize(Candidates);
	for (Index = 0; Index < VotesBlocks * ENCRYPTION_BLOCK_LENGTH; ++Index)
		{
		if (Index % ENCRYPTION_BLOCK_LENGTH == 0)
			{
			if (File::Read(Buffer, ENCRYPTION_BLOCK_LENGTH, 1) < 1)
				throw make_IO_exception(FILE_READ_ERROR,
					GetPathName());
			Encoder.Decrypt(Buffer, Buffer);
			}
		Value = GetVote(Buffer [Index % ENCRYPTION_BLOCK_LENGTH]);
		if (Index < Candidates)
			{
			if (Value > MaximumVote)
				make_application_exception(
					CORRUPTED_VOTES_FILE);
			Vote.Append(Value);
			}
		else
			if (Value != 0)
				make_application_exception(
					CORRUPTED_VOTES_FILE);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read the votes and the signature of a voter.
//!
//! \param	Voter					The index of the voter.
//! \param	CurrentVote				Reference to the struct
//!							that upon return will
//!							contain the votes and
//!							the signature.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_NOT_OPEN			If the File is not
//!							opened.
//! \throw	io_space::FILE_SEEK_ERROR		If the File cannot be
//!							seeked.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading.
//! \throw	application_spec::CORRUPTED_VOTES_FILE	If the file contains
//!							votes greater than
//!							MaximumVote.
//!
//! \returns	None.
//!
//! \see	SIGNATURE_LENGTH
//! \see	ENCRYPTION_BLOCK_LENGTH
//! \see	SIGNATURE_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::Read(std_uint Voter, register VoteData& CurrentVote)
		throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Index;
			byte		Buffer [ENCRYPTION_BLOCK_LENGTH];

	Read(Voter, CurrentVote.Vote);
	CurrentVote.Voter = Voter;
	for (Index = 0; Index < 2 * SIGNATURE_LENGTH; Index += 2)
		{
		if (Index % ENCRYPTION_BLOCK_LENGTH == 0)
			{
			if (File::Read(Buffer, ENCRYPTION_BLOCK_LENGTH, 1) < 1)
				throw make_IO_exception(FILE_READ_ERROR,
					GetPathName());
			Encoder.Decrypt(Buffer, Buffer);
			}
		CurrentVote.Signature [Index / 2] =
			Buffer [Index % ENCRYPTION_BLOCK_LENGTH];
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write a vote and modify the fillers of some other votes.
//!
//! \param	CurrentVote				Reference to the struct
//!							containing the data of
//!							the vote to be written.
//! \param	VotersKey				Array that contains the
//!							encryption key of the
//!							voters' file.
//! \param	VotesKey				Array that contains the
//!							encryption key of the
//!							votes file.
//! \param	FillerGenerator				Reference to the random
//!							number generator used to
//!							create random record
//!							fillers.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_NOT_OPEN			If the VotesFile is not
//!							opened.
//! \throw	io_space::FILE_SEEK_ERROR		If the votes file cannot
//!							be seeked.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading.
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing.
//! \throw	application_spec::CORRUPTED_VOTES_FILE	If the file contains
//!							votes greater than
//!							MaximumVote.
//!
//! \returns	None.
//!
//! \note
//!	The file is locked during the operation, to ensure the integrity of the
//!	data.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//! \see	RANDOM_VOTES
//! \see	STD_UINT_MAX
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::WriteVote(const VoteData& CurrentVote,
		const byte VotersKey [ENCRYPTION_KEY_LENGTH],
		const byte VotesKey [ENCRYPTION_KEY_LENGTH],
		register RandomGenerator& FillerGenerator)
		throw(FatalException, IOException, ApplicationException)
	{
	register	std_uint	Index;
	register	std_uint	VoterIndex;
	register	std_uint	LatestIndex;

	RandomIndex.Append(CurrentVote.Voter);
	InitializeGenerator(IndexGenerator, VotersKey, VotesKey,
		CurrentVote.Voter);
	for (Index = RANDOM_VOTES + IndexGenerator.Generate(RANDOM_VOTES / 2);
		Index > 0; --Index)
		RandomIndex.Append(IndexGenerator.Generate(Voters - 1));
	OrderedIndex = RandomIndex;
	LatestIndex = STD_UINT_MAX;
	for (Index = 0; Index < OrderedIndex.GetPresent(); ++Index)
		{
		if ((VoterIndex = OrderedIndex [Index]) != LatestIndex)
			{
			if (VoterIndex == CurrentVote.Voter)
				{
				Seek(OrderedIndex [Index] * RecordLength,
					FILE_SEEK_SET);
				Lock(RecordLength);
				WriteSingleVote(CurrentVote, FillerGenerator);
				Seek(OrderedIndex [Index] * RecordLength,
					FILE_SEEK_SET);
				Unlock(RecordLength);
				}
			else
				Modify(OrderedIndex [Index], FillerGenerator);
			LatestIndex = VoterIndex;
			}
		SystemFlush();
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Modify the fillers of a voter.
//!
//! \param	Voter					Index of the voter.
//! \param	FillerGenerator				Reference to the random
//!							number generator used to
//!							create random record
//!							fillers.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_NOT_OPEN			If the VotesFile is not
//!							opened.
//! \throw	io_space::FILE_SEEK_ERROR		If the votes file cannot
//!							be seeked.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading.
//! \throw	io_space::FILE_WRITE_ERROR		If an error occurs while
//!							writing.
//! \throw	application_spec::CORRUPTED_VOTES_FILE	If the file contains
//!							votes greater than
//!							MaximumVote.
//!
//! \returns	None.
//!
//! \note
//!	The modified record is locked during the operation, to ensure the
//!	integrity of the data.
//!
////////////////////////////////////////////////////////////////////////////////

void	VotesFile::Modify(std_uint Voter, RandomGenerator& FillerGenerator)
		throw(FatalException, IOException, ApplicationException)
	{
	VoteData	CurrentVote;

	Seek(Voter * RecordLength, FILE_SEEK_SET);
	Lock(RecordLength);
	Read(Voter, CurrentVote);
	WriteSingleVote(CurrentVote, FillerGenerator);
	Seek(Voter * RecordLength, FILE_SEEK_SET);
	Unlock(RecordLength);
	}

}
