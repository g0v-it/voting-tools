////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	07/12/2008
//!
//! \par	Function:
//!	Contains the declaration of the utility_space::CharacterManager class
//!	template.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined CHARACTER_MANAGER_H

# define	CHARACTER_MANAGER_H

# include	"FatalException.h"

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	CharacterManager
//!	Provides all characters necessary for time and number conversions.
//!
//! \tparam	CHAR_TYPE	Template parameter CHAR_TYPE is the type of the
//!				characters used. It can be either <b>char</b> or
//!				<b>wchar_t</b>.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	class	CharacterManager
	{
	private:

//! \property	EOSCharacter
//!	Contains the string termination character.
		static	const	CHAR_TYPE	EOSCharacter;

//! \property	EOLNCharacter
//!	Contains the line termination character.
		static	const	CHAR_TYPE	EOLNCharacter;

//! \property	EscapeCharacter
//!	Contains the escape character.
		static	const	CHAR_TYPE	EscapeCharacter;

//! \property	BackspaceCharacter
//!	Contains the backspace character.
		static	const	CHAR_TYPE	BackspaceCharacter;

//! \property	TabulationCharacter
//!	Contains the horizontal tabulation character.
		static	const	CHAR_TYPE	TabulationCharacter;

//! \property	SpaceCharacter
//!	Contains the space character.
		static	const	CHAR_TYPE	SpaceCharacter;

//! \property	ZeroCharacter
//!	Contains the character that represents zero.
		static	const	CHAR_TYPE	ZeroCharacter;

//! \property	PlusSignCharacter
//!	Contains the plus sign character.
		static	const	CHAR_TYPE	PlusSignCharacter;

//! \property	MinusSignCharacter
//!	Contains the minus sign character.
		static	const	CHAR_TYPE	MinusSignCharacter;

//! \property	AsteriskCharacter
//!	Contains the asterisk character.
		static	const	CHAR_TYPE	AsteriskCharacter;

//! \property	SlashCharacter
//!	Contains the slash character.
		static	const	CHAR_TYPE	SlashCharacter;

//! \property	EqualCharacter
//!	Contains the equal character.
		static	const	CHAR_TYPE	EqualCharacter;

//! \property	OpenParenthesisCharacter
//!	Contains the open parentesis character.
		static	const	CHAR_TYPE	OpenParenthesisCharacter;

//! \property	CloseParenthesisCharacter
//!	Contains the closed parenthesis character.
		static	const	CHAR_TYPE	CloseParenthesisCharacter;

//! \property	OpenBracketCharacter
//!	Contains the open braket character.
		static	const	CHAR_TYPE	OpenBracketCharacter;

//! \property	CloseBracketCharacter
//!	Contains the closed braket character.
		static	const	CHAR_TYPE	CloseBracketCharacter;

//! \property	UpArrowCharacter
//!	Contains the up arrow character.
		static	const	CHAR_TYPE	UpArrowCharacter;

//! \property	DecimalPointCharacter
//!	Contains the decimal point character.
		static	const	CHAR_TYPE	DecimalPointCharacter;

//! \property	LowercaseExponentCharacter
//!	Contains the lowercase character used to specify exponent in exponential
//!	floating point format.
		static	const	CHAR_TYPE	LowercaseExponentCharacter;

//! \property	UppercaseExponentCharacter
//!	Contains the uppercase character used to specify exponent in exponential
//!	floating point format.
		static	const	CHAR_TYPE	UppercaseExponentCharacter;

//! \property	AlertCharacter
//!	Contains the alert character.
		static	const	CHAR_TYPE	AlertCharacter;

//! \property	HexDigitCharacter
//!	Contains the characters corresponding to values from 0 to
//!	HEXADECIMAL_BASE - 1.
//!
//! \see	HEXADECIMAL_BASE
		static	const	CHAR_TYPE	HexDigitCharacter
							[HEXADECIMAL_BASE + 1];

						CharacterManager(void)
							throw(FatalException);

						CharacterManager(const
							CharacterManager&
							thisCharacterManager)
							throw(FatalException);

		const	CharacterManager&	operator = (const
							CharacterManager&
							thisCharacterManager)
							throw(FatalException);

	public:

		static	CHAR_TYPE		GetEOS(void) noexcept;

		static	CHAR_TYPE		GetEOLN(void) noexcept;

		static	CHAR_TYPE		GetEscape(void) noexcept;

		static	CHAR_TYPE		GetBackspace(void) noexcept;

		static	CHAR_TYPE		GetTabulation(void) noexcept;

		static	CHAR_TYPE		GetSpace(void) noexcept;

		static	CHAR_TYPE		GetZero(void) noexcept;

		static	CHAR_TYPE		GetPlusSign(void) noexcept;

		static	CHAR_TYPE		GetMinusSign(void) noexcept;

		static	CHAR_TYPE		GetAsterisk(void) noexcept;

		static	CHAR_TYPE		GetSlash(void) noexcept;

		static	CHAR_TYPE		GetEqual(void) noexcept;

		static	CHAR_TYPE		GetOpenParenthesis(void)
							noexcept;

		static	CHAR_TYPE		GetCloseParenthesis(void)
							noexcept;

		static	CHAR_TYPE		GetOpenBracket(void) noexcept;

		static	CHAR_TYPE		GetCloseBracket(void) noexcept;

		static	CHAR_TYPE		GetUpArrow(void) noexcept;

		static	CHAR_TYPE		GetDecimalPoint(void) noexcept;

		static	CHAR_TYPE		GetLowercaseExponent(void)
							noexcept;

		static	CHAR_TYPE		GetUppercaseExponent(void)
							noexcept;

		static	CHAR_TYPE		GetAlert(void) noexcept;

		static	bool			IsDigit(CHAR_TYPE Character)
							noexcept;

		static	bool			IsHexDigit(CHAR_TYPE Character)
							noexcept;

		static	bool			IsExponent(CHAR_TYPE Character)
							noexcept;

		static	bool			IsUpper(CHAR_TYPE Character)
							noexcept;

		static	bool			IsLower(CHAR_TYPE Character)
							noexcept;

		static	CHAR_TYPE		ToUpper(CHAR_TYPE Character)
							noexcept;

		static	CHAR_TYPE		ToLower(CHAR_TYPE Character)
							noexcept;

		static	std_uint		CharToNumber(CHAR_TYPE
							Character)
							throw(FatalException);

		static	std_uint		CharToHexNumber(CHAR_TYPE
							Character)
							throw(FatalException);

		static	CHAR_TYPE		NumberToChar(std_uint Value)
							throw(FatalException);

		static	CHAR_TYPE		HexNumberToChar(std_uint Value)
							throw(FatalException);

	};
}

# include	"CharacterManager.tpl"

# endif
