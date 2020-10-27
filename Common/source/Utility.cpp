////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	13/10/2018
//!
//!	Contains the declaration of the utility namespace, for documentation
//!	purposes and the definitions of common non inline utility functions.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<string.h>

# include	"Standard.h"
# include	"CommonMessage.h"
# include	"ExceptionHandler.h"
# include	"CharacterManager.h"
# include	"FileManager.h"
# include	"File.h"
# include	"Utility.h"

# if	!defined USE_INLINE
# include	"Utility.inl"
# endif

namespace	utility_space
{

using	namespace	application_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Handle command line options, removing thm from the array of parameters.
//!
//! \param	argc	Reference to the number of command line arguments.
//! \param	argv	Reference to the array of command line arguments.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	NUMERIC_ERROR_OPTION
//!
////////////////////////////////////////////////////////////////////////////////

void	HandleOptions(int& argc, char**& argv) noexcept
	{
	if (argc > 1)
		if (strcmp(argv [1], NUMERIC_ERROR_OPTION) == 0)
			{
			ExceptionHandler::GetInstance().SetNumericMessage(true);
			--argc;
			++argv;
			}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Decode a command line argument, representing an unsigned integer.
//!
//! \param	Argument				Pointer to the command
//!							line argument.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	application_space::INVALID_INTEGER	If the argument does not
//!							represent a valid
//!							integer.
//!
//! \returns	std_uint				The decoded value.
//!
////////////////////////////////////////////////////////////////////////////////

std_uint	DecodeInteger(const char* Argument)
			throw(FatalException, ApplicationException)
	{
	std_uint	Value;
	std_uint	StartIndex;
	CharString	ArgumentString(Argument);

	try
		{
		StartIndex = 0;
		ArgumentString.ToNumber(Value, StartIndex,
			ArgumentString.GetLength());
		}
	catch (...)
		{
		throw make_application_exception(INVALID_INTEGER);
		}
	if (StartIndex != ArgumentString.GetLength())
		throw make_application_exception(INVALID_INTEGER);
	return Value;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Decode a string written in hexadecimal format.
//!
//! \param	Argument				Pointer to the string.
//! \param	Buffer					Pointer to the buffer
//!							that upon return will
//!							contain the decoded
//!							string.
//! \param	Length					Number of bytes expected
//!							in the string.
//!
//! \throw	application_space::INVALID_HEX_LENGTH	If the argument length
//!							is not 2 * Length.
//! \throw	application_space::INVALID_HEX_STRING	If the argument does not
//!							represent a valid
//!							hexadecimal string.
//!
//! \returns	None.
//!
//! \note
//!	If Buffer does not point to an array of at least Length bytes, the
//!	behaviour is undefined.
//!
//! \see	HEXADECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

void	DecodeHex(register const char* Argument, register byte* Buffer,
		register std_uint Length) throw(ApplicationException)
	{
	register	char	FirstCharacter;
	register	char	SecondCharacter;

	try
		{
		for (; Length > 0; --Length)
			{
			if ((FirstCharacter = *Argument++) ==
				CharacterManager<char>::GetEOS())
				throw make_application_exception(
					INVALID_HEX_LENGTH);
			if ((SecondCharacter = *Argument++) ==
				CharacterManager<char>::GetEOS())
				throw make_application_exception(
					INVALID_HEX_LENGTH);
			*Buffer++ = CharacterManager<char>::
				CharToHexNumber(FirstCharacter) *
				HEXADECIMAL_BASE + CharacterManager<char>::
				CharToHexNumber(SecondCharacter);
			}
		}
	catch (FatalException Exc)
		{
		assert(Exc.GetExceptionKind() == ILLEGAL_CONVERSION);
		throw make_application_exception(INVALID_HEX_STRING);
		}
	if (*Argument != CharacterManager<char>::GetEOS())
		throw make_application_exception(INVALID_HEX_LENGTH);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Encode a sequence of bytes as a string in hexadecimal format.
//!
//! \param	Argument	Pointer to the sequence of bytes.
//! \param	Buffer		Pointer to the buffer that upon return will
//!				contain the encoded string.
//! \param	Length		Number of bytes in Argument.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	If Buffer does not point to an array of at least 2 * Length char, the
//!	behaviour is undefined.
//!
//! \see	HEXADECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

void	EncodeHex(register const byte* Argument, register char* Buffer,
		register std_uint Length) noexcept
	{
	for (; Length > 0; --Length)
		{
		*Buffer++ = CharacterManager<char>::
			HexNumberToChar(*Argument / HEXADECIMAL_BASE);
		*Buffer++ = CharacterManager<char>::
			HexNumberToChar(*Argument++ % HEXADECIMAL_BASE);
		}
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Create the path name of a file.
//!
//! \param	DirectoryPath			Reference to the directory path
//!						name.
//! \param	FileName			Reference to the file name.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	CharString			The path name of the file.
//!
////////////////////////////////////////////////////////////////////////////////

CharString	MakePathName(const CharString& DirectoryPath,
			const CharString& FileName) throw(FatalException)
	{
	return DirectoryPath +
		FileManager::GetInstance()->GetDirectorySeparator() +
		FileName;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout an header, centered with respect to a field of given
//!	length.
//!
//! \param	Header				The header to be written.
//! \param	Length				The length of the field.
//! \param	Offset				The offset, that is the number
//!						of characters, with respect to
//!						the beginning of the field,
//!						after which printing shall
//!						begin.
//!
//! \throw	io_space::FILE_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	std_uint			The number of characters written
//!						after the end of the field.
//!
//! \see	FILLER_FORMAT
//! \see	STRING_FORMAT
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

std_uint	PrintCenteredHeader(const CharString& Header, std_uint Length,
			std_uint Offset) throw(IOException)
	{
	std_uint	FillerLength;

	FillerLength = Length > Header.GetLength()?
		(Length - Header.GetLength()) / 2: 0;
	if (FillerLength > Offset)
		FillerLength -= Offset;
	if (FillerLength > 0)
		{
		if (printf(FILLER_FORMAT, FillerLength,
			CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		Offset += FillerLength;
		}
	if (printf(STRING_FORMAT, Header.GetLength(), Header.GetString()) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	Offset += Header.GetLength();
	if (Length > Offset)
		{
		if (printf(FILLER_FORMAT, Length - Offset,
			CharacterManager<char>::GetSpace()) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		return 0;
		}
	return Offset - Length;
	}

}
