////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	25/04/2018
//!
//! \par	Function:
//!	Contains the definitions of static attributes and non inline functions
//!	of the io_space::FileManager abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<sys/stat.h>
# include	<errno.h>

# include	"Standard.h"
# include	"FileManager.h"
# include	"ActualFileManager.h"

# if	!defined USE_INLINE
# include	"FileManager.inl"
# endif

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor
//!
//! \throw	None
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

FileManager::~FileManager(void) noexcept
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether a file or directory exists or not.
//!
//! \param	PathName				Path name of the file or
//!							directory.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access the
//!							file.
//!
//! \returns	bool					true if file exists.
//!
////////////////////////////////////////////////////////////////////////////////

bool	FileManager::FileExists(const CharString& PathName) const
		throw(FatalException, IOException)
	{
	struct	stat	StatVar;

	if (stat(PathName.GetString(), &StatVar) == 0)
		return true;
	if (errno == ENOENT)
		return false;
	throw make_IO_exception(MakeExceptionKind(errno), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the size of a file.
//!
//! \param	PathName				Path name of the file.
//!
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access the
//!							file.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//!
//! \returns	std_uint				File size in bytes.
//!
////////////////////////////////////////////////////////////////////////////////

std_uint	FileManager::GetFileSize(const CharString& PathName) const
			throw(FatalException, IOException)
	{
	struct	stat	StatVar;

	if (stat(PathName.GetString(), &StatVar) == 0)
		return static_cast<std_uint>(StatVar.st_size);
	throw make_IO_exception(MakeExceptionKind(errno), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Flush the system buffers of the file to the actual device. \n
//!	Default implementation for systems that do not allow flushing of a
//!	single file.
//!
//! \throw	None.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

void	FileManager::SystemFlush(int FileDescriptor, const CharString& PathName)		const throw(FatalException, IOException)
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return a pointer to the singleton instance of the FileManager object,
//!	depending upon actual FileManager. \n
//!	The instance is created as a static member of the function, instead of
//!	static member of the class. Though this is a little inefficient, it
//!	ensures the order of creation of objects.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	FileManager*			Pointer to current FileManager
//!						object.
//!
////////////////////////////////////////////////////////////////////////////////

FileManager*	FileManager::GetInstance(void) throw(FatalException)
	{
	static	ActualFileManager	FileManagerInstance;

	return &FileManagerInstance;
	}

}
