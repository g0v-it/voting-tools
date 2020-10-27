////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	11/10/2018
//!
//! \par	Function:
//!	It contains the declaration of the utility_space::Cryptography class.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	CRYPTOGRAPHY_H

# define	CRYPTOGRAPHY_H

# include	"Parameter.h"
# include	"Utility.h"
# include	"LocalUtility.h"

# include	<string.h>

//! \def	DEFAULT_KEY
//!	Default value for all bytes of the encryption key.
# define	DEFAULT_KEY				0

//! \def	BYTE_FEISTEL_STEPS
//!	Number of Feistel steps acting on bytes.
# define	BYTE_FEISTEL_STEPS			8

//! \def	WORD_FEISTEL_STEPS
//!	Number of Feistel steps acting on std_uint.
# define	WORD_FEISTEL_STEPS			8

//! \def	MULTIPLIER_OFFSET
//!	Offset of the part of key used to compute the Multiplier and Constant
//!	arrays.
# define	MULTIPLIER_OFFSET			3

//! \def	ENCRYPTION_BLOCK_LENGTH
//!	Length of an encryption block in bytes.
//!
//! \note
//!	Cryptography encodes and decodes only blocks of ENCRYPTION_BLOCK_LENGTH
//!	bytes.
# define	ENCRYPTION_BLOCK_LENGTH			sizeof(std_ulong)

namespace	utility_space
{

static_assert(ENCRYPTION_KEY_LENGTH % sizeof(std_uint) == 0,
	"Wrong ENCRYPTION_KEY_LENGTH, non multiple of sizeof(std_uint)");

static_assert(ENCRYPTION_KEY_LENGTH >=
	WORD_FEISTEL_STEPS + MULTIPLIER_OFFSET + sizeof(std_uint),
	"Wrong ENCRYPTION_KEY_LENGTH, less than WORD_FEISTEL_STEPS + "
	"MULTIPLIER_OFFSET + sizeof(std_uint)");

////////////////////////////////////////////////////////////////////////////////
//! \class	Cryptography
//!	The Cryptography class represents a cryptographycal device, used to
//!	encrypt and decrypt data packets.
//!
//! \note
//!	Encryption and decryption consider a single std_ulong at a time; the
//!	result depends uniquely upon key and current value.
//!
////////////////////////////////////////////////////////////////////////////////

class	Cryptography
	{
	private:

//! \typedef	SBoxFunction
//!	Pointer to function used to implement a s-box.
		typedef		byte		(*SBoxFunction)(byte Value);

//! \property	Key
//!	Cryptographycal key.
//!
//! \see	ENCRYPTION_KEY_LENGTH
				byte		Key [ENCRYPTION_KEY_LENGTH];

//! \property	RotatedKey
//!	Cryptographycal keys used for each Feistel step. \n
//!	This key is derived from Key, but it is stored separately for efficiency
//!	sake.
//!
//! \see	ENCRYPTION_KEY_LENGTH
				std_uint	RotatedKey [BYTE_FEISTEL_STEPS];

//! \property	Multiplier
//!	Multipliers for the linear congruent pseudo random number generators.
//!	They are derived from Key, but they are pre-computed for efficiency
//!	sake.
//!
//! \see	WORD_FEISTEL_STEPS
				byte		Multiplier [WORD_FEISTEL_STEPS];

//! \property	Constant
//!	Additive constants for the linear congruent pseudo random number
//!	generators. They are derived from Key, but they are pre-computed for
//!	efficiency sake.
//!
//! \see	WORD_FEISTEL_STEPS
				byte		Constant [WORD_FEISTEL_STEPS];

//! \var	ModuleTable
//!	Modules table.
//!
//! \note
//!	All the numbers are primes, to have pseudo random number generators of
//!	maximum period length for any choice of remaining parameters.
//!
//! \see	WORD_FEISTEL_STEPS
		static	const	std_uint	ModuleTable
							[WORD_FEISTEL_STEPS];

//! \var	SubsTable
//!	Substitution table.
//!
//! \see	BYTE_MAX
//! \see	SBox_1
//! \see	SBox_3
//! \see	SBox_5
//! \see	SBox_7
		static	const	byte		SubsTable [BYTE_MAX + 1];

//! \var	DiffuseTable
//!	Bit diffusion table.
//!
//! \note
//!	The table consists of 4 arrays, one for each byte of a std_uint and it
//!	is computed as follows.
//!	For first array, corresponding to byte 0 of the source:
//!	- bit 3 is equal to bit 0 of the index, that is, bit 0 of the source
//!	- bit 8 is equal to bit 1 of the index, that is, bit 1 of the source
//!	- bit 17 is equal to bit 2 of the index, that is, bit 2 of the source
//!	- bit 24 is equal to bit 3 of the index, that is, bit 3 of the source
//!	- bit 7 is equal to bit 4 of the index, that is, bit 4 of the source
//!	- bit 14 is equal to bit 5 of the index, that is, bit 5 of the source
//!	- bit 21 is equal to bit 6 of the index, that is, bit 6 of the source
//!	- bit 28 is equal to bit 7 of the index, that is, bit 7 of the source
//!	.
//!	For second array, corresponding to byte 1 of the source:
//!	- bit 4 is equal to bit 0 of the index, that is, bit 8 of the source
//!	- bit 11 is equal to bit 1 of the index, that is, bit 9 of the source
//!	- bit 18 is equal to bit 2 of the index, that is, bit 10 of the source
//!	- bit 25 is equal to bit 3 of the index, that is, bit 11 of the source
//!	- bit 0 is equal to bit 4 of the index, that is, bit 12 of the source
//!	- bit 15 is equal to bit 5 of the index, that is, bit 13 of the source
//!	- bit 22 is equal to bit 6 of the index, that is, bit 14 of the source
//!	- bit 29 is equal to bit 7 of the index, that is, bit 15 of the source
//!	.
//!	For third array, corresponding to byte 2 of the source:
//!	- bit 5 is equal to bit 0 of the index, that is, bit 16 of the source
//!	- bit 12 is equal to bit 1 of the index, that is, bit 17 of the source
//!	- bit 19 is equal to bit 2 of the index, that is, bit 18 of the source
//!	- bit 26 is equal to bit 3 of the index, that is, bit 19 of the source
//!	- bit 1 is equal to bit 4 of the index, that is, bit 20 of the source
//!	- bit 8 is equal to bit 5 of the index, that is, bit 21 of the source
//!	- bit 23 is equal to bit 6 of the index, that is, bit 22 of the source
//!	- bit 30 is equal to bit 7 of the index, that is, bit 23 of the source
//!	.
//!	For fourth array, corresponding to byte 3 of the source:
//!	- bit 6 is equal to bit 0 of the index, that is, bit 24 of the source
//!	- bit 13 is equal to bit 1 of the index, that is, bit 25 of the source
//!	- bit 20 is equal to bit 2 of the index, that is, bit 26 of the source
//!	- bit 26 is equal to bit 3 of the index, that is, bit 27 of the source
//!	- bit 2 is equal to bit 4 of the index, that is, bit 28 of the source
//!	- bit 9 is equal to bit 5 of the index, that is, bit 29 of the source
//!	- bit 16 is equal to bit 6 of the index, that is, bit 30 of the source
//!	- bit 31 is equal to bit 7 of the index, that is, bit 31 of the source
//!	.
//!
//! \see	BYTE_MAX
		static	const	std_uint	DiffuseTable [sizeof(std_uint)]
							[BYTE_MAX + 1];

//! \var	SubsFunctionTable
//!	Table of pointers to substitution functions used in Feistel steps.
//!
//! \see	BYTE_FEISTEL_STEPS
		static	const	SBoxFunction	SubsFunctionTable
							[BYTE_FEISTEL_STEPS]
							[sizeof(std_uint)];

			void		MakeRotatedKey(void) noexcept;

		static	byte		SBox_0(byte Value) noexcept;

		static	byte		SBox_1(byte Value) noexcept;

		static	byte		SBox_2(byte Value) noexcept;

		static	byte		SBox_3(byte Value) noexcept;

		static	byte		SBox_4(byte Value) noexcept;

		static	byte		SBox_5(byte Value) noexcept;

		static	byte		SBox_6(byte Value) noexcept;

		static	byte		SBox_7(byte Value) noexcept;

		static	std_uint	Diffuse(std_uint Source,
						std_uint Destination) noexcept;

		static	void		FeistelStep(std_uint ConstantSource,
						std_uint& ModifiedSource,
						std_uint LocalKey,
						const SBoxFunction FunctionArray
						[sizeof(std_uint)]) noexcept;

		static	void		FeistelStep(std_uint ConstantSource,
						std_uint& ModifiedSource,
						std_uint Module,
						std_uint Multiplier,
						std_uint Constant,
						const SBoxFunction FunctionArray
						[sizeof(std_uint)]) noexcept;

	public:

					Cryptography(void) noexcept;


					Cryptography(const Cryptography&
						Argument) noexcept = default;

					Cryptography(Cryptography&& Argument)
						noexcept = default;

			Cryptography&	operator = (const Cryptography&
						Argument) noexcept = default;

			Cryptography&	operator = (Cryptography&& Argument)
						noexcept = default;

					~Cryptography(void) noexcept = default;

			void		SetKey(const byte thisKey
						[ENCRYPTION_KEY_LENGTH])
						noexcept;

			void		GetKey(byte CurrentKey
						[ENCRYPTION_KEY_LENGTH])
						const noexcept;

			void		Crypt(const byte Plain
						[ENCRYPTION_BLOCK_LENGTH],
						byte Encrypted
						[ENCRYPTION_BLOCK_LENGTH]) const
						noexcept;

			void		Decrypt(const byte Encrypted
						[ENCRYPTION_BLOCK_LENGTH],
						byte Plain
						[ENCRYPTION_BLOCK_LENGTH]) const
						noexcept;

		static	std_uint	ComputeBlocks(std_uint Bytes) noexcept;

	};

}

# if defined	USE_INLINE
# include	"Cryptography.inl"
# endif

# endif
