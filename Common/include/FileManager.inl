////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	25/04/2018
//!
//! \par	Function:
//!	Contains the definition of inline functions of the io_space::FileManager
//!	abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Constructor.
//!
//! \param	thisDirectorySeparator		Directory separator.
//! \param	thisExtensionSeparator		Extension separator.
//! \param	thisCurrentDirectory		Current directory name.
//! \param	thisParentDirectory		Parent directory name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation for
//!						attributes fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

	INLINE	FileManager::FileManager(const CharString&
			thisDirectorySeparator,
			const CharString& thisExtensionSeparator,
			const CharString& thisCurrentDirectory,
			const CharString& thisParentDirectory)
			throw(FatalException):
			DirectorySeparator(thisDirectorySeparator),
			ExtensionSeparator(thisExtensionSeparator),
			CurrentDirectoryName(thisCurrentDirectory),
			ParentDirectoryName(thisParentDirectory)
		{
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns platform specific directory separator as a string.
//!
//! \throw	None
//!
//! \returns	const	CharString&	Platfrom specific directory separatory.
//!
////////////////////////////////////////////////////////////////////////////////

	INLINE	const	CharString&	FileManager::GetDirectorySeparator(void)
						const noexcept
		{
		return DirectorySeparator;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns platform specific extension separator as a string.
//!
//! \throw		None
//!
//! \returns	const	CharString&	Platfrom specific extension separatory.
//!
////////////////////////////////////////////////////////////////////////////////

	INLINE	const	CharString&	FileManager::GetExtensionSeparator(void)
						const noexcept
		{
		return ExtensionSeparator;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns platform specific name of current directory.
//!
//! \throw		None
//!
//! \returns	const	CharString&	Platfrom specific name of current
//!					directory.
//!
////////////////////////////////////////////////////////////////////////////////

	INLINE	const	CharString&	FileManager::
						GetCurrentDirectoryName(void)
						const noexcept
		{
		return CurrentDirectoryName;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns platform specific name of parent directory.
//!
//! \throw		None
//!
//! \returns	const	CharString&	Platfrom specific name of parent
//!					directory.
//!
////////////////////////////////////////////////////////////////////////////////

	INLINE	const	CharString&	FileManager::
						GetParentDirectoryName(void)
						const noexcept
		{
		return ParentDirectoryName;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Remove a file or directory. \n
//!	A directory can be remove only if it is empty.
//!
//! \param	PathName				Path name of the file to
//!							be removed.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs
//!							during the operation.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the source file does
//!							not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If the user has not the
//!							the permission to remove
//!							the file.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	FileManager::Remove(const CharString& PathName) const
			throw(FatalException, IOException)
		{
		if (remove(PathName.GetString()) != FILE_REMOVE_OK)
			throw make_IO_exception(MakeExceptionKind(errno),
				PathName);
		}

}
