////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	17/04/2018
//!
//! \par	Function:
//!	Contains the definitions of static attributes of the
//!	application_space::ApplicationException class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"ApplicationException.h"

# if	!defined USE_INLINE
# include	"ApplicationException.inl"
# endif

namespace	utility_space
{

using	namespace	application_space;

//! \property	ApplicationExceptionBase::ExceptionName
//!	Names of the application exceptions.\n
//!	The order of the strings must correspond to that of the
//!	application_space::ApplicationErrorType enumerated type.
template<>
const	char*	const	ApplicationExceptionBase::ExceptionName
				[LAST_APPLICATION_EXCEPTION] =
	{
	"a command line argument does not represent a valid integer",
	"a hexadecimal string has a wrong length",
	"a string is not a valid hexadecimal string",
	"the number of candidates is not valid",
	"the number of guarantors is not valid",
	"the number of voters is not valid",
	"the maximum vote is not valid",
	"the file containing candidates data has invalid length",
	"the file containing guarantors data has invalid length",
	"the file containing voters' indices has invalid length",
	"the file containing votes has invalid length",
	"the voters' key is not correct",
	"the votes' key is not correct",
	"the time interval is zero or greater than the maximum valid value",
	"the file containing candidates' data is corrupted",
	"the file containing guarantors' data is corrupted",
	"the file containing election parameters is corrupted",
	"the file containing voters' indices is corrupted",
	"the file containing votes is corrupted",
	"the hash of the key of a candidate is not correct",
	"the hash of the key of a guarantor is not correct",
	"the election state is not valid for the requested operation",
	"the key is zero",
	"the hash is zero",
	"the number of the candidate is not valid",
	"the number of the guarantor is not valid",
	"the number of the voter is not valid",
	"the format of the line containing votes is not valid",
	"a vote is not valid",
	"some vote is missing",
	"the signature is missing",
	"the key of the guarantor has already been set",
	"the vote of the candidate has already been set",
	"the format of the encryption file is not valid"
	};

}
