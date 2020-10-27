////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	27/04/2018
//!
//! \par	Function:
//!	Contains the declaration of data stuctures and function used to check
//!	the state of an election.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined STATE_H
# define	STATE_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"GenericString.h"

namespace	application_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

////////////////////////////////////////////////////////////////////////////////
//! \enum	ElectionStateType
//!	Enumerated type for election state.
//!
////////////////////////////////////////////////////////////////////////////////

enum	ElectionStateType
	{
		//! Election created; not all guarantors' hashed keys have been
		//! communicated. \n
		//! The only possible action is to communicate guarantors'
		//! hashed keys.
	ELECTION_CREATED,

		//! Election started; all guarantors' hashed keys have been
		//! communicated. \n
		//! It is possible for candidates to vote or to close the
		//! election, communicating a guarantor's key.
	ELECTION_STARTED,

		//! Election closed; not all guarantors' keys have been
		//! communicated. \n
		//! The only possible action is to communicate guarantors' keys.
	ELECTION_CLOSED,

		//! Election terminated; all guarantors' keys have been
		//! communicated. \n
		//! No further action is possible.
	ELECTION_TERMINATED
	};

////////////////////////////////////////////////////////////////////////////////
//! \class	StateInfo
//!	The StateInfo struct contains all informationa about the state of an
//!	election.
//!
////////////////////////////////////////////////////////////////////////////////

struct	StateInfo
	{
//! property	State,
//!	State of the election of guarantors.
	ElectionStateType	State;

//! property	Guarantors,
//!	Number of guarantors.
	std_uint		Guarantors;

//! property	MissingGuarantors,
//!	Number of guarantors that have not yet completed their job.
	std_uint		MissingGuarantors;

//! property	Candidates,
//!	Number of candidates.
	std_uint		Candidates;

//! property	MissingCandidates,
//!	Number of candidates that have not yet completed their job.
	std_uint		MissingCandidates;
	};

void	GetState(const CharString DirectoryPath, StateInfo& CurrentState)
		throw(FatalException, IOException, ApplicationException);

}

# endif
