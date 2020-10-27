////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	25/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the io_space::FileManager abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined FILE_MANAGER_H

# define	FILE_MANAGER_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"Vector.h"
# include	"GenericString.h"

# include	<stdio.h>
# include	<errno.h>

//! \def	FILE_REMOVE_OK
//!	Valure returned by remove when the operation succeeds.
# define	FILE_REMOVE_OK			0

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	FileManager
//!	Abstract class, which declares all the basic file system related
//!	services. \n
//!	This class provides a default implementation of all those methods for
//!	which a portable, system independent implementation is possible;
//!	remaining methods are purely virtual methods and will be implemented in
//!	derived classes. \n
//!	Semaining services are implemented for every system through a concrete
//!	OS specific derived class. \n
//!	The FileManager class is a singleton. The class defines GetInstance
//!	function, which will return the current FileManager object.
//!
////////////////////////////////////////////////////////////////////////////////

class	FileManager
	{
	private:

//! \property	DirectorySeparator
//!	Platform specific directory separator
			const	CharString	DirectorySeparator;

//! \property	ExtensionSeparator
//!	Platform specific extension separator
			const	CharString	ExtensionSeparator;

//! \property	CurrentDirectoryName
//!	Platform specific name of current directory.
			const	CharString	CurrentDirectoryName;

//! \property	ParentDirectoryName
//!	Platform specific name of parent directory.
			const	CharString	ParentDirectoryName;

						FileManager(const FileManager&
							thisFileManager)
							noexcept = delete;

						FileManager(FileManager&&
							thisFileManager)
							noexcept = delete;

			const	FileManager&	operator = (const FileManager&
							thisFileManager)
							noexcept = delete;

			const	FileManager&	operator = (FileManager&&
							thisFileManager)
							noexcept = delete;

	protected:

						FileManager(const CharString&
							thisDirectorySeparator,
							const CharString&
							thisExtensionSeparator,
							const CharString&
							thisCurrentDirectory,
							const CharString&
							thisParentDirectory)
							throw(FatalException);

		virtual				~FileManager(void) noexcept;

	public:

			const	CharString&	GetDirectorySeparator(void)
							const noexcept;

			const	CharString&	GetExtensionSeparator(void)
							const noexcept;

			const	CharString&	GetCurrentDirectoryName(void)
							const noexcept;

			const	CharString&	GetParentDirectoryName(void)
							const noexcept;

		virtual		bool		FileExists(const CharString&
							PathName) const
							throw(FatalException,
							IOException);

		virtual		bool		IsDirectory(const CharString&
							PathName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		void		GetListOfFiles(const CharString&
							DirectoryPath,
							Vector<CharString>
							FileName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		void		CreateDirectory(const
							CharString&
							DirectoryName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

				void		Remove(const CharString&
							PathName) const
							throw(FatalException,
							IOException);

		virtual		void		RemoveFile(const CharString&
							DirectoryName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		void		RemoveDirectory(const
							CharString&
							DirectoryName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		std_uint	GetFileSize(const CharString&
							PathName) const
							throw(FatalException,
							IOException);

		virtual		void		SetReadOnly(const CharString&
							PathName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		void		SystemFlush(int FileDescriptor,
							const CharString&
							PathName) const
							throw(FatalException,
							IOException);

		virtual		void		Lock(int FileDescriptor,
							std_uint Size,
							const CharString&
							PathName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		void		Unlock(int FileDescriptor,
							std_uint Size,
							const CharString&
							PathName) const
							throw(FatalException,
							IOException) =
							PURE_VIRTUAL;

		virtual		IOErrorType	MakeExceptionKind(int Error)
							const
							throw(FatalException) =
							PURE_VIRTUAL;

		static		FileManager*	GetInstance(void)
							throw(FatalException);

	};

}

# if	defined USE_INLINE
# include "FileManager.inl"
# endif

# endif
