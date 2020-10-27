////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	06/11/2018
//!
//! \par	Function:
//!	It contains the declaration of the utility_space::CandidateVote class.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	CANDIDATE_VOTE_H

# define	CANDIDATE_VOTE_H

# include	"FatalException.h"
# include	"Vector.h"

namespace	utility_space
{

using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	CandidateVote
//!	The CandidateVote class contains the numbers of votes of a candidate.
//!
////////////////////////////////////////////////////////////////////////////////

class	CandidateVote
	{
	private:

//! \property	Count
//!	Vector containing the number of votes.
		Vector<std_uint>	Count;

//! \property	LowerExtreme
//!	The lower extreme of a fraction of the votes.
		std_uint		LowerExtreme;

	public:

				CandidateVote(void) throw(FatalException);

		explicit	CandidateVote(register std_uint MaximumVote)
					throw(FatalException);

				CandidateVote(const CandidateVote& Argument)
					throw(FatalException) = default;

				CandidateVote(CandidateVote&& Argument)
					throw(FatalException) = default;

		CandidateVote&	operator = (const CandidateVote& Argument)
					throw(FatalException) = default;

		CandidateVote&	operator = (CandidateVote&& Argument)
					throw(FatalException) = default;

				~CandidateVote(void) noexcept;

		bool		operator == (register const CandidateVote&
					Operand) const noexcept;

		bool		operator != (register const CandidateVote&
					Operand) const noexcept;

		bool		operator > (register const CandidateVote&
					Operand) const noexcept;

		bool		operator < (register const CandidateVote&
					Operand) const noexcept;

		std_uint	GetLowerExtreme(void) const noexcept;

		std_uint	GetCounter(std_uint Vote) const
					throw(FatalException);

		void		IncrementCount(std_uint Vote)
					throw(FatalException);

		void		ComputeLowerExtreme(register std_uint Votes)
					noexcept;

	};

}

# if defined	USE_INLINE
# include	"CandidateVote.inl"
# endif

# endif
