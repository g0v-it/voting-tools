////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	28/10/2009
//!
//! \par	Function:
//!	Contains the definitions of non inline functions of the
//!	io_space::LinuxFileManager class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<dirent.h>
# include	<unistd.h>
# include	<errno.h>
# include	<sys/stat.h>

# include	"Standard.h"
# include	"LinuxFileManager.h"

# if	!defined USE_INLINE
# include	"LinuxFileManager.inl"
# endif

//! \def	FILE_UNLINK_OK
//!	Valure returned by unlink when the operation succeeds.
# define	FILE_UNLINK_OK				0

//! \def	DIRECTORY_CLOSE_OK
//!	Value returned by closedir when the operation succeeds.
# define	DIRECTORY_CLOSE_OK			0

//! \def	DIRECTORY_REMOVE_OK
//!	Value returned by rmdir when the operation succeeds.
# define	DIRECTORY_REMOVE_OK			0

//! \def	CHANGE_MODE_OK
//!	Value returned by chmod when the operation succeeds.
# define	CHANGE_MODE_OK				0

//! \def	LOCK_OK
//!	Value returned by lockf when the operation succeeds.
# define	LOCK_OK					0

//! \def	FSYNC_OK
//!	Value returned by fsync when the operation succeeds.
# define	FSYNC_OK				0

//! \def	DEFAULT_DIRECTORY_PERMISSIONS
//!	Default permissions when creating a directory.
# define	DEFAULT_DIRECTORY_PERMISSIONS		0777

//! \def	READ_ONLY_PERMISSIONS
//!	Read only permissions.
# define	READ_ONLY_PERMISSIONS			0444

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether a path name refers a directory or not.
//!
//! \param	PathName				Path name to be checked.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access the
//!							file.
//!
//! \returns	bool					true if path refers a
//!							directory
//!
////////////////////////////////////////////////////////////////////////////////

bool	LinuxFileManager::IsDirectory(const CharString& PathName) const
		throw(FatalException, IOException)
	{
	struct	stat	StatVar;

	if (stat(PathName.GetString(), &StatVar) == 0)
		return S_ISDIR(StatVar.st_mode);
	throw make_IO_exception(MakeExceptionKind(errno), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the list of files in a given directory, excluding current directory
//!	name and parent directory name.
//!
//! \param	DirectoryPath				Path of the directory.
//! \param	FileName				Vector of strings, to be
//!							filled with file names,
//!							in no particular order.
//!							Previous Vector content
//!							is discarded.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//! \throw	io_space::FILE_NOT_A_DIRECTORY		If the path name does
//!							not refer to a
//!							directory.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to access the
//!							file.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	None
//!
//! \note
//!	If an exception is thrown, the content of FileName is undefined.
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::GetListOfFiles(const CharString& DirectoryPath,
		Vector<CharString> FileName) const
		throw(FatalException, IOException)
	{
	DIR*		DirHandle;
	struct	dirent*	DirEntry;
	CharString	CurrentFile;

	if (!IsDirectory(DirectoryPath))
		throw make_IO_exception(FILE_NOT_A_DIRECTORY, DirectoryPath);
	FileName.Clear();

		// Open the directory
	DirHandle = opendir(DirectoryPath.GetString());
	if (static_cast<DIR*>(NULL) == DirHandle)
		throw make_IO_exception(MakeExceptionKind(errno),
			DirectoryPath);

		// Read the Directory
	while ((DirEntry = readdir(DirHandle)) != static_cast<dirent*>(NULL))
		{
		CurrentFile = CharString(DirEntry->d_name);

			// Skip current directory (".") and parent
			// directory ("..")
		if (CurrentFile != GetCurrentDirectoryName() &&
			CurrentFile != GetParentDirectoryName())
			FileName.Append(CurrentFile);
		}
	if (closedir(DirHandle) != DIRECTORY_CLOSE_OK)
		throw make_IO_exception(MakeExceptionKind(errno),
			DirectoryPath);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create a directory.
//!
//! \param	DirectoryPath				Path of the directory to
//!							be created
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_ALREADY_EXISTS		If a file or directory
//!							with the given path
//!							already exists.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to create the
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If the link count of the
//!							parent directory would
//!							exceed the maximum.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::CreateDirectory(const CharString& DirectoryPath) const
		throw(FatalException, IOException)
	{
	if (mkdir(DirectoryPath.GetString(), DEFAULT_DIRECTORY_PERMISSIONS) !=
		0)
		throw make_IO_exception(MakeExceptionKind(errno),
			DirectoryPath);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Remove a file.
//!
//! \param	PathName				Path of the file to be
//!							removed
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//! \throw	io_space::FILE_IS_A_DIRECTORY		If the path name refers
//!							to a directory.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the user has not the
//!							the permission to remove
//!							the file.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::RemoveFile(const CharString& PathName) const
		throw(FatalException, IOException)
	{
	if (IsDirectory(PathName))
		throw make_IO_exception(FILE_IS_A_DIRECTORY, PathName);
	if (unlink(PathName.GetString()) != FILE_UNLINK_OK)
		throw make_IO_exception(MakeExceptionKind(errno), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Remove a directory.
//!
//! \param	DirectoryPath				Path of the directory to
//!							be removed
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the directory does
//!							not exist.
//! \throw	io_space::FILE_NOT_A_DIRECTORY		If the path name does
//!							not refer to a
//!							directory.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the user has not the
//!							the permission to remove
//!							the directory.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::RemoveDirectory(const CharString& DirectoryPath) const
		throw(FatalException, IOException)
	{
	if (!IsDirectory(DirectoryPath))
		throw make_IO_exception(FILE_NOT_A_DIRECTORY, DirectoryPath);
	if (rmdir(DirectoryPath.GetString()) != DIRECTORY_REMOVE_OK)
		throw make_IO_exception(MakeExceptionKind(errno),
			DirectoryPath);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Set permissions of a file as read only.
//!
//! \param	PathName				Path name of the file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the file does not
//!							exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the user has not the
//!							the permission to change
//!							permissions.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::SetReadOnly(const CharString& PathName) const
		throw(FatalException, IOException)
	{
	if (chmod(PathName.GetString(), READ_ONLY_PERMISSIONS) !=
		CHANGE_MODE_OK)
		throw make_IO_exception(MakeExceptionKind(errno), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Flush the system buffers of the file to the actual device.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened or if
//! \throw	io_space::FILE_WRITE_ERROR	If an error occurs while writing
//!						data or if the File is a special
//!						device which does not support
//!						synchronization.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::SystemFlush(int FileDescriptor,
		const CharString& PathName) const
		throw(FatalException, IOException)
	{
	if (fsync(FileDescriptor) != FSYNC_OK)
		{
		if (errno == EBADF)
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		throw make_IO_exception(FILE_WRITE_ERROR, PathName);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Lock a given number of bytes, from current position.
//!
//! \param	FileDescriptor				File descriptor of the
//!							file.
//! \param	Size					Number of bytes to lock.
//! \param	PathName				PathName of the file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the file has not been
//!							opened in write or
//!							read-write or update
//!							mode.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the file has been
//!							memory mapped by another
//!							process.
//! \throw	io_space::FILE_DEADLOCK			If the lock would cause
//!							a deadlock.
//! \throw	io_space::TOO_MANY_LOCKS		If there are too many
//!							locks.
//!
//! \returns	None
//!
//! \note
//!	If the locked part overlaps another locked part, the locks are merged.
//!
//! \note
//!	If the locked part overlaps a part that has been locked by another
//!	process, the function waits for the other process to unlock the part.
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::Lock(int FileDescriptor, std_uint Size,
		const CharString& PathName) const
		throw(FatalException, IOException)
	{
	if (lockf(FileDescriptor, F_LOCK, Size) != LOCK_OK)
		{
		if (errno == EINVAL)
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		throw make_IO_exception(MakeExceptionKind(errno), PathName);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Unlock a given number of bytes, from current position.
//!
//! \param	FileDescriptor				File descriptor of the
//!							file.
//! \param	Size					Number of bytes to lock.
//! \param	PathName				PathName of the file.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the file has not been
//!							opened in write or
//!							read-write or update
//!							mode.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the file has been
//!							memory mapped by another
//!							process.
//!
//! \returns	None
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxFileManager::Unlock(int FileDescriptor, std_uint Size,
		const CharString& PathName) const
		throw(FatalException, IOException)
	{
	if (lockf(FileDescriptor, F_ULOCK, Size) != LOCK_OK)
		{
		if (errno == EINVAL)
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		throw make_IO_exception(MakeExceptionKind(errno), PathName);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the file exception corresponding to a standard error.
//!
//! \param	Error				Error value as defined in
//!						errno.h.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails
//!						fails when creating an
//!						exception.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the error not among those
//!						defined in errno.h.
//!
//! \returns	io_space::IOErrorType		File Exception value.
//!
////////////////////////////////////////////////////////////////////////////////

IOErrorType	LinuxFileManager::MakeExceptionKind(int Error) const
			throw(FatalException)
	{
	switch (Error)
		{
		case ENOENT:
			return FILE_DOES_NOT_EXIST;
		case EEXIST:
			return FILE_ALREADY_EXISTS;
		case EACCES:
		case EPERM:
		case EDQUOT:
		case EAGAIN:
		case ENOTEMPTY:
			return FILE_PERMISSION_DENIED;
		case EMFILE:
		case ENFILE:
			return TOO_MANY_OPEN_FILES;
		case EISDIR:
		case EROFS:
		case EBUSY:
		case ETXTBSY:
			return FILE_PERMISSION_DENIED;
		case ENAMETOOLONG:
		case EFAULT:
		case ELOOP:
		case ENOTDIR:
		case EINVAL:
		case ENODEV:
		case ENXIO:
			return FILE_INVALID_PATH_NAME;
		case EIO:
		case ENOMEM:
		case ENOSPC:
		case EOVERFLOW:
			return FILE_IO_ERROR;
		case EDEADLOCK:
			return FILE_DEADLOCK;
		case ENOLCK:
			return TOO_MANY_LOCKS;
		default:
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		}
	}

}
