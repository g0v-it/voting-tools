////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	28/04/2018
//!
//! \par	Function:
//!	Contains the definitions of the messages of self-election handling
//!	programs.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	MESSAGE_H

# define	MESSAGE_H

# include	"CommonMessage.h"

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	MissingMessage	Messages indicating the number of missing items.
//!	Definitions of messages used to indicate the number of missing items.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	MISSING_GUARANTORS_HASH_FORMAT
//!	Format of the message printed to show the number of guarantors that
//!	still have to communicate their hashed key.
# define	MISSING_GUARANTORS_HASH_FORMAT \
	"\t%u guarantors still have to communicate their hashed key.\n\n"

//! \def	SINGLE_MISSING_GUARANTOR_HASH_FORMAT
//!	Format of the message printed to indicate that a single guarantor still
//!	has to communicate his hashed key.
# define	SINGLE_MISSING_GUARANTOR_HASH_FORMAT \
	"\t%u guarantor still has to communicate his hashed key.\n\n"

//! \def	MISSING_GUARANTORS_KEY_FORMAT
//!	Format of the message printed to show the number of guarantors that
//!	still have to communicate their key.
# define	MISSING_GUARANTORS_KEY_FORMAT \
	"\t%u guarantors still have to communicate their key.\n\n"

//! \def	SINGLE_MISSING_GUARANTOR_KEY_FORMAT
//!	Format of the message printed to indicate that a single guarantor still
//!	has to communicate his key.
# define	SINGLE_MISSING_GUARANTOR_KEY_FORMAT \
	"\t%u guarantor still has to communicate his key.\n\n"

//! \def	MISSING_CANDIDATES_VOTE_FORMAT
//!	Format of the message printed to show the number of candidates that
//!	still have to communicate their vote.
# define	MISSING_CANDIDATES_VOTE_FORMAT \
	"\t%u candidates still have to communicate their vote.\n\n"

//! \def	SINGLE_MISSING_CANDIDATE_VOTE_FORMAT
//!	Format of the message printed to indicate that a single candidate still
//!	has to communicate his vote.
# define	SINGLE_MISSING_CANDIDATE_VOTE_FORMAT \
	"\t%u candidate still has to communicate his vote.\n\n"

//! \def	NOT_VOTING_CANDIDATES_FORMAT
//!	Format of the message printed to show the number of candidates that did
//!	not vote.
# define	NOT_VOTING_CANDIDATES_FORMAT \
	"\t%u candidates did not vote.\n\n"

//! \def	SINGLE_NOT_VOTING_CANDIDATE_FORMAT
//!	Format of the message printed to indicate that a single candidate did
//!	not vote.
# define	SINGLE_NOT_VOTING_CANDIDATE_FORMAT \
	"\t%u candidate did not vote.\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	ElectionMessage	Messages indicating the state of an election.
//!	Definitions of messages used to indicate the the state of an election.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	ELECTION_STARTED_MESSAGE
//!	Format of the message printed to indicate that the election was started.
# define	ELECTION_STARTED_MESSAGE \
	"Election started.\n\n"

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
	"Usage:\n\t" \
	"CreationRandom [%s] <election directory> <candidates> <guarantors>" \
	"\n\n\t<candidates> must be in the range [%u .. %u]\n" \
	"\t<guarantors> must be in the range [%u .. %u]\n"

//! \def	CREATE_FORMAT
//!	Message printed when the program terminates successfully.
# define	CREATE_FORMAT \
	"Election successfully created with %u candidates and %u " \
	"guarantors.\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	StateMessage	Election state inspection program messages
//!	Definitions of messages used by the election state inspection program
//!	and related constants.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	STATE_USAGE_MESSAGE
//!	Message printed to explain the usage of the election state inspection
//!	program.
# define	STATE_USAGE_MESSAGE \
	"Usage:\n\tStateRandom [%s] <election directory>\n\n"

//! \def	ELECTION_CREATED_FORMAT
//!	Format of the message printed to show the numbers of candidates and
//!	guarantors.
# define	ELECTION_CREATED_FORMAT \
	"Election created with %u candidates and %u guarantors.\n\n"

//! \def	ELECTION_CLOSED_MESSAGE
//!	Message printed to indicated that the election is closed.
# define	ELECTION_CLOSED_MESSAGE \
	"\tElection completed;\n" \
	"\t%u guarantors still have to communicate their key.\n\n"

//! \def	ELECTION_TERMINATED_MESSAGE
//!	Message printed to indicated that the election is terminated.
# define	ELECTION_TERMINATED_MESSAGE \
	"Election terminated;\n\n"

//! \def	GUARANTORS_HEADER_FORMAT
//!	Format of the header printed when printing guarantors' data.
# define	GUARANTORS_HEADER_FORMAT \
		"Guarantors' data\n"

//! \def	CANDIDATES_HEADER_FORMAT
//!	Format of the header printed when printing candidates' data.
# define	CANDIDATES_HEADER_FORMAT \
		"Candidates' data\n"

//! \def	RESULT_HEADER_FORMAT
//!	Format of the header printed when printing election result.
# define	RESULT_HEADER_FORMAT	"Election result\n"

//! \def	GUARANTOR_NUMBER_HEADER
//!	Header of guarantors' numbers.
# define	GUARANTOR_NUMBER_HEADER	"Number"

//! \def	CANDIDATE_NUMBER_HEADER
//!	Header of candidates' numbers.
# define	CANDIDATE_NUMBER_HEADER	"Number"

//! \def	PLACEMENT_HEADER
//!	Header of candidates' placement.
# define	PLACEMENT_HEADER	"Placement"

//! \def	KEY_HEADER
//!	Header of keys.
# define	KEY_HEADER		"Key"

//! \def	HASH_HEADER
//!	Header of hashed keys.
# define	HASH_HEADER		"Hashed key"

//! \def	SIGNATURE_HEADER
//!	Header of signatures.
# define	SIGNATURE_HEADER	"Signature"

//! \def	MIXED_KEY_HEADER
//!	Header of mixed keys.
# define	MIXED_KEY_HEADER	"Mixed key"

//! \def	VOTE_HEADER
//!	Header of votes.
# define	VOTE_HEADER		"Vote"

//! \def	GUARANTOR_NUMBER_LENGTH
//!	Length of the fiels of candidates' numbers.
# define	GUARANTOR_NUMBER_LENGTH	2

//! \def	CANDIDATE_NUMBER_LENGTH
//!	Length of the fiels of candidates' numbers.
# define	CANDIDATE_NUMBER_LENGTH	7

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	StartMessage	Election starting program messages
//!	Definitions of messages used by the election starting program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	START_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the election
//!	starting program.
# define	START_USAGE_FORMAT \
	"Usage:\n" \
	"\tStartRandom [%s] <election directory> <guarantor> <key hash> " \
	"[<signature>]\n" \
	"\twhere <key hash> is the hashed key of %u bytes\n" \
	"\tand <signature> is the optional signature of %u bytes;\n" \
	"\t<key kash> and <signature> are written as ASCII characters,\n" \
	"two for each byte.\n" \

//! \def	GUARANTOR_HASH_SET_FORMAT
//!	Format of the message printed when a guarantor's key has has been set.
# define	GUARANTOR_HASH_SET_FORMAT \
	"Key of guarantor %u set\n"

//! \def	ALL_GUARANTORS_HASH_MESSAGE
//!	Message printed when all guarantor's hashed keys have has been
//!	communicated.
# define	ALL_GUARANTORS_HASH_MESSAGE \
	"All guarantors' hashed keys have been communicated; " \
	"election started.\n\n"

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
	"Usage:\n" \
	"\tVoteRandom [%s] <election directory> <candidate> <key> " \
	"[<signature>]\n" \
	"\twhere <key> is the key of %u bytes\n" \
	"\tand <signature> is the optional signature of %u bytes;\n" \
	"\t<key> and <signature> are written as ASCII characters, two for " \
	"each byte.\n"

//! \def	CANDIDATE_VOTE_SET_FORMAT
//!	Format of the message printed when a candidate's vote has has been set.
# define	CANDIDATE_VOTE_SET_FORMAT \
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
//! \defgroup	CloseMessage	Election closing program messages
//!	Definitions of messages used by the election closing program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	CLOSE_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the election
//!	closing program.
# define	CLOSE_USAGE_FORMAT \
	"Usage:\n" \
	"\tCloseRandom [%s] <election directory> <guarantor> <key>\n" \
	"\twhere <key> is the key of %u bytes\n" \
	"\t<key> is written as ASCII characters, two for each byte.\n"

//! \def	GUARANTOR_KEY_SET_FORMAT
//!	Format of the message printed when a guarantor's key has has been set.
# define	GUARANTOR_KEY_SET_FORMAT \
	"Key of guarantor %u set\n"

//! \def	ALL_GUARANTORS_KEYS_MESSAGE
//!	Message printed when all candidates's votes have has been communicated.
# define	ALL_GUARANTORS_KEYS_MESSAGE \
	"All guarantors' keys have been communicated; election terminated\n\n"

//! \def	COMPUTING_VOTES_MESSAGE
//!	Message printed when starting to compute the actual votes.
# define	COMPUTING_VOTES_MESSAGE	"Computing votes\n"

//! \def	VOTES_COMPUTED_MESSAGE
//!	Message printed to indicated that the election is terminated.
# define	VOTES_COMPUTED_MESSAGE \
	"All votes computed; election terminated;\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	HashMessage	Hash computation program messages
//!	Definitions of messages used by the hash computation program.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	HASH_USAGE_FORMAT
//!	Format of the message printed to explain the usage of the hash
//!	computation program.
# define	HASH_USAGE_FORMAT \
	"Usage: HashRandom [%s] <key>\n\twhere <key> is the key of %u bytes\n"

//! \def	HASH_VALUE_MESSAGE
//!	Message printed to show the hash value.
# define	HASH_VALUE_MESSAGE	"Hash value is: "

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	GenericMessage	Generic messages
//!	Definitions of messages used by various functions.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \def	GUARANTORS_KEY_FORMAT
//!	Format of output filler of variable lengt.
# define	GUARANTORS_KEY_FORMAT	"Guarantors' mixed key: %*s\n\n"

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

# endif
