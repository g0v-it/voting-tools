////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	17/04/2018
//!
//! \par	Function:
//! 	Contains the declaration of the
//!	application_space::ApplicationExceptionBase class, generated from
//!	utility_space::GenericException class template, with EXCEPTION_TYPE
//!	equal to application_space::ApplicationErrorType and
//!	NUMBER_OF_EXCEPTIONS equal to
//!	application_space::LAST_APPLICATION_EXCEPTION, and of the
//!	application_space::ApplicationException class, derived from the
//!	application_space::ApplicationExceptionBase class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined APPLICATION_EXCEPTION_H

# define	APPLICATION_EXCEPTION_H

# include	"GenericException.h"

namespace	application_space
{

using	namespace	utility_space;

////////////////////////////////////////////////////////////////////////////////
//! \enum	ApplicationErrorType
//!	Enumerated type for application exceptions.
//!
//! \note
//!	If the order is altered or if a new application exception is added, the
//!	initialization of the
//!	application_space::ApplicationExceptionBase::ExceptionName array must be
//!	updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	ApplicationErrorType
		{
			//!	A command line argument does not represent a
			//!	valid integer.
		INVALID_INTEGER,

			//!	A hexadecimal string has a wrong length.
		INVALID_HEX_LENGTH,

			//!	A string is not represent a valid hexadecimal
			//!	string.
		INVALID_HEX_STRING,

			//!	The number of candidates is not valid.
		INVALID_CANDIDATES_NUMBER,

			//!	The number of guarantors is not valid.
		INVALID_GUARANTORS_NUMBER,

			//!	The number of voters is not valid.
		INVALID_VOTERS_NUMBER,

			//!	The maximum vote is not valid.
		INVALID_MAXIMUM_VOTE,

			//!	The file containing candidates data has invalid
			//!	length.
		INVALID_CANDIDATES_FILE_LENGTH,

			//!	The file containing guarantors data has invalid
			//!	length.
		INVALID_GUARANTORS_FILE_LENGTH,

			//!	The file containing voters' indices has invalid
			//!	length.
		INVALID_VOTERS_FILE_LENGTH,

			//!	The file containing the votes has invalid
			//!	length.
		INVALID_VOTES_FILE_LENGTH,

			//!	The key used to encrypt the voters' indices is
			//!	invalid.
		INVALID_VOTERS_KEY,

			//!	The key used to encrypt the votes is invalid.
		INVALID_VOTES_KEY,

			//!	A time interval is zero or greater than the
			//!	maximum valid value.
		INVALID_INTERVAL,

			//!	The file containing candidates data is
			//!	corrupted.
		CORRUPTED_CANDIDATES_FILE,

			//!	The file containing guarantors data is
			//!	corrupted.
		CORRUPTED_GUARANTORS_FILE,

			//!	The file containing election parameters is
			//!	corrupted.
		CORRUPTED_PARAMETERS_FILE,

			//!	The file containing voters' indices is
			//!	corrupted.
		CORRUPTED_VOTERS_FILE,

			//!	The file containing votes is corrupted.
		CORRUPTED_VOTES_FILE,

			//!	The hash of the key of a candidate is not
			//!	correct.
		CANDIDATE_HASH_MISMATCH,

			//!	The hash of the key of a guarantor is not
			//!	correct.
		GUARANTOR_HASH_MISMATCH,

			//!	The election state is not valid for the
			//!	requested operation.
		INVALID_STATE,

			//!	The key is zero.
		INVALID_KEY,

			//!	The hash is zero.
		INVALID_HASH,

			//!	The number of the candidate is not valid.
		INVALID_CANDIDATE,

			//!	The number of the guarantor is not valid.
		INVALID_GUARANTOR,

			//!	The number of the voter is not valid.
		INVALID_VOTER,

			//!	The format of the line containing votes is not
			//!	valid or the line is empty.
		INVALID_VOTE_FORMAT,

			//!	A vote is not valid.
		INVALID_VOTE,

			//!	Some vote is missing.
		MISSING_VOTES,

			//!	Some vote is missing.
		MISSING_SIGNATURE,

			//!	The key of the guarantor has already been set.
		GUARANTOR_KEY_ALREADY_SET,

			//!	The vote of the candidate has already been set.
		CANDIDATE_VOTE_ALREADY_SET,

			//!	The format of the encryption key file is not
			//!	valid.
		INVALID_KEY_FILE_FORMAT,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_APPLICATION_EXCEPTION
		};

////////////////////////////////////////////////////////////////////////////////
//! \class	ApplicationExceptionBase
//!	Parent class for Application exceptions, instance of
//!	utility_space::GenericException, with EXCEPTION_TYPE equal to
//!	application_space::ApplicationErrorType and NUMBER_OF_EXCEPTIONS equal
//!	to application_space::LAST_APPLICATION_EXCEPTION.
//!
//! \see	application_space::ApplicationException
//!
////////////////////////////////////////////////////////////////////////////////

typedef	GenericException<ApplicationErrorType, LAST_APPLICATION_EXCEPTION>
		ApplicationExceptionBase;

////////////////////////////////////////////////////////////////////////////////
//! \class ApplicationException
//!	Class for application exceptions, derived from
//!	Application_space::ApplicationExceptionBase.
//!
////////////////////////////////////////////////////////////////////////////////

class	ApplicationException: public ApplicationExceptionBase
	{
	private:

//! \property	Index
//!	Index of the invalid record.
//!
//! \note
//!	The index is meaningful iff the error is CORRUPTED_CANDIDATES_FILE,
//!	CORRUPTED_GUARANTORS_FILE, CORRUPTED_PARAMETERS_FILE,
//!	CORRUPTED_VOTERS_FILE, CANDIDATE_HASH_MISMATCH, GUARANTOR_HASH_MISMATCH,
//!	GUARANTOR_KEY_ALREADY_SET or CANDIDATE_VOTE_ALREADY_SET.
			std_uint		Index;

		const	ApplicationException&	operator = (const
							ApplicationException&
							thisException)
							noexcept = delete;

		const	ApplicationException&	operator =
							(ApplicationException&&
							thisException)
							noexcept = delete;

	public:
				ApplicationException(ApplicationErrorType
					thisExceptionKind,
					const char* thisFileName,
					std_uint thisLineNumber) noexcept;

				ApplicationException(ApplicationErrorType
					thisExceptionKind, std_uint thisRecord,
					const char* thisFileName,
					std_uint thisLineNumber) noexcept;

				ApplicationException(const ApplicationException&
					thisException) noexcept;

				ApplicationException(ApplicationException&&
					thisException) noexcept;

		std_uint	GetIndex(void) const noexcept;

	};

////////////////////////////////////////////////////////////////////////////////
//! \def	make_application_exception(ErrorKind)
//!	Create an ApplicationException object, using current source file name
//!	and current line number, without record index.
//!
//! \param	ErrorKind	Enumerated value of type
//!				application_space::ApplicationErrorType.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_application_exception(ErrorKind)	\
			ApplicationException((ErrorKind), __FILE__, __LINE__)

////////////////////////////////////////////////////////////////////////////////
//! \def	make_application_index_exception(ErrorKind)
//!	Create an ApplicationException object, using current source file name
//!	and current line number, with record index.
//!
//! \param	ErrorKind	Enumerated value of type
//!				application_space::ApplicationErrorType.
//! \param	Index		Index of the invalid record.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_application_index_exception(ErrorKind, Index)	\
			ApplicationException((ErrorKind), (Index), __FILE__, \
			__LINE__)

}

# if	defined USE_INLINE
# include	"ApplicationException.inl"
# endif

# endif
