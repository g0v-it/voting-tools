////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	10/10/2018
//!
//! \par	Function:
//!	Contains the definitions of the messages of majority judgement election
//!	handling programs.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	MESSAGE_H

# define	MESSAGE_H

# include	"CommonMessage.h"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	CreationMessage	Election creation program messages
//!	Definitions of messages used by the election creation program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	CREATE_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the election
//!	creation program.
# define	CREATE_USAGE_FORMAT \
	"Usage:\n" \
	"\tCreateMajority <election directory> <candidates> <voters> " \
	"<maximum vote> <keys file>\n\n" \
	"\t<candidates> must be in the range [%u .. %u]\n" \
	"\t<voters> must be in the range [%u .. %u]\n" \
	"\t<maximum vote> must be in the range [%u .. %u]\n"

//! \def	CREATE_FORMAT
//!	Message printed when the program terminates successfully.
# define	CREATE_FORMAT \
	"Election successfully created with %u candidates and %u " \
	"voters; maximum vote is %u.\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	VoteMessage	Election voting program messages
//!	Definitions of messages used by the election voting program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	VOTE_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the election
//!	voting program.
# define	VOTE_USAGE_FORMAT \
	"Usage:\n\tVoteMajority <election directory> <keys file>\n"

//! \def	VOTE_SET_FORMAT
//!	Format of the message printed when a voter's vote has has been set.
# define	VOTE_SET_FORMAT \
	"Vote of candidate %u set\n"

//! \def	ALL_CANDIDATES_VOTES_MESSAGE
//!	Message printed when all candidates's votes have has been communicated.
# define	ALL_CANDIDATES_VOTES_MESSAGE \
	"All candidates' votes have been communicated\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	NoiseMessage	Election state noise generation program messages
//!	Definitions of messages used by the noise generation program and related
//!	constants.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	NOISE_USAGE_FORMAT
//!	Message printed to explain the usage of the noise generation inspection
//!	program.
# define	NOISE_USAGE_FORMAT \
	"Usage:\n\tNoiseMajority <election directory> <keys file> " \
	"<iterations> [<interval>]\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	ResultMessage	Election result computation program messages
//!	Definitions of messages used by the election result computation program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	RESULT_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the election
//!	closing program.
# define	RESULT_USAGE_FORMAT \
	"Usage:\n" \
	"\tResultMajority <election directory> <keys file> [<interval>]\n\n"

//! \def	ELECTION_HEADER_FORMAT
//!	Message printed as header of the election results.
# define	ELECTION_HEADER_FORMAT \
	"Election with %u candidates and %u voters; maximum vote is %u.\n" \
	"\tResult on %s\n\n"

//! \def	ALL_VOTERS_MESSAGE
//!	Message printed when all voters did actually vote.
# define	ALL_VOTERS_MESSAGE	"\tall voters did vote\n\n"

//! \def	VOTERS_FORMAT
//!	Message printed when only a part of the voters did actually vote.
# define	VOTERS_FORMAT		"\t%d voters did actually vote\n\n"

//! \def	RESULT_HEADER
//!	Message printed as header of the classification.
# define	RESULT_HEADER		"Position Candidate Lower Median"

//! \def	VOTES_HEADER
//!	Message printed as header of the votes.
# define	VOTES_HEADER		"Votes"

//! \def	CANDIDATE_RESULT_FORMAT
//!	Format used to print first part of candidate's results.
# define	CANDIDATE_RESULT_FORMAT	"%7u   %7u       %2u       "

//! \def	VOTE_FIELD_LENGTH
//!	Length of the fields used to print the number of votes.
# define	VOTE_FIELD_LENGTH	7

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

# endif
