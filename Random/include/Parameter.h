////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	22/04/2018
//!
//! \par	Function:
//!	Contains the definitions of the parameters of self-election handling
//!	programs.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	PARAMETER_H

# define	PARAMETER_H

//! \def	KEY_LENGTH
//!	Length of guarantors and candidates keys in bytes.
//!
//! \note
//!	Due to current implementation of the hash function, the maximum value is
//!	55.
# define	KEY_LENGTH			55

//! \def	CANDIDATE_NUMBER_LENGTH
//!	Length of the candidate number in bytes.
# define	CANDIDATE_NUMBER_LENGTH		7

//! \def	CANDIDATE_KEY_LENGTH
//!	Length of the part of their key that candidates must insert.
//!
//! \see	KEY_LENGTH
//! \see	CANDIDATE_NUMBER_LENGTH
# define	CANDIDATE_KEY_LENGTH \
	(KEY_LENGTH - CANDIDATE_NUMBER_LENGTH)

//! \def	HASH_LENGTH
//!	Length of key hash value in bytes.
# define	HASH_LENGTH			32

//! \def	SIGNATURE_LENGTH
//!	Length of signature in bytes.
# define	SIGNATURE_LENGTH		32

//! \def	VOTE_LENGTH
//!	Length of hashed vote in bytes.
# define	VOTE_LENGTH			HASH_LENGTH

//! \def	CANDIDATE_RECORD_LENGTH
//!	Length of a candidate record in bytes.
//!
//! \see	KEY_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	VOTE_LENGTH
# define	CANDIDATE_RECORD_LENGTH \
	(KEY_LENGTH + SIGNATURE_LENGTH + VOTE_LENGTH)

//! \def	CANDIDATE_KEY_OFFSET
//!	Offset of the candidate selectable part of the key with respect to the
//!	beginning of a record in candidates' data file.
//!
//! \see	CANDIDATE_NUMBER_LENGTH
# define	CANDIDATE_KEY_OFFSET	CANDIDATE_NUMBER_LENGTH

//! \def	CANDIDATE_SIGNATURE_OFFSET
//!	Offset of the signature with respect to the beginning of a record in
//!	candidates' data file.
//!
//! \see	KEY_LENGTH
# define	CANDIDATE_SIGNATURE_OFFSET \
	KEY_LENGTH

//! \def	CANDIDATE_VOTE_OFFSET
//!	Offset of the final vote with respect to the beginning of a record in
//!	candidates' data file.
//!
//! \see	CANDIDATE_SIGNATURE_OFFSET
//! \see	SIGNATURE_LENGTH
# define	CANDIDATE_VOTE_OFFSET \
	(CANDIDATE_SIGNATURE_OFFSET + SIGNATURE_LENGTH)

//! \def	GUARANTOR_RECORD_LENGTH
//!	Length of a guarantor record in bytes.
//!
//! \see	KEY_LENGTH
//! \see	HASH_LENGTH
//! \see	SIGNATURE_LENGTH
# define	GUARANTOR_RECORD_LENGTH \
	(KEY_LENGTH + HASH_LENGTH + SIGNATURE_LENGTH)

//! \def	GUARANTOR_HASH_OFFSET
//!	Offset of the hashed key with respect to the beginning of a record in
//!	guarantors' data file.
//!
//! \see	KEY_LENGTH
# define	GUARANTOR_HASH_OFFSET	KEY_LENGTH

//! \def	GUARANTOR_SIGNATURE_OFFSET
//!	Offset of the signature with respect to the beginning of a record in
//!	guarantors' data file.
//!
//! \see	GUARANTOR_HASH_OFFSET
//! \see	HASH_LENGTH
# define	GUARANTOR_SIGNATURE_OFFSET \
	(GUARANTOR_HASH_OFFSET + HASH_LENGTH)

//! \def	MAXIMUM_RECORD_LENGTH
//!	Maximum length of a record in bytes.
# define	MAXIMUM_RECORD_LENGTH \
	(CANDIDATE_RECORD_LENGTH > GUARANTOR_RECORD_LENGTH? \
	CANDIDATE_RECORD_LENGTH: GUARANTOR_RECORD_LENGTH)

//! \def	GUARANTORS_FILE_NAME
//!	Name of the file containing guarantors keys and corresponging hash
//!	values.
# define	GUARANTORS_FILE_NAME	"Guarantors"

//! \def	CANDIDATES_FILE_NAME
//!	Name of the file containing candidates keys and corresponging hash
//!	values.
# define	CANDIDATES_FILE_NAME	"Candidates"

//! \def	MINIMUM_CANDIDATES
//!	Minimum number of candidates.
# define	MINIMUM_CANDIDATES	2

//! \def	MAXIMUM_CANDIDATES
//!	Maximum number of candidates.
# define	MAXIMUM_CANDIDATES	9999999

//! \def	MINIMUM_GUARANTORS
//!	Minimum number of guarantors.
# define	MINIMUM_GUARANTORS	1

//! \def	MAXIMUM_GUARANTORS
//!	Maximum number of guarantors.
# define	MAXIMUM_GUARANTORS	99

# endif
