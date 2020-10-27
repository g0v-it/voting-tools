////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	24/04/2018
//!
//! \par	Function:
//!	Contains the implementation of the template functions of the
//!	io_space::File class.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	io_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read a single character.
//!
//! \tparam	CHAR_TYPE			Template parameter CHAR_TYPE is
//!						the type of the character to
//!						read. It can be either
//!						<b>char</b> or <b>wchar_t</b>.
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
//!						file was a write.
//! \throw	io_space::END_OF_FILE		If reading past last character
//!						of the file.
//!
//! \returns	CHAR_TYPE			The charecter read.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	File::ReadCharacter(void)
					throw(FatalException, IOException)
		{
		CHAR_TYPE	LocalChar;

		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));

		if (Read(static_cast<void *>(&LocalChar), sizeof(CHAR_TYPE),
			1) != 1)
			throw make_IO_exception(END_OF_FILE, PathName);
		return LocalChar;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Read up to the end of a line, storing the characters into a String. \n
//!	The line termination character will be read, but not stored into the
//!	String.
//!
//! \tparam	CHAR_TYPE			Template parameter CHAR_TYPE is
//!						the type of the character to
//!						write. It can be either char or
//!						wchar_t.
//!
//! \param	Argument			Reference to the String that
//!						upon return will contain the
//!						line.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	io_space::FILE_NOT_OPEN		If the File is not opened in
//!						read or read-write or update
//!						mode.
//! \throw	io_space::FILE_READ_ERROR	If the number of bytes read is
//!						less than expected and end of
//!						file is not reached.
//! \throw	io_space::FILE_SEEK_ERROR	If the file cannot be seeked and
//!						latest operation on the same
//!						file was a write.
//! \throw	io_space::END_OF_FILE		If reading past last character
//!						of the file.
//!
//! \returns	None.
//!
//! \note
//!	If the io_space::END_OF_FILE exception is thrown, the String contains
//!	all characters read before the end of file. If any other exception is
//!	thrown, the StringBuffer content is undefined.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	File::ReadLine(register String<CHAR_TYPE>& Argument)
				throw(FatalException, IOException)
		{
		register	CHAR_TYPE	Character;

		Argument.Clear();
		while ((Character = ReadCharacter<CHAR_TYPE>()) !=
			CharacterManager<CHAR_TYPE>::GetEOLN())
			Argument += Character;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write a single character.
//!
//! \tparam	CHAR_TYPE			Template parameter CHAR_TYPE is
//!						the type of the character to
//!						write. It can be either char or
//!						wchar_t.
//!
//! \param	Argument			Character to be written.
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

template<typename CHAR_TYPE>
	INLINE	void	File::WriteCharacter(CHAR_TYPE Argument)
				throw(FatalException, IOException)
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));

		Write(static_cast<const void *>(&Argument), sizeof(CHAR_TYPE),
			1);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write a std_uint, with the minimum possible length.
//!
//! \param	Value				Value to be written.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
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

template<typename CHAR_TYPE>
	INLINE	void	File::WriteNumber(std_uint Value)
				throw(FatalException, IOException)
		{
		String<CHAR_TYPE>	Buffer;

		Buffer.ToString(Value);
		Write(Buffer);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write a String.
//!
//! \tparam	CHAR_TYPE			Template parameter CHAR_TYPE is
//!						the template parameter of the
//!						string to write. It can be
//!						either <b>char</b> or
//!						<b>wchar_t</b>.
//!
//! \param	Argument			String to be written.
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

template<typename CHAR_TYPE>
	INLINE	void	File::Write(const String<CHAR_TYPE>& Argument)
				throw(FatalException, IOException)
		{
		Write(static_cast<const void *>(Argument.GetString()),
			sizeof(CHAR_TYPE), Argument.GetLength());
		}

}
