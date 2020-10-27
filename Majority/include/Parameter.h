////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	08/10/2018
//!
//! \par	Function:
//!	Contains the definitions of the parameters of majority judgement
//!	election handling programs.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	PARAMETER_H

# define	PARAMETER_H

//! \def	ENCRYPTION_KEY_LENGTH
//!	Length of the encryption keys in bytes.
//!
//! \note
//!	It must be an integer multiple of sizeof(std_uint) and at least equal to
//!	WORD_FEISTEL_STEPS + MULTIPLIER_OFFSET + sizeof(std_uint) - 1.
# define	ENCRYPTION_KEY_LENGTH		16

//! \def	SIGNATURE_LENGTH
//!	Length of signature in bytes.
# define	SIGNATURE_LENGTH		32

//! \def	ELECTION_FILE_NAME
//!	Name of the file containing the parameters of the election:
# define	ELECTION_FILE_NAME		"Election"

//! \def	VOTERS_FILE_NAME
//!	Name of the file containing for each voter the index of its data into
//!	the votes file.
# define	VOTERS_FILE_NAME		"Voters"

//! \def	VOTES_FILE_NAME
//!	Name of the file containing the votes.
# define	VOTES_FILE_NAME			"Votes"

//! \def	MINIMUM_CANDIDATES
//!	Minimum number of candidates.
# define	MINIMUM_CANDIDATES		2

//! \def	MAXIMUM_CANDIDATES
//!	Maximum number of candidates.
# define	MAXIMUM_CANDIDATES		999999

//! \def	MINIMUM_VOTERS
//!	Minimum number of voters.
# define	MINIMUM_VOTERS			1

//! \def	MAXIMUM_VOTERS
//!	Maximum number of voters.
# define	MAXIMUM_VOTERS			9999999

//! \def	MINIMUM_VOTE
//!	Minimum possible value for the greatest vote.
# define	MINIMUM_VOTE			1

//! \def	MAXIMUM_VOTE
//!	Maximum possible value for the greatest vote.
# define	MAXIMUM_VOTE			15

//! \def	RANDOM_VOTES
//!	Minimum number of modified record when a vote is inserted.
//!
//! \note
//!	The number of votes actually modified is randomly chosen in the interval
//!	[RANDOM_VOTES .. RANDOM_VOTES * 3 / 2].
# define	RANDOM_VOTES			100

//! \def	MAXIMUM_NOISE_INTERVAL
//!	Maximum time interval for noise generation in seconds.
# define	MAXIMUM_NOISE_INTERVAL		3600

//! \def	MAXIMUM_RESULT_INTERVAL
//!	Maximum time interval for resut generation in minutes.
# define	MAXIMUM_RESULT_INTERVAL	1440

# endif
