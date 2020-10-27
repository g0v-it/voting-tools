////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	16/10/2018
//!
//! \par	Function:
//!	It contains the declaration of the utility_space::RandomGenerator class.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	RANDOM_GENERATOR_H

# define	RANDOM_GENERATOR_H

# include	"LinearGenerator.h"

//! \def	LINEAR_GENERATORS
//!	Number of linear generators.
# define	LINEAR_GENERATORS		101

//! \def	MAXIMUM_RANDOM_NUMBER
//!	Maximum random number that can be generated.
# define	MAXIMUM_RANDOM_NUMBER		3000000000

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	RandomGenerator
//!	The RandomGenerator class represents a random numbers generator, used to
//!	generate random numbers. \n
//!	The cycle of generated numbers is repeats itself after more than
//!	MAXIMUM_RANDOM_NUMBER ^ LINEAR_GENERATORS numbers.
//!
////////////////////////////////////////////////////////////////////////////////

class	RandomGenerator
	{
	private:

////////////////////////////////////////////////////////////////////////////////
//! \class	GeneratorData
//!	The GeneratorData struct contains the data of a linear congruent random
//!	numbers generator.
//!
////////////////////////////////////////////////////////////////////////////////

	struct	GeneratorData
		{

//! \property	Multiplier
//!	Multiplier.
		std_uint	Multiplier;

//! \property	Constant
//!	Additive constant.
		std_uint	Constant;

//! \property	Module
//!	Module.
		std_uint	Module;

		};

//! \property	RandomSelector
//!	Simple linear congruent random numbers generator, used to select the
//!	generator to be used for actual number generation.
			LinearGenerator	RandomSelector;

//! \property	GeneratorArray
//!	Array of linear congruent random numbers generators.
//!
//! \see	LINEAR_GENERATORS
			LinearGenerator	GeneratorArray [LINEAR_GENERATORS];

//! \property	Data
//!	Parameters used to initialize the array of linear congruent random
//!	numbers generators.
//!
//! \see	LINEAR_GENERATORS
		static	const	GeneratorData	Data [LINEAR_GENERATORS];

	public:

					RandomGenerator(void) noexcept;

					RandomGenerator(const RandomGenerator&
						Argument) noexcept = default;

					RandomGenerator(RandomGenerator&&
						Argument) noexcept = default;

		RandomGenerator&	operator = (const
						RandomGenerator& Argument)
						noexcept = default;

		RandomGenerator&	operator = (RandomGenerator&&
						Argument) noexcept = default;

					~RandomGenerator(void) noexcept =
						default;

		void			SetSeeds(std_uint SelectorSeed,
						const std_uint Seed
						[LINEAR_GENERATORS]) noexcept;

		std_uint		Generate(std_uint Maximum)
						throw(FatalException);

	};

}

# if defined	USE_INLINE
# include	"RandomGenerator.inl"
# endif

# endif
