////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	17/10/2018
//!
//! \par	Function:
//!	It contains the declaration of the utility_space::LinearGenerator class.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	LINEAR_GENERATOR_H

# define	LINEAR_GENERATOR_H

//! \def	DEFAULT_MULTIPLIER
//!	Default multiplier used by a linear congruent random number generator.
//!
//! \note
//!	It must be less than STD_UINT_MAX
# define	DEFAULT_MULTIPLIER		1900109

//! \def	DEFAULT_CONSTANT
//!	Default additive constant used by a linear congruent random number
//!	generator.
//!
//! \note
//!	It must be less than STD_UINT_MAX
# define	DEFAULT_CONSTANT		7079

//! \def	DEFAULT_MODULE
//!	Default module used by a linear congruent random number generator.
//!
//! \note
//!	It must be less than STD_UINT_MAX
# define	DEFAULT_MODULE			4293001441

# include	"FatalException.h"

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	LinearGenerator
//!	The LinearGenerator class represents a linear congruent random numbers
//!	generator, used to generate random numbers. \n
//!	Proper choice of the parameter ensures that the cycle of generated
//!	numbers is repeats itself after Module generation. \n
//!	See Erwin Donald Knuth, The art of Computer Programming, vol II.
//!
////////////////////////////////////////////////////////////////////////////////

class	LinearGenerator
	{
	private:

//! \property	Multiplier
//!	Multiplier.
		std_uint		Multiplier;

//! \property	Constant
//!	Additive constant.
		std_uint		Constant;

//! \property	Module
//!	Module.
		std_uint		Module;

//! \property	Value
//!	Latest generated value.
		std_uint		Value;

	public:

					LinearGenerator(void) noexcept;

					LinearGenerator(const LinearGenerator&
						Argument) noexcept = default;

					LinearGenerator(LinearGenerator&&
						Argument) noexcept = default;

		LinearGenerator&	operator = (const LinearGenerator&
					Argument) noexcept = default;

		LinearGenerator&	operator = (LinearGenerator&& Argument)
						noexcept = default;

					~LinearGenerator(void) noexcept =
						default;

		void			SetParameters(std_uint thisMultiplier,
						std_uint thisConstant,
						std_uint thisModule)
						throw(FatalException);

		void			SetSeed(std_uint Seed) noexcept;

		std_uint		Generate(std_uint Maximum)
						throw(FatalException);

	};

}

# if defined	USE_INLINE
# include	"LinearGenerator.inl"
# endif

# endif
