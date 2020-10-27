////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	07/12/2008
//!
//! \par	Function:
//!	Contains the implementation of the utility_space::CharacterManager class
//!	template.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	utility_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor. \n
//!	The purpose of its definition (as private) is to forbid instantiation of
//!	CharacterManager objects outside the class.
//!
//! \throw	utility_space::ILLEGAL_FUNCTION_CALL	If called.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CharacterManager<CHAR_TYPE>::CharacterManager(void)
			throw(FatalException)
		{
		throw make_fatal_exception(ILLEGAL_FUNCTION_CALL);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor. \n
//!	The purpose of its definition (as private) is to forbid instantiation of
//!	CharacterManager objects through copying.
//!
//! \param	thisCharacterManager			Reference to source
//!							CharacterManager object.
//!
//! \throw	utility_space::ILLEGAL_FUNCTION_CALL	If called.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CharacterManager<CHAR_TYPE>::CharacterManager(const
			CharacterManager& thisCharacterManager)
			throw(FatalException)
		{
		throw make_fatal_exception(ILLEGAL_FUNCTION_CALL);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Assignment operator. \n
//!	The purpose of its definition (as private) is to forbid assignment of
//!	CharacterManager objects.
//!
//! \param	thisCharacterManager			Reference to source
//!							CharacterManager object.
//!
//! \throw	utility_space::ILLEGAL_FUNCTION_CALL	If called.
//!
//! \returns	const	CharacterManager&		Reference to the
//!							assigned
//!							CharacterManager object.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	CharacterManager<CHAR_TYPE>&
				CharacterManager<CHAR_TYPE>::operator = (const
				CharacterManager& thisCharacterManager)
				throw(FatalException)
		{
		throw make_fatal_exception(ILLEGAL_FUNCTION_CALL);

			// Dummy return statement, to avoid compiler warning.
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the string termination character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The string termination character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetEOS(void)
					noexcept
		{
		return EOSCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the line termination character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The line termination character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetEOLN(void)
					noexcept
		{
		return EOLNCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the escape character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The escape character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetEscape(void)
					noexcept
		{
		return EscapeCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the backspace character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The backspace character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetBackspace(void)
					noexcept
		{
		return BackspaceCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the horizontal tabulation character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The horizontal tabulation character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetTabulation(void)
					noexcept
		{
		return TabulationCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the space character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The space character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetSpace(void)
					noexcept
		{
		return SpaceCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents zero.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The zero character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetZero(void)
					noexcept
		{
		return ZeroCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the plus sign.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The plus sign character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetPlusSign(void)
					noexcept
		{
		return PlusSignCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the minus sign.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The minus sign character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetMinusSign(void)
					noexcept
		{
		return MinusSignCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the asterisk.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The asterisk character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetAsterisk(void)
					noexcept
		{
		return AsteriskCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the slash.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The slash character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetSlash(void)
					noexcept
		{
		return SlashCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the equal.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The equal character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetEqual(void)
					noexcept
		{
		return EqualCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the open parenthesis.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The open parenthesis character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetOpenParenthesis(void) noexcept
		{
		return OpenParenthesisCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the closed parenthesis.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The closed parenthesis character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetCloseParenthesis(void) noexcept
		{
		return CloseParenthesisCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the open square bracket.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The open square bracket character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetOpenBracket(void) noexcept
		{
		return OpenBracketCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the closed square bracket.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The closed square bracket character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetCloseBracket(void) noexcept
		{
		return CloseBracketCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the up arrow.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The up arrow character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetUpArrow(void)
					noexcept
		{
		return UpArrowCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the character that represents the decimal point.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The decimal point character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetDecimalPoint(void) noexcept
		{
		return DecimalPointCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the lowercase character used to specify exponent in exponential
//!	floating point format.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The the lowercase character used to specify
//!				exponent in exponential floating point format.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetLowercaseExponent(void) noexcept
		{
		return LowercaseExponentCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the uppercase character used to specify exponent in exponential
//!	floating point format.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The the uppercase character used to specify
//!				exponent in exponential floating point format.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					GetUppercaseExponent(void) noexcept
		{
		return UppercaseExponentCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the alert character.
//!
//! \throw	None.
//!
//! \returns	CHAR_TYPE	The alert character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::GetAlert(void)
					noexcept
		{
		return AlertCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if a character is a digit. \n
//!	Only 10 consecutive characters, starting from zero, are considered as
//!	digits
//!
//! \param	Character	Character to be checked.
//!
//! \throw	None
//!
//! \returns	bool		true, if the character is a digit.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	CharacterManager<CHAR_TYPE>::IsDigit(CHAR_TYPE
				Character) noexcept
		{
		return Character >= GetZero() &&
			Character <= GetZero() + DECIMAL_BASE - 1;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Check if a character is a character used to specify exponent in
//!	exponential floating point format.
//!
//! \param	Character	Character to be checked.
//!
//! \throw	None
//!
//! \returns	bool		true, if the character is a character used to
//!				specify exponent in exponential floating point
//!				format.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	CharacterManager<CHAR_TYPE>::IsExponent(CHAR_TYPE
				Character) noexcept
		{
		return Character == LowercaseExponentCharacter ||
			Character == UppercaseExponentCharacter;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a character to its numeric value.
//!	Only 10 consecutive characters, starting from zero, are considered as
//!	digits.
//!
//! \param	Character				Character to be
//!							converted.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If the argument is not a
//!							digit.
//!
//! \returns	std_uint				Numeric value of the
//!							character.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	std_uint	CharacterManager<CHAR_TYPE>::
					CharToNumber(CHAR_TYPE Character)
					throw(FatalException)
		{
		if (!IsDigit(Character))
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		return static_cast<std_uint>(Character - GetZero());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a number to the corresponding character.
//!
//! \param	Value					Value to be converted.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If the argument is not
//!							less than DECIMAL_BASE.
//!
//! \returns	std_uint				Character corresponding
//!							to the argument.
//!
//! \see	DECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					NumberToChar(std_uint Value)
					throw(FatalException)
		{
		if (Value >= DECIMAL_BASE)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		return HexDigitCharacter [Value];
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a number up to HEXADECIMAL_BASE - 1 to the corresponding
//!	character.
//!
//! \param	Value					Value to be converted.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If the argument is not
//!							less than
//!							HEXADECIMAL_BASE.
//!
//! \returns	CHAR_TYPE				Character corresponding
//!							to the argument.
//!
//! \see	HEXADECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CHAR_TYPE	CharacterManager<CHAR_TYPE>::
					HexNumberToChar(std_uint Value)
					throw(FatalException)
		{
		if (Value >= HEXADECIMAL_BASE)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		return HexDigitCharacter [Value];
		}

}
