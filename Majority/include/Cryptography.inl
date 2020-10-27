////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	11/10/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	utility_space::Cryptography class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Fill the array of rotated keys and the Multiplier and Constant arrays.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	MULTIPLIER_OFFSET
//! \see	UCHAR_MAX
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Cryptography::MakeRotatedKey(void) noexcept
	{
	register	std_uint	Index;
	register	std_uint	Value;

	for (Index = 0; Index < number_of_elements(RotatedKey); ++Index)
		RotatedKey [Index] =
			RotateRight(Pack(&Key [Index * sizeof(std_uint) %
			number_of_elements(Key)]), Index);
	for (Index = 0; Index < number_of_elements(Multiplier); ++Index)
		{
		Value = RotateRight(Pack(&Key [Index + MULTIPLIER_OFFSET]),
			Index);
		Multiplier [Index] = Value / (UCHAR_MAX + 1);
		Constant [Index] = Value % (UCHAR_MAX + 1);
		assert(Multiplier [Index] < ModuleTable [Index]);
		assert(Constant [Index] < ModuleTable [Index]);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Diffuse a key and XOR it with source data.
//!
//! \param	Source		Key.
//! \param	Destination	Reference to source data, replaced with the
//!				diffused version.
//!
//! \throw	None.
//!
//! \returns	The diffused key, XOR_ed with source data.
//!
//! \see	BYTE_BITS
//! \see	BYTE_MAX
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	Cryptography::Diffuse(std_uint Source,
				std_uint Destination) noexcept
	{
	Destination ^= DiffuseTable [0] [Source % (BYTE_MAX + 1)];
	Destination ^= DiffuseTable [1] [(Source >> BYTE_BITS) %
		(BYTE_MAX + 1)];
	Destination ^= DiffuseTable [2] [(Source >> (2 * BYTE_BITS)) %
		(BYTE_MAX + 1)];
	Destination ^= DiffuseTable [3] [(Source >> (3 * BYTE_BITS)) %
		(BYTE_MAX + 1)];
	return Destination;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Execute a step of a Feistel function. \n
//!	Part of the data is xor-ed with the key, then bytes are substituted by
//!	different functions and the result scrambled, distributing bits of all
//!	parts among all resulting bytes.
//!
//! \param	ConstantSource	The part of source data that is not changed.
//! \param	ModifiedSource	Reference to the part of source data that is
//!				changed.
//! \param	LocalKey	Key used to xor the modified source data.
//! \param	FunctionArray	Array of pointers to functions implementing the
//!				S-box, one for each byte.
//!
//! \throw	None.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Cryptography::FeistelStep(std_uint ConstantSource,
			std_uint& ModifiedSource, std_uint LocalKey,
			const SBoxFunction FunctionArray [sizeof(std_uint)])
			noexcept
	{
	ConstantSource ^= LocalKey;
	ModifiedSource =
		Diffuse(FunctionArray [0] (static_cast<byte>(ConstantSource)) |
		(FunctionArray [1] (static_cast<byte>(ConstantSource >>
		CHAR_BIT)) << CHAR_BIT) |
		(FunctionArray [2] (static_cast<byte>(ConstantSource >>
		(2 * CHAR_BIT))) << (2 * CHAR_BIT)) |
		(FunctionArray [3] (static_cast<byte>(ConstantSource >>
		(3 * CHAR_BIT))) << (3 * CHAR_BIT)), ModifiedSource);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Execute a step of a Feistel function. \n
//!	Part of the data is used as seed of a linear congruent pseudo random
//!	number generator and the result is then scrambled, distributing bits of
//!	all parts among all resulting bytes.
//!
//! \param	ConstantSource	The part of source data that is not changed.
//! \param	ModifiedSource	Reference to the part of source data that is
//!				changed.
//! \param	Module		Module of the generator.
//! \param	Multiplier	Multiplier of the generator.
//! \param	Constant	Additive constant of the generator.
//! \param	FunctionArray	Array of pointers to functions implementing the
//!				S-box, one for each byte.
//!
//! \throw	None.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Cryptography::FeistelStep(std_uint ConstantSource,
			std_uint& ModifiedSource, std_uint Module,
			std_uint Multiplier, std_uint Constant,
			const SBoxFunction FunctionArray [sizeof(std_uint)])
			noexcept
	{
	ConstantSource =
		static_cast<std_uint>((static_cast<std_ulong>(ConstantSource) *
		static_cast<std_ulong>(Multiplier) + Constant) % Module);
	ModifiedSource =
		Diffuse(FunctionArray [0] (static_cast<byte>(ConstantSource)) |
		(FunctionArray [1] (static_cast<byte>(ConstantSource >>
		CHAR_BIT)) << CHAR_BIT) |
		(FunctionArray [2] (static_cast<byte>(ConstantSource >>
		(2 * CHAR_BIT))) << (2 * CHAR_BIT)) |
		(FunctionArray [3] (static_cast<byte>(ConstantSource >>
		(3 * CHAR_BIT))) << (3 * CHAR_BIT)), ModifiedSource);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor; initialize the device with a zero key.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	Cryptography::Cryptography(void) noexcept: Key(), RotatedKey(),
		Multiplier(), Constant()
	{
	ignore_value(memset(Key, DEFAULT_KEY, sizeof(Key)));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Set the encryption key.
//!
//! \param	thisKey	The encryption key.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Cryptography::SetKey(const byte thisKey [ENCRYPTION_KEY_LENGTH])
			noexcept
	{
	byte	LocalKey [ENCRYPTION_KEY_LENGTH];

	ignore_value(memcpy(Key, thisKey, sizeof(Key)));
	MakeRotatedKey();
	Crypt(Key, LocalKey);
	ignore_value(memcpy(Key, LocalKey, sizeof(Key)));
	MakeRotatedKey();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get current encryption key.
//!
//! \param	CurrentKey	Array that upon return will contain the key.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	Cryptography::GetKey(byte CurrentKey [ENCRYPTION_KEY_LENGTH])
			const noexcept
	{
	ignore_value(memcpy(CurrentKey, Key, sizeof(Key)));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the number of encrypted blocks that are necessary to store a
//!	given number of bytes.
//!
//! \param	Bytes		The number of bytes.
//!
//! \throw	None.
//!
//! \returns	std_uint	The number of encrypted blocks that are
//!				necessary to store the given number of bytes.
//!
//! \see	ENCRYPTION_BLOCK_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	Cryptography::ComputeBlocks(std_uint Bytes) noexcept
	{
	return (Bytes + ENCRYPTION_BLOCK_LENGTH - 1) / ENCRYPTION_BLOCK_LENGTH;
	}

}
