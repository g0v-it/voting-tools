////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	17/10/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	utility_space::LinearGenerator class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
//! \see	DEFAULT_MULTIPLIER
//! \see	DEFAULT_CONSTANT
//! \see	DEFAULT_MODULE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	LinearGenerator::LinearGenerator(void) noexcept:
		Multiplier(DEFAULT_MULTIPLIER), Constant(DEFAULT_CONSTANT),
		Module(DEFAULT_MODULE), Value(0)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Set the parameters of the linear congruent generator.
//!
//! \param	thisMultiplier			New value for the multiplier.
//! \param	thisConstant			New value for the additive
//!						constant.
//! \param	thisModule			New value for the module.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If thisMultiplier or thisModule
//!						are zero.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	LinearGenerator::SetParameters(std_uint thisMultiplier,
			std_uint thisConstant, std_uint thisModule)
			throw(FatalException)
	{
	if (Multiplier == 0 or Module == 0)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);
	Multiplier = thisMultiplier;
	Constant = thisConstant;
	Module = thisModule;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Set the seed of the linear congruent generator.
//!
//! \param	Seed	The new seed, used as the latest generated value.
//!
//! \throw	None.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	LinearGenerator::SetSeed(std_uint Seed) noexcept
	{
	Value = Seed;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Generate a new random number, between 0 and a given number, with uniform
//!	probability.
//!
//! \param	Maximum				The maximum number that can be
//!						generated.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If Maximum is not less than
//!						Module.
//!
//! \returns	std_uint			The generated number.
//!
//! \note
//!	A new value is computed as (Value * Multiplier + Constant) % Module and
//!	it is stored in Value. To ensure equal probability for all numbers, the
//!	process is repeated until Value <= Module - Module % Maximum, then
//!	Value % Maximum + 1 is returned.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	LinearGenerator::Generate(std_uint Maximum)
				throw(FatalException)
	{
	if (Maximum >= Module)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);
	if (Maximum == 0)
		return 0;
	for (;;)
		{
		Value = static_cast<std_uint>((static_cast<std_ulong>(
			Multiplier) * static_cast<std_ulong>(Value) +
			Constant) % Module);
		if (Value <= Module - Module % Maximum)
			return Value % (Maximum + 1);
		}
	}

}
