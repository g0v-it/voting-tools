////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	30/04/2018
//!
//! \par	Function:
//!	Contains the definition of the hash function.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdint.h>

# include	"Standard.h"
# include	"Utility.h"
# include	"Hash.h"

//! \def	SHA2_H_SIZE
//!	Number of elements of the array of constants h, used by the SHA2-256
//!	algorithm.
# define	SHA2_H_SIZE		8

//! \def	SHA2_K_SIZE
//!	Number of elements of an array the constants k, used by the SHA2-256
//!	algorithm.
# define	SHA2_K_SIZE		64

//! \def	SHA2_PADDING
//!	Byte used to pad the key, as prescribed by the SHA2-256 algorithm.
# define	SHA2_PADDING		(static_cast<uint32_t>(0x80))

namespace	application_space
{

using	namespace	utility_space;

//! \property	SHA2_h
//!	Array of constants used by the SHA2-256 algorithm.
//!
//! \note
//!	The constants are first 32 bits of the fractional part of the square
//!	roots of the first 8 primes, from 2 to 19: a simple choice without any
//!	rational reason. Well, they simply "look" random enough.
static	const	uint32_t	SHA2_h [SHA2_H_SIZE] =
	{
	0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
	0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
	};

//! \property	SHA2_k
//!	Array of constants used by the SHA2-256 algorithm.
//!
//! \note
//!	The constants are first 32 bits of the fractional part of the cube roots
//!	of the first 64 primes, from 2 to 311: a simple choice without any
//!	rational reason. Well, they simply "look" random enough.
static	const	uint32_t	SHA2_k [SHA2_K_SIZE] =
	{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
	};

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the hash function, using the SHA2-256 algorithm.
//!
//! \param	Key	Pointer to the key whose hash function must be computed.
//! \param	Hash	Pointer to the array that upon return will contain the
//!			value of the hash function.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	The code exploits the fact that additions of uint32_t are computed
//!	module 2^32.
//!
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	BYTE_BITS
//! \see	BYTE_MAX
//! \see	SHA2_H_SIZE
//! \see	SHA2_K_SIZE
//! \see	SHA2_PADDING
//!
////////////////////////////////////////////////////////////////////////////////

void	ComputeHash(register const byte Key [KEY_LENGTH],
		register byte Hash [HASH_LENGTH]) noexcept
	{
	register	std_uint	Index;
	register	std_uint	ByteIndex;
	register	uint32_t	Value_0;
	register	uint32_t	Value_1;
			uint32_t	Work [SHA2_K_SIZE];
			uint32_t	LocalHash [SHA2_H_SIZE];

	for (Index = 0; Index < KEY_LENGTH / sizeof(uint32_t);)
		{
		Value_0 = static_cast<uint32_t>(*Key++);
		for (ByteIndex = 1; ByteIndex < sizeof(uint32_t); ++ByteIndex)
			Value_0 = (Value_0 << BYTE_BITS) |
			static_cast<uint32_t>(*Key++);
		Work [Index++] = Value_0;
		}
	Work [Index++] = (((((Key [0] << BYTE_BITS) | Key [1]) << BYTE_BITS) |
		Key [2]) << BYTE_BITS) | SHA2_PADDING;
	Work [Index++] = 0;
	Work [Index++] = KEY_LENGTH * BYTE_BITS;
	for (; Index < SHA2_K_SIZE; ++Index)
		{
		Value_0 = Work [Index - 15];
		Value_1 = Work [Index - 2];
		Work [Index] = Work [Index - 16] + (RotateRight(Value_0, 7) ^
			RotateRight(Value_0, 18) ^ (Value_0 >> 3)) +
			Work [Index - 7] + (RotateRight(Value_1, 17) ^
			RotateRight(Value_1, 19) ^ (Value_1 >> 10));
		}
	ignore_value(memcpy(LocalHash, SHA2_h, sizeof(SHA2_h)));
	for (Index = 0; Index < SHA2_K_SIZE; ++Index)
		{
		Value_0 = (RotateRight(LocalHash [4], 6) ^
			RotateRight(LocalHash [4], 11) ^
			RotateRight(LocalHash [4], 25)) + LocalHash [7] +
			(LocalHash [6] ^ (LocalHash [4] & (LocalHash [6] ^
			LocalHash [5]))) + SHA2_k [Index] + Work [Index];
		Value_1 = (RotateRight(LocalHash [0], 2) ^
			RotateRight(LocalHash [0], 13) ^
			RotateRight(LocalHash [0], 22)) +
			((LocalHash [1] & LocalHash [2]) |
			(LocalHash [0] & (LocalHash [1] ^ LocalHash [2])));
		LocalHash [7] = LocalHash [6];
		LocalHash [6] = LocalHash [5];
		LocalHash [5] = LocalHash [4];
		LocalHash [4] = LocalHash [3] + Value_0;
		LocalHash [3] = LocalHash [2];
		LocalHash [2] = LocalHash [1];
		LocalHash [1] = LocalHash [0];
		LocalHash [0] = Value_0 + Value_1;
		}
	for (Index = 0; Index < HASH_LENGTH / sizeof(std_uint); ++Index)
		for (ByteIndex = 0; ByteIndex < sizeof(std_uint); ++ByteIndex)
			*Hash++ = static_cast<byte>(((LocalHash [Index] +
				SHA2_h [Index]) >> ((sizeof(std_uint) - 1 -
				ByteIndex) * BYTE_BITS)) % (BYTE_MAX + 1));
	}

}
