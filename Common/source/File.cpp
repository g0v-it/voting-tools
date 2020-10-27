////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/04/2018
//!
//! \par	Function:
//!	Contains the definitions of static attributes and non inline functions
//!	of the io_space::File class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"File.h"

# if	!defined USE_INLINE
# include	"File.inl"
# endif

namespace	io_space
{

	const	CharString	File::NoPathName("<no name>");

	const	char*	const	File::OpenMode [LAST_FILE_TYPE]
					[LAST_OPEN_MODE] =
		{
			{
				//!	File open mode OPEN_READ: open for
				//!	reading, binary file.
			"rb",

				//!	File open mode OPEN_WRITE: open for
				//!	writing, binary file, destroys existing
				//!	file.
			"wb",

				//!	File open mode OPEN_READ_WRITE: open for
				//!	reading and writing, binary file,
				//!	destroys existing file.
			"wb+",

				//!	File open mode OPEN_UPDATE: open for
				//!	reading and writing, binary file, keeps
				//!	existing file.
			"rb+"

				//!	Not open.
			""
			},
			{
				//!	File open mode OPEN_READ: open for
				//!	reading, text file.
			"r",

				//!	File open mode OPEN_WRITE: open for
				//!	writing, text file, destroys existing
				//!	file.
			"w",

				//!	File open mode OPEN_READ_WRITE: open for
				//!	reading and writing, text file, destroys
				//!	existing file.
			"w+",

				//!	File open mode OPEN_UPDATE: open for
				//!	reading and writing, text file, keeps
				//!	existing file.
			"r+"

				//!	Not open.
			""
			}
		};

	const	int	File::SeekMode [LAST_SEEK_MODE] =
		{
			//! File seek mode FILE_SEEK_CUR: seek from current
			//! position.
		SEEK_CUR,
			//! File seek mode FILE_SEEK_END: seek from end of file.
		SEEK_END,
			//! File seek mode FILE_SEEK_SET: seek from beginning of
			//! file.
		SEEK_SET
		};

}
