////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	18/04/2018
//!
//! \par	Function:
//!	Contains the definitions of the common inline utility_space functions.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute a power of two.
//!
//! \param	Exponent			Exponent of the power.
//!
//! \throw	numeric_space::NUMERIC_OVERFLOW	If the power cannot be
//!						represented as a std_uint.
//!
//! \returns	std_uint			The power of two.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	PowerOfTwo(std_uint Exponent) throw(NumericException)
	{
	if (Exponent >= STD_UINT_BITS)
		throw make_numeric_exception(NUMERIC_OVERFLOW);
	return static_cast<std_uint>(0x01) << Exponent;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the number of bits needed to represent a std_uint, that is, the
//!	exponent of the minimum power of two greater than the argument. \n
//!	If the argument is 0, the function returns 0.
//!
//! \param	Value		The number.
//!
//! \throw	None.
//!
//! \returns	std_uint	The number of bits needed to represent Value.
//!
//! \see	STD_UINT_BITS
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	Size(std_uint Value) noexcept
	{
	std_uint	NumOfBits;

	if ((Value >> (STD_UINT_BITS / 2)) > 0)
		{
		Value >>= STD_UINT_BITS / 2;
		NumOfBits = STD_UINT_BITS / 2;
		}
	else
		NumOfBits = 0;
	if ((Value >> (STD_UINT_BITS / 4)) > 0)
		{
		Value >>= STD_UINT_BITS / 4;
		NumOfBits += STD_UINT_BITS / 4;
		}
	if ((Value >> (STD_UINT_BITS / 8)) > 0)
		{
		Value >>= STD_UINT_BITS / 8;
		NumOfBits += STD_UINT_BITS / 8;
		}
	if ((Value >> (STD_UINT_BITS / 16)) > 0)
		{
		Value >>= STD_UINT_BITS / 16;
		NumOfBits += STD_UINT_BITS / 16;
		}
	while (Value > 0)
		{
		Value >>= 1;
		++NumOfBits;
		}
	return NumOfBits;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Rotate a std_uint right.
//!
//! \param	Argument	The value to be rotated.
//! \param	Amount		The number of rotations.
//!
//! \throw	None.
//!
//! \returns	std_uint	The rotated value.
//!
////////////////////////////////////////////////////////////////////////////////

std_uint	RotateRight(std_uint Argument, std_uint Amount) noexcept
	{
	if ((Amount %= STD_UINT_BITS) == 0)
		return Argument;
	return (Argument >> Amount) | (Argument << (STD_UINT_BITS - Amount));
	}

}
