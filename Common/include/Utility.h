////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	13/10/2018
//!
//! \par	Function:
//!	Contains the declaration of the common utility_space functions.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	UTILITY_H

# define	UTILITY_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"GenericString.h"

namespace	utility_space
{

using	namespace	io_space;
using	namespace	application_space;

std_uint	PowerOfTwo(std_uint Exponent) throw(NumericException);

std_uint	Size(std_uint Value) noexcept;

std_uint	RotateRight(std_uint Argument, std_uint Amount) noexcept;

void		HandleOptions(int& argc, char**& argv) noexcept;

std_uint	DecodeInteger(const char* Argument)
			throw(FatalException, ApplicationException);

void		DecodeHex(register const char* Argument, register byte* Buffer,
			register std_uint Length) throw(ApplicationException);

void		EncodeHex(register const byte* Argument, register char* Buffer,
			register std_uint Length) noexcept;

CharString	MakePathName(const CharString& DirectoryPath,
			const CharString& FileName) throw(FatalException);

std_uint	PrintCenteredHeader(const CharString& Header, std_uint Size,
			std_uint Offset) throw(IOException);

}

# if	defined USE_INLINE
# include	"Utility.inl"
# endif

# endif
