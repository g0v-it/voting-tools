////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/10/2018
//!
//! \par	Function:
//!	It contains the definitions of inline functions of the
//!	io_space::VotersFile class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

using	namespace	utility_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	VotersFile::VotersFile(void) throw(FatalException): File()
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor; if the file is still open, the function closes it and
//!	throws an exception.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_CLOSE_ERROR	If the File is open and an error
//!						occurs while closing it.
//! \throw	io_space::FILE_NOT_CLOSED	If the File is open.
//!
//! \returns	Not applicable.
//!
//! \note
//!	The exception could be thrown when the File is destroyed while
//!	processing another exception, thrown but not yet caught.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	VotersFile::~VotersFile(void) throw(FatalException, IOException)
	{
	}

}
