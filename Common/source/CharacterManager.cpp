////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	07/12/2008
//!
//! \par	Function:
//!	Contains the definition of static data members of the
//!	utility_space::CharacterManager class template.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"CharacterManager.h"

# include	<ctype.h>
# include	<wctype.h>
# include	<string.h>
# include	<wchar.h>

namespace	utility_space
{

template<>
//!	CharacterManager<char>::EOSCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::EOSCharacter = '\0';

//!	CharacterManager<wchar_t>::EOSCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::EOSCharacter = L'\0';

template<>
//!	CharacterManager<char>::EOLNCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::EOLNCharacter = '\n';

//!	CharacterManager<wchar_t>::EOLNCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::EOLNCharacter = L'\n';

template<>
//!	CharacterManager<char>::EscapeCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::EscapeCharacter = '\x1B';

//!	CharacterManager<wchar_t>::EscapeCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::EscapeCharacter = L'\x1B';

template<>
//!	CharacterManager<char>::BackspaceCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::BackspaceCharacter = '\b';

//!	CharacterManager<wchar_t>::BackspaceCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::BackspaceCharacter = L'\b';

template<>
//!	CharacterManager<char>::TabulationCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::TabulationCharacter = '\t';

//!	CharacterManager<wchar_t>::TabulationCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::TabulationCharacter = L'\t';

template<>
//!	CharacterManager<char>::SpaceCharacter \n
//!	Definition valid when the template parameter is char.
const	char	CharacterManager<char>::SpaceCharacter = ' ';

//!	CharacterManager<wchar_t>::SpaceCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::SpaceCharacter = L' ';

//!	CharacterManager<char>::ZeroCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::ZeroCharacter = '0';

//!	CharacterManager<wchar_t>::ZeroCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::ZeroCharacter = L'0';

template<>
const	char	CharacterManager<char>::PlusSignCharacter = '+';

//!	CharacterManager<wchar_t>::PlusSignCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::PlusSignCharacter = L'+';

//!	CharacterManager<char>::MinusSignCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::MinusSignCharacter = '-';

//!	CharacterManager<wchar_t>::MinusSignCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::MinusSignCharacter = L'-';

//!	CharacterManager<char>::AsteriskCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::AsteriskCharacter = '*';

//!	CharacterManager<wchar_t>::AsteriskCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::AsteriskCharacter = L'*';

//!	CharacterManager<char>::SlashCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::SlashCharacter = '/';

//!	CharacterManager<wchar_t>::SlashCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::SlashCharacter = L'/';

//!	CharacterManager<char>::EqualCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::EqualCharacter = '=';

//!	CharacterManager<wchar_t>::EqualCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::EqualCharacter = L'=';

//!	CharacterManager<char>::OpenParenthesisCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::OpenParenthesisCharacter = '(';

//!	CharacterManager<wchar_t>::OpenParenthesisCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::OpenParenthesisCharacter = L'(';

//!	CharacterManager<char>::CloseParenthesisCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::CloseParenthesisCharacter = ')';

//!	CharacterManager<wchar_t>::CloseParenthesisCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::CloseParenthesisCharacter = L')';

//!	CharacterManager<char>::OpenBracketCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::OpenBracketCharacter = '[';

//!	CharacterManager<wchar_t>::OpenBracketCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::OpenBracketCharacter = L'[';

//!	CharacterManager<char>::CloseBracketCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::CloseBracketCharacter = ']';

//!	CharacterManager<wchar_t>::CloseBracketCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::CloseBracketCharacter = L']';

//!	CharacterManager<char>::UpArrowCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::UpArrowCharacter = '^';

//!	CharacterManager<wchar_t>::UpArrowCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::UpArrowCharacter = L'^';

//!	CharacterManager<char>::DecimalPointCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::DecimalPointCharacter = '.';

//!	CharacterManager<wchar_t>::DecimalPointCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::DecimalPointCharacter = L'.';

//!	CharacterManager<char>::LowercaseExponentCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::LowercaseExponentCharacter = 'e';

//!	CharacterManager<wchar_t>::LowercaseExponentCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::LowercaseExponentCharacter = L'e';

//!	CharacterManager<char>::UppercaseExponentCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::UppercaseExponentCharacter = 'E';

//!	CharacterManager<wchar_t>::UppercaseExponentCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::UppercaseExponentCharacter = L'E';

//!	CharacterManager<char>::AlertCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::AlertCharacter = '\a';

//!	CharacterManager<wchar_t>::AlertCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::AlertCharacter = L'\a';

//!	CharacterManager<char>::HexDigitCharacter \n
//!	Definition valid when the template parameter is char.
template<>
const	char	CharacterManager<char>::HexDigitCharacter
			[HEXADECIMAL_BASE + 1] = "0123456789ABCDEF";

//!	CharacterManager<wchar_t>::HexDigitCharacter \n
//!	Definition valid when the template parameter is wchar_t.
template<>
const	wchar_t	CharacterManager<wchar_t>::HexDigitCharacter
			[HEXADECIMAL_BASE + 1] = L"0123456789ABCDEF";

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if a character is a hexadecimal digit. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character	Character to be checked.
//!
//! \throw	None
//!
//! \returns	bool		true, if the character is a hexadecimal digit.
//!
//! \note
//!	Both uppercase and lowercase characters are considered as valid
//!	hexadecimal digits.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<char>::IsHexDigit(char Character) noexcept
		{
		return isxdigit(Character);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if a character is a hexadecimal digit. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character	Character to be checked.
//!
//! \throw	None
//!
//! \returns	bool		true, if the character is a hexadecimal digit.
//!
//! \note
//!	Both uppercase and lowercase characters are considered as valid
//!	hexadecimal digits.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<wchar_t>::IsHexDigit(wchar_t Character)
			noexcept
		{
		return iswxdigit(Character);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether the character is uppercase, using current locale. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character	Character to be tested.
//!
//! \throw	None.
//!
//! \returns	bool		true if the character is uppercase.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<char>::IsUpper(char Character) noexcept
	{
	return isupper(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether the character is uppercase, using current locale. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character	Character to be tested.
//!
//! \throw	None.
//!
//! \returns	bool		true if the character is uppercase.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<wchar_t>::IsUpper(wchar_t Character) noexcept
	{
	return iswupper(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether the character is lowercase, using current locale. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character	Character to be tested.
//!
//! \throw	None.
//!
//! \returns	bool		true if the character is lowercase.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<char>::IsLower(char Character) noexcept
	{
	return islower(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check whether the character is lowercase, using current locale. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character	Character to be tested.
//!
//! \throw	None.
//!
//! \returns	bool		true if the character is lowercase.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	bool	CharacterManager<wchar_t>::IsLower(wchar_t Character) noexcept
	{
	return iswlower(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the character to uppercase, using current locale. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character	Character to be converted.
//!
//! \throw	None.
//!
//! \returns	char		The converted character.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	char	CharacterManager<char>::ToUpper(char Character) noexcept
	{
	return toupper(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the character to uppercase, using current locale. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character	Character to be converted.
//!
//! \throw	None.
//!
//! \returns	char		The converted character.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	wchar_t	CharacterManager<wchar_t>::ToUpper(wchar_t Character) noexcept
	{
	return towupper(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the character to lowercase, using current locale. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character	Character to be converted.
//!
//! \throw	None.
//!
//! \returns	char		The converted character.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	char	CharacterManager<char>::ToLower(char Character) noexcept
	{
	return tolower(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the character to lowercase, using current locale. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character	Character to be converted.
//!
//! \throw	None.
//!
//! \returns	char		The converted character.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	wchar_t	CharacterManager<wchar_t>::ToLower(wchar_t Character) noexcept
	{
	return towlower(Character);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a hexadecimal character to its numeric value. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	Character				Character to be
//!							converted.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If the argument is not a
//!							valid hexadecimal digit.
//!
//! \returns	std_uint				Numeric value of the
//!							character.
//!
//! \note
//!	Both uppercase and lowercase characters are considered as valid
//!	hexadecimal digits.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	std_uint	CharacterManager<char>::CharToHexNumber(char Character)
				throw(FatalException)
		{
		const	char*	p;

		if ((p = strchr(HexDigitCharacter, ToUpper(Character))) ==
			static_cast<char*>(NULL))
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		return p - HexDigitCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a hexadecimal character to its numeric value. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	Character				Character to be
//!							converted.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If the argument is not a
//!							valid hexadecimal digit.
//!
//! \returns	std_uint				Numeric value of the
//!							character.
//!
//! \note
//!	Both uppercase and lowercase characters are considered as valid
//!	hexadecimal digits.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	std_uint	CharacterManager<wchar_t>::CharToHexNumber(wchar_t
				Character) throw(FatalException)
		{
		const	wchar_t*	p;

		if ((p = wcschr(HexDigitCharacter, ToUpper(Character))) ==
			static_cast<wchar_t*>(NULL))
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		return p - HexDigitCharacter;
		}

}
