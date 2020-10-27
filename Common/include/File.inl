////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/04/2018
//!
//! \par	Function:
//!	Contains the definition of inline functions of the io_space::File class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file in the specified mode.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//! \param	thisType				File type.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and the file does not
//!							exist.
//! \throw	io_space::FILE_ALREADY_EXISTS		If open mode is
//!							OPEN_WRITE and the file
//!							already exists.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::Open(const CharString& thisPathName,
			OpenModeType thisMode, FileKind thisType)
			throw(FatalException, IOException)
	{
	if (Mode != NOT_OPEN)
		throw make_IO_exception(FILE_ALREADY_OPEN, PathName);
	if (thisMode >= NOT_OPEN)
		throw(make_IO_exception(FILE_INVALID_OPEN_MODE, thisPathName));
	if (thisPathName.IsEmpty())
		throw(make_IO_exception(FILE_INVALID_PATH_NAME, thisPathName));
	PathName = thisPathName;
	FileHandle = fopen(PathName.GetString(),
		OpenMode [thisType] [thisMode]);
	if (FileHandle == static_cast<FILE *>(NULL))
		throw make_IO_exception(FileManager::GetInstance()->
			MakeExceptionKind(errno), PathName);
	Mode = thisMode;
	LastOperation = OPERATION_NONE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file in the specified mode and allocates a buffer for
//!	the file, buffered in full buffer mode. \n
//!	This open method allows faster access to files, if reading/writing
//!	occurs in large blocks or if the physical record is larger than the
//!	default buffer size.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//! \param	thisType				File type.
//! \param	BufferSize				Size of the buffer
//!							allocated for the file;
//!							must not exceed
//!							MAXIMUM_BUFFER_SIZE,
//!							otherwise the buffer is
//!							not allocated.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If BUfferSize is greater
//!							than
//!							MAXIMUM_BUFFER_SIZE.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and file does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	bool					True, if the file is
//!							open and the buffer size
//!							is set, false if the
//!							file is open, but the
//!							buffer size is not set.
//!
//! \see	MAXIMUM_BUFFER_SIZE
//! \see	FILE_SETBUF_OK
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	File::Open(const CharString& thisPathName,
			OpenModeType thisMode, FileKind thisType,
			std_uint BufferSize) throw(FatalException, IOException)
	{
	Open(thisPathName, thisMode, thisType);
	if (BufferSize > MAXIMUM_BUFFER_SIZE)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);
	return setvbuf(FileHandle, static_cast<char *>(NULL), _IOFBF,
		static_cast<size_t>(BufferSize)) == FILE_SETBUF_OK;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	File::File(void) throw(FatalException): PathName(),
		FileHandle(static_cast<FILE *>(NULL)), Mode(NOT_OPEN),
		LastOperation(OPERATION_NONE)
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

INLINE	File::~File(void) throw(FatalException, IOException)
	{
	if (Mode != NOT_OPEN)
		{
		Close();
//		throw make_IO_exception(FILE_NOT_CLOSED, PathName);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the path name of a File.
//!
//! \throw	io_space::FILE_NOT_OPEN		If the File is not open.
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			File path name.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	CharString	File::GetPathName(void) const
				throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);
	return PathName;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the open mode.
//!
//! \throw	None.
//!
//! \returns	OpenModeType	File open mode.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	OpenModeType	File::GetOpenMode(void) const noexcept
	{
	return Mode;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether the file is opened.
//!
//! \throw	None.
//!
//! \returns	bool	true, if the file is opened.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	File::IsOpened(void) const noexcept
	{
	return Mode != NOT_OPEN;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file as binary file in the specified mode.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and file does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::OpenBinary(const CharString& thisPathName,
			OpenModeType thisMode)
			throw(FatalException, IOException)
	{
	Open(thisPathName, thisMode, BINARY_FILE);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file as binary file in the specified mode and
//!	allocates a buffer for the file, buffered in full buffer mode. \n
//!	This open method allows faster access to files, if reading/writing
//!	occurs in large blocks or if the physical record is larger than the
//!	default buffer size.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//! \param	BufferSize				Size of the buffer
//!							allocated for the file;
//!							must not exceed
//!							MAXIMUM_BUFFER_SIZE,
//!							otherwise the buffer is
//!							not allocated.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If BUfferSize is greater
//!							than
//!							MAXIMUM_BUFFER_SIZE.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and file does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	bool					True, if the file is
//!							open and the buffer size
//!							is set, false if the
//!							file is open, but the
//!							buffer size is not set.
//!
//! \see	MAXIMUM_BUFFER_SIZE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	File::OpenBinary(const CharString& thisPathName,
			OpenModeType thisMode, std_uint BufferSize)
			throw(FatalException, IOException)
	{
	return Open(thisPathName, thisMode, BINARY_FILE, BufferSize);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file as text file in the specified mode.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and file does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::OpenText(const CharString& thisPathName,
			OpenModeType thisMode)
			throw(FatalException, IOException)
	{
	Open(thisPathName, thisMode, TEXT_FILE);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Open the physical file as text file in the specified mode and allocates
//!	a buffer for the file, buffered in full buffer mode. \n
//!	This open method allows faster access to files, if reading/writing
//!	occurs in large blocks or if the physical record is larger than the
//!	default buffer size.
//!
//! \param	thisPathName				Path name of the file to
//!							be opened.
//! \param	thisMode				Open mode.
//! \param	BufferSize				Size of the buffer
//!							allocated for the file;
//!							must not exceed
//!							MAXIMUM_BUFFER_SIZE,
//!							otherwise the buffer is
//!							not allocated.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If BUfferSize is greater
//!							than
//!							MAXIMUM_BUFFER_SIZE.
//! \throw	io_space::FILE_ALREADY_OPEN		If File is already open.
//! \throw	io_space::FILE_INVALID_OPEN_MODE	If open mode is NOT_OPEN
//!							or LAST_OPEN_MODE.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If open mode is
//!							OPEN_READ or OPEN_UPDATE
//!							and file does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							file or if the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::TOO_MANY_OPEN_FILES		If trying to open too
//!							many files.
//!
//! \returns	bool					True, if the file is
//!							open and the buffer size
//!							is set, false if the
//!							file is open, but the
//!							buffer size is not set.
//!
//! \see	MAXIMUM_BUFFER_SIZE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	File::OpenText(const CharString& thisPathName,
			OpenModeType thisMode, std_uint BufferSize)
			throw(FatalException, IOException)
	{
	return Open(thisPathName, thisMode, TEXT_FILE, BufferSize);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Connect the File to standard intput. \n
//!	The file is considered opened as text file in read mode.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	io_space::FILE_ALREADY_OPEN	If File is already open.
//!
//! \returns	None.
//!
//! \note
//!	stdin must be already open as text file in read mode when the function
//!	is called, otherwise I/O operations on this File will fail.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::OpenInput(void) throw(FatalException, IOException)
	{
	if (Mode != NOT_OPEN)
		throw make_IO_exception(FILE_ALREADY_OPEN, PathName);
	PathName = CharString(DEFAULT_STDIN_PATHNAME);
	FileHandle = stdin;
	Mode = OPEN_READ;
	LastOperation = OPERATION_READ;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Connect the File to standard output. \n
//!	The file is considered opened as text file in write mode.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	io_space::FILE_ALREADY_OPEN	If File is already open.
//!
//! \returns	None.
//!
//! \note
//!	stdout must be already open as text file in write mode when the function
//!	is called, otherwise I/O operations on this File will fail.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::OpenOutput(void) throw(FatalException, IOException)
	{
	if (Mode != NOT_OPEN)
		throw make_IO_exception(FILE_ALREADY_OPEN, PathName);
	PathName = CharString(DEFAULT_STDOUT_PATHNAME);
	FileHandle = stdout;
	Mode = OPEN_WRITE;
	LastOperation = OPERATION_WRITE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Connect the File to standard error. \n
//!	The file is considered opened as text file in write mode.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	io_space::FILE_ALREADY_OPEN	If File is already open.
//!
//! \returns	None.
//!
//! \note
//!	stderr must be already open as text file in write mode when the function
//!	is called, otherwise I/O operations on this File will fail.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::OpenError(void) throw(FatalException, IOException)
	{
	if (Mode != NOT_OPEN)
		throw make_IO_exception(FILE_ALREADY_OPEN, PathName);
	PathName = CharString(DEFAULT_STDERR_PATHNAME);
	FileHandle = stderr;
	Mode = OPEN_WRITE;
	LastOperation = OPERATION_WRITE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Closes a file.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the file is not open.
//! \throw	io_space::FILE_CLOSE_ERROR	If an error occurs while closing
//!						the file.
//!
//! \returns	None.
//!
//! \see	FILE_CLOSE_OK
//!
//! \note
//!	If the file is standard input, standard output or standard error, the
//!	File object is closed, but the physical file is not actually closed.
//!
//! \note
//!	The io_space::FILE_CLOSE_ERROR exception could be thrown when the File
//!	is closed while processing another exception, thrown but not yet caught.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::Close(void) throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	assert(FileHandle != static_cast<FILE *>(NULL));

	if (FileHandle != stdin && FileHandle != stdout && FileHandle != stderr)
		if (fclose(FileHandle) != FILE_CLOSE_OK)
			throw make_IO_exception(FILE_CLOSE_ERROR, PathName);
	FileHandle = static_cast<FILE *>(NULL);
	Mode = NOT_OPEN;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read up to Count items of Size bytes and stores them in Destination.
//!
//! \param	Destination			Storage location for data.
//! \param	Size				Item size in bytes; must not
//!						exceed MAXIMUM_ITEM_SIZE.
//! \param	Count				Maximum number of items to be
//!						read; must not exceeed
//!						MAXIMUM_ITEM_SIZE.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If Size or Count are greater
//!						than MAXIMUM_ITEM_SIZE.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened in
//!						read or read-write or update
//!						mode.
//! \throw	io_space::FILE_READ_ERROR	If the number of bytes read is
//!						less than expected and end of
//!						file is not reached.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked and
//!						latest operation on the same
///						file was a write.
//!
//! \returns	std_uint			The number of full items
//!						actually read, which may be less
//!						than Count if the end of the
//!						file is encountered before
//!						having read Count items.
//!
//! \note
//!	If Destination is not a valid pointer to an area of at least
//!	Count * Size bytes, the behaviour is undefined.
//!
//! \see	MAXIMUM_ITEM_SIZE
//! \see	FILE_SEEK_OK
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	File::Read(void* Destination, std_uint Size,
				std_uint Count)
				throw(FatalException, IOException)
	{
	size_t	ObjectsRead;

	switch (Mode)
		{
		case OPEN_READ:
		case OPEN_READ_WRITE:
		case OPEN_UPDATE:
			break;
		case OPEN_WRITE:
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		default:
			throw make_IO_exception(FILE_NOT_OPEN, NoPathName);
		}
	if (Size > MAXIMUM_ITEM_SIZE || Count > MAXIMUM_ITEM_SIZE)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);

	assert(FileHandle != static_cast<FILE *>(NULL));

	if (LastOperation == OPERATION_WRITE)
		if (fseek(FileHandle, 0, SEEK_CUR) != FILE_SEEK_OK)
			throw make_IO_exception(FILE_SEEK_ERROR, PathName);
	if ((ObjectsRead = fread(Destination, static_cast<size_t>(Size),
		static_cast<size_t>(Count), FileHandle)) <
		static_cast<size_t>(Count))
		if (!feof(FileHandle))
			throw make_IO_exception(FILE_READ_ERROR, PathName);
	LastOperation = OPERATION_READ;
	return static_cast<std_uint>(ObjectsRead);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read a single byte.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened in
//!						read or read-write or update
//!						mode.
//! \throw	io_space::FILE_READ_ERROR	If the number of bytes read is
//!						less than expected and end of
//!						file is not reached.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked and
//!						latest operation on the same
///						file was a write.
//!
//! \returns	byte				Byte read from file.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	byte	File::ReadByte(void) throw(FatalException, IOException)
	{
	byte	LocalBuffer;

	if (Read(static_cast<void *>(&LocalBuffer), 1, 1) != 1)
		throw make_IO_exception(END_OF_FILE, PathName);
	return LocalBuffer;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write up to Count items of Size bytes from Source.
//!
//! \param	Source				Storage location for data.
//! \param	Size				Item size in bytes; must not
//!						exceed MAXIMUM_ITEM_SIZE.
//! \param	Count				Maximum number of items to be
//!						written; must not exceeed
//!						MAXIMUM_ITEM_SIZE.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If Size or Count are greater
//!						than MAXIMUM_ITEM_SIZE.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened in
//!						write or read-write or update
//!						mode.
//! \throw	io_space::FILE_WRITE_ERROR	If an error occurs while
//!						writing.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked and
//!						latest operation on the same
//!						file was a read.
//!
//! \returns	None.
//!
//! \note
//!	If Source is not a valid pointer to an area of at least Count * Size
//!	bytes, the behaviour is undefined.
//!
//! \see	MAXIMUM_ITEM_SIZE
//! \see	FILE_SEEK_OK
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::Write(const void* Source, std_uint Size, std_uint Count)
			throw(FatalException, IOException)
	{
	size_t	ObjectsWritten;

	switch (Mode)
		{
		case OPEN_WRITE:
		case OPEN_READ_WRITE:
		case OPEN_UPDATE:
			break;
		case OPEN_READ:
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		default:
			throw make_IO_exception(FILE_NOT_OPEN, NoPathName);
		}
	if (Size > MAXIMUM_ITEM_SIZE || Count > MAXIMUM_ITEM_SIZE)
		throw make_fatal_exception(ILLEGAL_ARGUMENT);

	assert(FileHandle != static_cast<FILE *>(NULL));

	if (LastOperation == OPERATION_READ)
		if (fseek(FileHandle, 0, SEEK_CUR) != FILE_SEEK_OK)
			throw make_IO_exception(FILE_SEEK_ERROR, PathName);
	if ((ObjectsWritten = fwrite(static_cast<const void *>(Source),
		static_cast<size_t>(Size), static_cast<size_t>(Count),
		FileHandle)) < static_cast<size_t>(Count))
		throw make_IO_exception(FILE_WRITE_ERROR, PathName);
	LastOperation = OPERATION_WRITE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write a single byte.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened in
//!						write or read-write or update
//!						mode.
//! \throw	io_space::FILE_WRITE_ERROR	If an error occurs while
//!						writing.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked and
//!						latest operation on the same
//!						file was a read.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::WriteByte(byte Argument)
			throw(FatalException, IOException)
	{
	Write(static_cast<const void *>(&Argument), 1, 1);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Tests the end-of-file indicator for the file.
//!
//! \warning	The end-of-file indicator is set only after a read operation
//!		fails and it is reset by Write or Seek.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//!
//! \returns	bool				true, if the EOF indicator is
//!						set.
//!
//! \see	FILE_EOF_FALSE
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	bool	File::IsEOF(void) throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	assert(FileHandle != static_cast<FILE *>(NULL));

	return feof(FileHandle) != FILE_EOF_FALSE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Moves the file pointer to a specified location.
//!
//! \param	Offset				Number of bytes from Origin.
//! \param	Origin				Initial position; must be one
//!						of the following values:
//!						- SEEK_CUR: current position,
//!						- SEEK_END: end of file,
//!						- SEEK_SET: beginning of file.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	utility_space::ILLEGAL_ARGUMENT	if Origin has an illegal value
//!						or if the seek point is before
//!						the beginning of the file.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//! \throw	io_space::FILE_SEEK_ERROR	If the File cannot be seeked.
//!
//! \returns	None.
//!
//! \see	FILE_SEEK_OK
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::Seek(std_sint Offset, SeekModeType Origin)
			throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	assert(FileHandle != static_cast<FILE *>(NULL));

	switch (Origin)
		{
		case FILE_SEEK_CUR:
		case FILE_SEEK_SET:
		case FILE_SEEK_END:
			break;
		default:
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		}
	if (fseek(FileHandle, static_cast<long>(Offset),
		SeekMode [static_cast<unsigned int>(Origin)]) != FILE_SEEK_OK)
		throw make_IO_exception(FILE_SEEK_ERROR, PathName);
	LastOperation = OPERATION_NONE;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get current file position.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked.
//!
//! \returns	std_uint			Current file position (offset
//!						from the beginning of the file).
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	std_uint	File::GetPosition(void) const
				throw(FatalException, IOException)
	{
	long	value;

	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	assert(FileHandle != static_cast<FILE *>(NULL));

	if ((value = ftell(FileHandle)) < 0)
		throw make_IO_exception(FILE_SEEK_ERROR, PathName);
	return static_cast<std_uint>(value);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Flush the user space buffer of the file. \n
//!	If the file has been used for output, the function forces a write of all
//!	user-space buffered data. If the file has been used for input, it
//!	discards any buffered data that has been fetched from the underlying
//!	file, but has not been read.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//!
//! \returns	None.
//!
//! \note
//!	The function only flushes the user-space buffers, but does not guarantee
//!	that data are physically writte, on a device.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::Flush(void) const throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	ignore_value(fflush(FileHandle));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Flush the buffers of the file to the actual device.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails when
//!						creating an exception.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened.
//! \throw	io_space::FILE_WRITE_ERROR	If an error occurs while writing
//!						data or if the File is a special
//!						device which does not support
//!						synchronization.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

INLINE	void	File::SystemFlush(void) const throw(FatalException, IOException)
	{
	if (Mode == NOT_OPEN)
		throw make_IO_exception(FILE_NOT_OPEN, NoPathName);

	ignore_value(fflush(FileHandle));
	FileManager::GetInstance()->SystemFlush(fileno(FileHandle), PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Lock a given number of bytes, from current position.
//!
//! \param	Size					Number of bytes to lock.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the file is not
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

void	File::Lock(std_uint Size) const throw(FatalException, IOException)
	{
	switch (Mode)
		{
		case OPEN_WRITE:
		case OPEN_READ_WRITE:
		case OPEN_UPDATE:
			break;
		default:
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		}
	FileManager::GetInstance()->Lock(fileno(FileHandle), Size, PathName);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Unlock a given number of bytes, from current position.
//!
//! \param	Size					Number of bytes to lock.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails when creating an
//!							exception.
//! \throw	io_space::FILE_NOT_OPEN			If the file is not
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

void	File::Unlock(std_uint Size) const throw(FatalException, IOException)
	{
	switch (Mode)
		{
		case OPEN_WRITE:
		case OPEN_READ_WRITE:
		case OPEN_UPDATE:
			break;
		default:
			throw make_IO_exception(FILE_NOT_OPEN, PathName);
		}
	FileManager::GetInstance()->Unlock(fileno(FileHandle), Size, PathName);
	}

}
