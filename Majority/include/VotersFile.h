////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/10/2018
//!
//! \par	Function:
//!	It contains the declaration of the io_space::VotersFile class.
//!
////////////////////////////////////////////////////////////////////////////////

# if !defined	VOTERS_FILE_H

# define	VOTERS_FILE_H

# include	"Parameter.h"
# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"File.h"
# include	"Vector.h"
# include	"RandomGenerator.h"

namespace	io_space
{

using	namespace	utility_space;
using	namespace	application_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	VotersFile
//!	The VotersFile class represents a File containing for each voter the
//!	index of its data into the votes file.
//!
//! \fileformat
//! \see	VotersFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

class	VotersFile: private File
	{
	private:

				VotersFile(const VotersFile& Argument)
					noexcept = delete;

				VotersFile(VotersFile&& Argument) noexcept =
					delete;

		VotersFile&	operator = (const VotersFile& Argument)
					noexcept = delete;

		VotersFile&	operator = (VotersFile&& Argument) noexcept =
					delete;

	public:

				VotersFile(void) throw(FatalException);

				~VotersFile(void)
					throw(FatalException, IOException);

		void		Create(const CharString& thisPathName,
					register std_uint Voters,
					const byte Key [ENCRYPTION_KEY_LENGTH],
					register RandomGenerator& Generator)
					throw(FatalException, IOException);

		void		Read(const CharString& thisPathName,
					register std_uint Voters,
					register Vector<std_uint>& VoterIndex,
					const byte Key [ENCRYPTION_KEY_LENGTH])
					throw(FatalException, IOException,
					ApplicationException);

	};

}

# if defined	USE_INLINE
# include	"VotersFile.inl"
# endif

# endif
