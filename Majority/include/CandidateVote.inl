////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	06/11/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	utility_space::CandidateVote class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CandidateVote::CandidateVote(void) throw(FatalException): Count(),
		LowerExtreme(0)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor; construct a CandidateVote with a given number of votes,
//!	that is, MaximumVote + 1.
//!
//! \param	MaximumVote			Maximum possible vote.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CandidateVote::CandidateVote(register std_uint MaximumVote)
		throw(FatalException): LowerExtreme(0)
	{
	Count.Resize(MaximumVote + 1);
	Count.Append(0);
	for (; MaximumVote > 0; --MaximumVote)
		Count.Append(0);
	Count.Trim();
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CandidateVote::~CandidateVote(void) noexcept
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if current CandidateVote object is equal to the given one.
//!
//! \param	Operand	Reference to the CandidateVote to compare.
//!
//! \throw	None.
//!
//! \returns	bool	True if the the object is equal, false otherwise.
//!
//! \note
//!	If the number of possible votes is not the same for both ojects, the
//!	behaviour is unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	CandidateVote::operator == (register const CandidateVote&
			Operand) const noexcept
	{
	register	std_uint	Index;

	assert(Count.GetPresent() == Operand.Count.GetPresent());
	for (Index = 0; Index < Count.GetPresent(); ++Index)
		if (Count [Index] != Operand.Count [Index])
			return false;
	return true;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if current CandidateVote object is diffrerent from the given one.
//!
//! \param	Operand	Reference to the CandidateVote to compare.
//!
//! \throw	None.
//!
//! \returns	bool	True if the the object is differente, false otherwise.
//!
//! \note
//!	If the number of possible votes is not the same for both ojects, the
//!	behaviour is unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	CandidateVote::operator != (register const CandidateVote&
			Operand) const noexcept
	{
	register	std_uint	Index;

	assert(Count.GetPresent() == Operand.Count.GetPresent());
	for (Index = 0; Index < Count.GetPresent(); ++Index)
		if (Count [Index] != Operand.Count [Index])
			return true;
	return false;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if current CandidateVote object is greater than the given one.
//!
//! \param	Operand	Reference to the CandidateVote to compare.
//!
//! \throw	None.
//!
//! \returns	bool	True if the the object is greater, false otherwise.
//!
//! \note
//!	If the number of possible votes is not the same for both ojects, the
//!	behaviour is unpredictable.
//!
//! \note
//!	If the median of both ojects has not been computed, the returned value
//!	is unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	CandidateVote::operator > (register const CandidateVote&
			Operand) const noexcept
	{
	register	std_uint	Index;

	assert(Count.GetPresent() == Operand.Count.GetPresent());
	if (LowerExtreme != Operand.LowerExtreme)
		return LowerExtreme > Operand.LowerExtreme;
	for (Index = LowerExtreme;; --Index)
		{
		if (Count [Index] != Operand.Count [Index])
			return Count [Index] > Operand.Count [Index];
		if (Index == 0)
			break;
		}
	for (Index = LowerExtreme + 1; Index < Count.GetPresent(); ++Index)
		{
		if (Count [Index] != Operand.Count [Index])
			return Count [Index] < Operand.Count [Index];
		}
	return false;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if current CandidateVote object is less than the given one.
//!
//! \param	Operand	Reference to the CandidateVote to compare.
//!
//! \throw	None.
//!
//! \returns	bool	True if the the object is less, false otherwise.
//!
//! \note
//!	If the number of possible votes is not the same for both ojects, the
//!	behaviour is unpredictable.
//!
//! \note
//!	If the median of both ojects has not been computed, the returned value
//!	is unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	CandidateVote::operator < (register const CandidateVote&
			Operand) const noexcept
	{
	register	std_uint	Index;

	assert(Count.GetPresent() == Operand.Count.GetPresent());
	if (LowerExtreme != Operand.LowerExtreme)
		return LowerExtreme < Operand.LowerExtreme;
	for (Index = LowerExtreme;; --Index)
		{
		if (Count [Index] != Operand.Count [Index])
			return Count [Index] < Operand.Count [Index];
		if (Index == 0)
			break;
		}
	for (Index = LowerExtreme + 1; Index < Count.GetPresent(); ++Index)
		{
		if (Count [Index] != Operand.Count [Index])
			return Count [Index] > Operand.Count [Index];
		}
	return false;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the latest computed lower extreme of a fraction f the votes.
//!
//! \throw	None.
//!
//! \returns	std_uint	The lower extreme.
//!
//! \note
//!	If the lower extreme was never computed, the function returns zero.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	CandidateVote::GetLowerExtreme(void) const noexcept
	{
	return LowerExtreme;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the counter of a vote.
//!
//! \param	Vote					The vote.
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If vote is greater than
//!							the maximum vote.
//!
//! \returns	std_uint				The counter of the vote.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	CandidateVote::GetCounter(std_uint Vote) const
				throw(FatalException)
	{
	return Count [Vote];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Increment the counter of a vote.
//!
//! \param	Vote					The vote.
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If vote is greater than
//!							the maximum vote.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	CandidateVote::IncrementCount(std_uint Vote)
			throw(FatalException)
	{
	++Count [Vote];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the lower extreme of a given fraction of the votes and store it
//!	into LowerExtreme.
//!
//! \param	Votes	The number of votes required to get the lower extreme.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	If the given number of votes cannot be reached, the function returns the
//!	number of different votes, that is, Vote.GetPresent() otherwise it
//!	returns the lowest index that satisfies the requirement.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	CandidateVote::ComputeLowerExtreme(register std_uint Votes)
			noexcept
	{
	register	std_uint	Index;
	register	std_uint	Sum;

	Sum = 0;
	for (Index = 0; Index < Count.GetPresent(); ++Index)
		if ((Sum += Count [Index]) >= Votes)
			break;
	LowerExtreme = Index;
	}

}
