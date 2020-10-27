////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	16/10/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	utility_space::RandomGenerator class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Generate a new random number, between 0 and a given number, with uniform
//!	probability. \n
//!	First one of the generator is selected, using the RandomSelector
//!	generator, then the selected generator is used to actually generate a
//!	number.
//!
//! \param	Maximum				The maximum number that can be
//!						generated.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If Maximum is greater than
//!						MAXIMUM_RANDOM_NUMBER.
//!
//! \returns	Not applicable.
//!
//! \see	MAXIMUM_RANDOM_NUMBER
//! \see	LINEAR_GENERATORS
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	RandomGenerator::Generate(std_uint Maximum)
				throw(FatalException)
	{
	if (Maximum > MAXIMUM_RANDOM_NUMBER)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);
	return GeneratorArray [RandomSelector.Generate(LINEAR_GENERATORS - 1)].
		Generate(Maximum);
	}

}
