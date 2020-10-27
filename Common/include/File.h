////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the io_space::File class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined FILE_H

# define	FILE_H

# include	"FatalException.h"
# include	"IOException.h"
# include	"GenericString.h"
# include	"FileManager.h"

# if	!defined NDEBUG
# include	<typeinfo>	// Defines typeid() used in .tpl
# endif

# include	<stdio.h>
# include	<errno.h>

//! \def	MAXIMUM_ITEM_SIZE
//!	Maximum size and number of items for Read and Write.
# define	MAXIMUM_ITEM_SIZE		(static_cast<std_uint>(0xFFFF))

//! \def	MAXIMUM_BUFFER_SIZE
//!	Max buffer size for Open.
# define	MAXIMUM_BUFFER_SIZE		(static_cast<std_uint>(0xFFFF))

//! \def	FILE_CLOSE_OK
//!	Valure returned by fclose when the operation succeeds.
# define	FILE_CLOSE_OK			0

//! \def	FILE_SETBUF_OK
//!	Valure returned by setvbuf when the operation succeeds.
# define	FILE_SETBUF_OK			0

//! \def	FILE_SEEK_OK
//!	Valure returned by fseek when the operation succeeds.
# define	FILE_SEEK_OK			0

//! \def	FILE_EOF_FALSE
//!	Valure returned by feof when the end of file flag is not set.
# define	FILE_EOF_FALSE			0

//! \def	DEFAULT_STDIN_PATHNAME
//!	Default name used for stdin file.
# define	DEFAULT_STDIN_PATHNAME		"<standard input>"

//! \def	DEFAULT_STDOUT_PATHNAME
//!	Default name used for stdout file.
# define	DEFAULT_STDOUT_PATHNAME		"<standard output>"

//! \def	DEFAULT_STDERR_PATHNAME
//!	Default name used for stderr file.
# define	DEFAULT_STDERR_PATHNAME		"<standard error>"

namespace	io_space
{

////////////////////////////////////////////////////////////////////////////////
//! \enum	OpenModeType
//!	Open modes. \n
//!
//! \note
//!	If the order is altered or if a new open mode is added, the
//!	initialization of the File::OpenMode array must be updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	OpenModeType
		{
			//!	Read only mode.
		OPEN_READ,

			//!	Write only mode.
		OPEN_WRITE,

			//!	Read and write mode.
		OPEN_READ_WRITE,

			//!	Update mode.
		OPEN_UPDATE,

			//!	Not open.
			//!	Must follow all valid open modes.
		NOT_OPEN,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_OPEN_MODE
		};

////////////////////////////////////////////////////////////////////////////////
//! \enum	SeekModeType
//!	File seek modes. \n
//!
//! \note
//!	If the order is altered or if a new seek mode is added, the
//!	initialization of the File::SeekMode array must be updated accordingly.
//!
////////////////////////////////////////////////////////////////////////////////

	enum	SeekModeType
		{
			//!	Seek from current position.
		FILE_SEEK_CUR,

			//!	Seek from end of file.
		FILE_SEEK_END,

			//!	Seek from beginning of file.
		FILE_SEEK_SET,

			//!	Dummy value to mark the end of enumerated type:
			//!	do not use.
		LAST_SEEK_MODE
		};

////////////////////////////////////////////////////////////////////////////////
//! \class	File
//!	Represents a file and provides file handling capabilities.
//!
//! \see	make_IO_exception
//! \see	OpenModeType
//! \see	SeekModeType
//! \see	MAXIMUM_ITEM_SIZE
//! \see	MAXIMUM_BUFFER_SIZE
//! \see	FILE_CLOSE_OK
//! \see	FILE_SETBUF_OK
//! \see	FILE_SEEK_OK
//! \see	FILE_EOF_FALSE
//!
////////////////////////////////////////////////////////////////////////////////

class	File
	{
	private:

////////////////////////////////////////////////////////////////////////////////
//! \enum	OperationKind
//!	Kind of I/O operations on files.
//!
////////////////////////////////////////////////////////////////////////////////

		enum	OperationKind
			{
				//! No operation performed yet.
			OPERATION_NONE,

				//! Read operation.
			OPERATION_READ,

				//! Write operation.
			OPERATION_WRITE
			};

	protected:

////////////////////////////////////////////////////////////////////////////////
//! \enum	FileKind
//!	Kind of files.
//!
////////////////////////////////////////////////////////////////////////////////

		enum	FileKind
			{
				//! Binary file.
			BINARY_FILE,

				//! Text file.
			TEXT_FILE,

				//!	Dummy value to mark the end of
				//!	enumerated type: do not use.
			LAST_FILE_TYPE
			};

	private:

//! \property	PathName
//!	Path name.
				CharString	PathName;

//! \property	FileHandle
//!	Pointer to the file, when the the file is opened, or NULL.
				FILE*		FileHandle;

//! \property	Mode
//!	Opening mode.
				OpenModeType	Mode;

//! \property	LastOperation
//!	Kind of latest operation performed on the file.
				OperationKind	LastOperation;

//! \property	NoPathName
//!	Default name for exception generation.
		static	const	CharString	NoPathName;

//! \property	OpenMode
//!	Strings for open modes.
		static	const	char*	const	OpenMode [LAST_FILE_TYPE]
							[LAST_OPEN_MODE];

//! \property	SeekMode
//!	Codes for seek modes.
		static	const	int		SeekMode [LAST_SEEK_MODE];

						File(const File& thisFile)
							noexcept = delete;

						File(File&& thisFile) noexcept =
							delete;

			const	File&		operator = (const File&
							thisFile) noexcept =
							delete;

			const	File&		operator = (File&& thisFile)
							noexcept = delete;

	protected:

				void		Open(const CharString&
							thisPathName,
							OpenModeType thisMode,
							FileKind thisType)
							throw(FatalException,
							IOException);

				bool		Open(const CharString&
							thisPathName,
							OpenModeType thisMode,
							FileKind thisType,
							std_uint BufferSize)
							throw(FatalException,
							IOException);

	public:

						File(void)
							throw(FatalException);

						~File(void)
							throw(FatalException,
							IOException);

				CharString	GetPathName(void) const
							throw(FatalException,
							IOException);

				OpenModeType	GetOpenMode(void) const
							noexcept;

				bool		IsOpened(void) const noexcept;

				void		OpenBinary(const CharString&
							thisPathName,
							OpenModeType this_Mode)
							throw(FatalException,
							IOException);

				bool		OpenBinary(const CharString&
							thisPathName,
							OpenModeType this_Mode,
							std_uint BufferSize)
							throw(FatalException,
							IOException);

				void		OpenText(const CharString&
							thisPathName,
							OpenModeType this_Mode)
							throw(FatalException,
							IOException);

				bool		OpenText(const CharString&
							thisPathName,
							OpenModeType this_Mode,
							std_uint BufferSize)
							throw(FatalException,
							IOException);

				void		OpenInput(void)
							throw(FatalException,
							IOException);

				void		OpenOutput(void)
							throw(FatalException,
							IOException);

				void		OpenError(void)
							throw(FatalException,
							IOException);

				void		Close(void)
							throw(FatalException,
							IOException);

				std_uint	Read(void* Destination,
							std_uint Size,
							std_uint Count)
							throw(FatalException,
							IOException);

		template<typename CHAR_TYPE>
				CHAR_TYPE	ReadCharacter(void)
							throw(FatalException,
							IOException);

		template<typename CHAR_TYPE>
				void		ReadLine(register
							String<CHAR_TYPE>&
							Argument)
							throw(FatalException,
							IOException);

				byte		ReadByte(void)
							throw(FatalException,
							IOException);

				void		Write(const void* Source,
							std_uint Size,
							std_uint Count)
							throw(FatalException,
							IOException);

		template<typename CHAR_TYPE>
				void		WriteCharacter(CHAR_TYPE
							Argument)
							throw(FatalException,
							IOException);

		template<typename CHAR_TYPE>
				void		WriteNumber(std_uint Value)
							throw(FatalException,
							IOException);

		template<typename CHAR_TYPE>
				void		Write(const String<CHAR_TYPE>&
							Argument)
							throw(FatalException,
							IOException);

				void		WriteByte(byte Argument)
							throw(FatalException,
							IOException);

				bool		IsEOF(void)
							throw(FatalException,
							IOException);

				void		Seek(std_sint Offset,
							SeekModeType Origin)
							throw(FatalException,
							IOException);

				std_uint	GetPosition(void) const
							throw(FatalException,
							IOException);

				void		Flush(void) const
							throw(FatalException,
							IOException);

				void		SystemFlush(void) const
							throw(FatalException,
							IOException);

				void		Lock(std_uint Size) const
							throw(FatalException,
							IOException);

				void		Unlock(std_uint Size) const
							throw(FatalException,
							IOException);

	};

}

# if	defined USE_INLINE
# include	"File.inl"
# endif

# include	"File.tpl"

# endif
