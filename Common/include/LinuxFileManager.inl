////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	28/10/2009
//!
//! \par	Function:
//!	Contains the definition of inline functions of the
//!	io_space::LinuxFileManager class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

///////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation for
//!						attributes fails.
//!
//! \returns	Not applicable.
//!
//! \see	LINUX_DIRECTORY_SEPARATOR
//! \see	LINUX_EXTENSION_SEPARATOR
//! \see	LINUX_CURRENT_DIRECTORY_NAME
//! \see	LINUX_PARENT_DIRECTORY_NAME
//!
///////////////////////////////////////////////////////////////////////////////

	INLINE	LinuxFileManager::LinuxFileManager(void) throw(FatalException):
			FileManager(CharString(LINUX_DIRECTORY_SEPARATOR),
			CharString(LINUX_EXTENSION_SEPARATOR),
			CharString(LINUX_CURRENT_DIRECTORY_NAME),
			CharString(LINUX_PARENT_DIRECTORY_NAME))
		{
		}

}
