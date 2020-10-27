////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	23/04/2018
//!
//! \par	Function:
//!	Contains the declarations of the io_space::LinuxFileManager class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined LINUX_FILE_MANAGER_H

# define	LINUX_FILE_MANAGER_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"Vector.h"
# include	"GenericString.h"
# include	"FileManager.h"

//! \def	LINUX_DIRECTORY_SEPARATOR
//!	Linux directory separator.
# define	LINUX_DIRECTORY_SEPARATOR	"/"

//! \def	LINUX_EXTENSION_SEPARATOR
//!	Linux extension separator.
# define	LINUX_EXTENSION_SEPARATOR	"."

//! \def	LINUX_CURRENT_DIRECTORY_NAME
//!	Linux current directory name.
# define	LINUX_CURRENT_DIRECTORY_NAME	"."

//! \def	LINUX_PARENT_DIRECTORY_NAME
//!	Linux parent directory name.
# define	LINUX_PARENT_DIRECTORY_NAME	".."

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	LinuxFileManager
//!	This class represents a file manager, specific to Linux platform and
//!	provides file handling capabilities.
//!
//! \see	FileManager::GetInstance	Declared as friend to allow
//!						access to constructor.
//!
////////////////////////////////////////////////////////////////////////////////

class	LinuxFileManager: public FileManager
	{

		friend	FileManager*	FileManager::GetInstance(void);

	private:

						LinuxFileManager(void)
							throw(FatalException);

						LinuxFileManager(const
							LinuxFileManager&
							thisFileManager)
							noexcept = delete;

						LinuxFileManager(
							LinuxFileManager&&
							thisFileManager)
							noexcept = delete;

		const	LinuxFileManager&	operator = (const
							LinuxFileManager&
							thisFileManager)
							noexcept = delete;

		const	LinuxFileManager&	operator = (LinuxFileManager&&
							thisFileManager)
							noexcept = delete;

	public:

			bool		IsDirectory(const CharString& PathName)
						const throw(FatalException,
						IOException);

			void		GetListOfFiles(const CharString&
						DirectoryPath,
						Vector<CharString> FileName)
						const throw(FatalException,
						IOException);

			void		CreateDirectory(const CharString&
						DirectoryPath) const
						throw(FatalException,
						IOException);

			void		RemoveFile(const CharString& PathName)
						const throw(FatalException,
						IOException);

			void		RemoveDirectory(const CharString&
						DirectoryPath) const
						throw(FatalException,
						IOException);

			void		SetReadOnly(const CharString& PathName)
						const throw(FatalException,
						IOException);

			void		SystemFlush(int FileDescriptor,
						const CharString& PathName)
						const throw(FatalException,
						IOException);

			void		Lock(int FileDescriptor, std_uint Size,
						const CharString& PathName)
						const throw(FatalException,
						IOException);

			void		Unlock(int FileDescriptor,
						std_uint Size,
						const CharString& PathName)
						const throw(FatalException,
						IOException);

			IOErrorType	MakeExceptionKind(int Error) const
						throw(FatalException);

	};

}

# if	defined USE_INLINE
# include	"LinuxFileManager.inl"
# endif

# endif
