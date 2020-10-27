////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	09/04/2018
//!
//! \par	Function:
//!	Contains the implementation of the data_structure_space::String class
//!	template.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	data_structure_space
{

	using	namespace	utility_space;
	using	namespace	numeric_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Append a character to the String.
//!
//! \param	Character			Character element.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None:
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::Append(CHAR_TYPE Character)
				throw(FatalException)
		{
		Vector<CHAR_TYPE>::Replace(Character, GetLength());
		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert an unsigned number to string, with a given minimum length and
//!	append it to the String.
//!
//! \param	Value				The number to be converted.
//! \param	MinimumLength			The minimum string length: the
//!						converted number is padded to
//!						this length, if it is shorter.
//! \param	ZeroFilled			If true, the padding character
//!						is a zero character, otherwise
//!						it is blank.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None.
//!
//! \note	The string must not be terminated with EOS; the converted number
//!		is appended at the end of the Vector. After the conversion, the
//!		String is terminated with EOS.
//!
//! \see	DECIMAL_BASE
//! \see	STD_UINT_MAX_DIGITS
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::AppendNumber(register std_uint Value,
				std_uint MinimumLength, bool ZeroFilled)
				throw(FatalException)
		{
		register	std_uint	Digits;
				CHAR_TYPE	Buffer [STD_UINT_MAX_DIGITS];

		if (Value == 0)
			{
			Buffer [0] =
				CharacterManager<CHAR_TYPE>::NumberToChar(0);
			Digits = 1;
			}
		else
			{
			Digits = 0;
			for (; Value > 0; Value /= DECIMAL_BASE)
				Buffer [Digits++] =
					CharacterManager<CHAR_TYPE>::
					NumberToChar(Value % DECIMAL_BASE);
			}
		if (Digits < MinimumLength)
			Vector<CHAR_TYPE>::Insert(ZeroFilled?
				CharacterManager<CHAR_TYPE>::GetZero():
				CharacterManager<CHAR_TYPE>::GetSpace(), 0,
				MinimumLength - Digits);
		while (Digits > 0)
			Vector<CHAR_TYPE>::Append(Buffer [--Digits]);
		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor; creates an empty string.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>::String(void) throw(FatalException):
			Vector<CHAR_TYPE>(1)
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));

		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Single argument constructor; creates an empty String with a given
//!	initial size, that is, large enough to contain Size characters.
//!
//! \param	Size				Initial size.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>::String(std_uint Size) throw(FatalException):
			Vector<CHAR_TYPE>(Size + 1)
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));

		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Single argument constructor; creates a String from an array of
//!	characters.
//!
//! \warning	If the array is not zero terminated, the behaviour is undefined.
//!
//! \param	SourceString			Array of characters.
//!
//! \throw	utility_space::INVALID_POINTER	If the pointer is NULL.
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>::String(register const CHAR_TYPE*
			SourceString) throw(FatalException): Vector<CHAR_TYPE>()
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));

		if (SourceString == static_cast<CHAR_TYPE *>(NULL))
			throw make_fatal_exception(INVALID_POINTER);

		Vector<CHAR_TYPE>::Resize(ComputeLength(SourceString) + 1);
		while (*SourceString != CharacterManager<CHAR_TYPE>::GetEOS())
			Vector<CHAR_TYPE>::Append(*SourceString++);
		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor.
//!
//! \param	thisString			String object.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>::String(const String<CHAR_TYPE>& thisString)
			throw(FatalException):
			Vector<CHAR_TYPE>(thisString)
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move constructor.
//!
//! \param	thisString			String object.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>::String(String<CHAR_TYPE>&& thisString)
			throw(FatalException):
			Vector<CHAR_TYPE>(thisString)
		{
		assert(typeid(CHAR_TYPE) == typeid(char) ||
			typeid(CHAR_TYPE) == typeid(wchar_t));
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Checks whether a String is empty.
//!
//! \throw	None.
//!
//! \returns	bool	true if the String is empty.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool String<CHAR_TYPE>::IsEmpty() const noexcept
		{
		assert(Vector<CHAR_TYPE>::GetStore()
			[Vector<CHAR_TYPE>::GetPresent() - 1] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return Vector<CHAR_TYPE>::GetPresent() == 1;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the length of the string.
//!
//! \throw	None.
//!
//! \returns	std_uint	Length of the string.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	std_uint String<CHAR_TYPE>::GetLength() const noexcept
		{
		assert(Vector<CHAR_TYPE>::GetStore()
			[Vector<CHAR_TYPE>::GetPresent() - 1] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return Vector<CHAR_TYPE>::GetPresent() - 1;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Delete all characters from the String, leaving it empty.
//!
//! \throw	None.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<class CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::Clear(void) noexcept
		{
		assert(Vector<CHAR_TYPE>::GetStore() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		Vector<CHAR_TYPE>::Clear();
		Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
			GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return a pointer to the (zero terminated) array of character. \n
//!	The pointer is intended for immediate use and shall not be stored, as
//!	it will be no longer valid after most operations on the String.
//!
//! \throw	None.
//!
//! \returns	const	CHAR_TYPE*	Pointer to the array of characters.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	CHAR_TYPE*	String<CHAR_TYPE>::GetString(void) const
						noexcept
		{
		assert(Vector<CHAR_TYPE>::GetStore() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return Vector<CHAR_TYPE>::GetStore();
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Assignment operator.
//!
//! \param	Argument			String to be assigned.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	const	String<CHAR_TYPE>&	Reference to the assigned
//!						object.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	String<CHAR_TYPE>&	String<CHAR_TYPE>::
							operator = (const
							String& Argument)
							throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		*static_cast<Vector<CHAR_TYPE> *>(this) =
			static_cast<const Vector<CHAR_TYPE> &>(Argument);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move assignment operator.
//!
//! \param	Argument			String to be assigned.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	const	String<CHAR_TYPE>&	Reference to the assigned
//!						object.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	String<CHAR_TYPE>&	String<CHAR_TYPE>::
							operator = (String&&
							Argument)
							throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		*static_cast<Vector<CHAR_TYPE> *>(this) =
			static_cast<Vector<CHAR_TYPE> &>(Argument);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Subscript operator, used to acces the characters of a String. \n
//!	The string terminator can be accessed using this operator.
//!
//! \param	Index					Index of the element to
//!							be retrieved. Valid
//!							range is
//!							[0 .. GetLength()].
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the index is greater
//!							than the String length.
//!
//! \returns	const	CHAR_TYPE&			Reference to the
//!							selected element.
//!
////////////////////////////////////////////////////////////////////////////////

template<class CHAR_TYPE>
	INLINE	const	CHAR_TYPE&	String<CHAR_TYPE>::
						operator [] (std_uint Index)
						const throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		return Vector<CHAR_TYPE>::operator [] (Index);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator ==.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if the object is equal to Operand.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator == (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) == COMPARE_EQUAL;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator !=.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if the object is not equal to Operand.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator != (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) != COMPARE_EQUAL;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator >.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if the object lexicographycally follows Operand.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator > (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) == COMPARE_GREATER;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator <.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if Operand lexicographycally follows the object.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator < (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) == COMPARE_LESS;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator >=.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if the object lexicographycally follows Operand of
//!			if the object is equal to Operand.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator >= (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) != COMPARE_LESS;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Comparision operator <=.
//!
//! \param	Operand	String that has to be compared to the object.
//!
//! \throw	None.
//!
//! \returns	bool	True if Operand lexicographycally follows the object or
//!			if the object is equal to Operand.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	bool	String<CHAR_TYPE>::operator <= (const String& Operand)
				const noexcept
		{
		return Compare(*this, Operand) != COMPARE_GREATER;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Operator + overloading: concatenates a character to the String
//!	object. \n
//!	If the character is the string terminator, an exception is thrown.
//!
//! \param	Argument			Character to be concatenated.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the character is the string
//!						terminator.
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	String<CHAR_TYPE>		Modified String.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>	String<CHAR_TYPE>::operator +
						(CHAR_TYPE Argument) const
						throw(FatalException)
		{
			// Allocate a string of the correct size, to avoid
			// resizing it
		String<CHAR_TYPE>	TempString(GetLength() + 2);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		if (Argument == CharacterManager<CHAR_TYPE>::GetEOS())
			throw make_fatal_exception(ILLEGAL_ARGUMENT);

			// Remove EOS from end of TempString
		TempString.Vector<CHAR_TYPE>::Clear();
		TempString.Vector<CHAR_TYPE>::Append(*this);
		TempString.Append(Argument);
		return TempString;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Operator += overloading: concatenates a character to the String object,
//!	modifying the object itself. \n
//!	If the character is the string terminator, an exception is thrown.
//!
//! \param	Argument			Character to be concatenated.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the character is the string
//!						terminator.
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	const	String<CHAR_TYPE>	Reference to the modified
//!						String.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	String<CHAR_TYPE>&	String<CHAR_TYPE>::
						operator += (CHAR_TYPE Argument)
						throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		if (Argument == CharacterManager<CHAR_TYPE>::GetEOS())
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		Append(Argument);
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Operator + overloading: concatenates a String to the object.
//!
//! \param	Argument			String to be concatenated.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	String<CHAR_TYPE>		Modified String.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	String<CHAR_TYPE>	String<CHAR_TYPE>::operator +
						(const String& Argument) const
						throw(FatalException)
		{
			// Allocate a string of the correct size, to avoid
			// resizing it
		String<CHAR_TYPE>	TempString(GetLength() +
						Argument.GetLength() + 1);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		assert(Argument.GetString() [Argument.GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

			// Remove EOS from end of TempString
		TempString.Vector<CHAR_TYPE>::Clear();
		TempString.Vector<CHAR_TYPE>::Append(*this);
		TempString.Vector<CHAR_TYPE>::RemoveRear(1);

			// The string argument already ends with EOS, so no need
			// for appending it again.
		TempString.Vector<CHAR_TYPE>::Append(Argument);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		return TempString;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Operator += overloading: concatenates a String to the object.
//!
//! \param	Argument			String to be concatenated.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	const	String<CHAR_TYPE>&	Reference to the modified
//!						String.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	const	String<CHAR_TYPE>&	String<CHAR_TYPE>::
							operator += (const
							String& Argument)
							throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		assert(Argument.GetString() [Argument.GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

			// Cannot simply call Append, because it does not work
			// properly when appending an object to itself.
		if (this == &Argument)
			return *this = *this + Argument;
		Vector<CHAR_TYPE>::RemoveRear(1);

			// The string argument already ends with EOS, so no need
			// for appending it again.
		Vector<CHAR_TYPE>::Append(Argument);
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compare the object to string, returning the comparison result.
//!
//! \param	Argument	String to be compared.
//!
//! \throw	None.
//!
//! \returns	CompareType	The comparison result:
//!				- COMPARE_EQUAL, if the object and the string
//!					are equal;
//!				- COMPARE_GREATER, if the object is lexically
//!					greater;
//!				- COMPARE_LESS, if the object is lexically less.
//!				.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	CompareType	String<CHAR_TYPE>::Compare(const String&
					Argument) const noexcept
		{
		return Compare(*this, Argument);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Removes the specified number of characters from the end.
//!
//! \param	NumCharacters				Number of elements to be
//!							removed. Valid range is
//!							[0 .. GetLength()].
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If NumElements is
//!							greater than the number
//!							of present characters.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::RemoveRear(std_uint NumCharacters)
				throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		if (NumCharacters > GetLength())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);
		Vector<CHAR_TYPE>::Remove(GetLength() - NumCharacters,
			NumCharacters);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Removes all characters from a specified index to the end.
//!
//! \param	StartIndex				Index from which the
//!							characters shall be
//!							removed. Valid range is
//!							[0 .. GetLength()].
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If StartIndex is greater
//!							than the number of
//!							present characters.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::RemoveFrom(std_uint StartIndex)
				throw(FatalException)
		{
		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());

		if (StartIndex > GetLength())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);
		Vector<CHAR_TYPE>::Remove(StartIndex, GetLength() - StartIndex);

		assert(GetString() [GetLength()] ==
			CharacterManager<CHAR_TYPE>::GetEOS());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a part of a String to a std_uint, starting at a given position
//!	and converting at most a given number of characters. \n
//!	The part of the string starting at StartIndex is converted, up to
//!	MaximumLength characters or to first non numeric character.
//!
//! \param	Value					The reference to the
//!							variable that upon
//!							return will contain the
//!							number.
//! \param	StartIndex				Starting index for the
//!							conversion. Valid range
//!							is
//!							[0 .. GetLength() - 1].
//!							On exit it is updated
//!							with the index of first
//!							not converted character.
//! \param	MaximumLength				The maximum length, that
//!							is, the maximum number
//!							of characters to be
//!							converted.
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If StartIndex is not
//!							smaller than the string
//!							length.
//! \throw	utility_space::ILLEGAL_CONVERSION	If no digit is
//!							converted, because the
//!							String is empty or it
//!							does not start with a
//!							digit or MaximumLength
//!							is zero.
//! \throw	numeric_space::NUMERIC_OVERFLOW		If the converted string
//!							cannot be represented as
//!							a std_uint.
//!
//! \returns	None.
//!
//! \note
//!	If the function throws an exception, the value of Value and StartIndex
//!	are undefined.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	void	String<CHAR_TYPE>::ToNumber(register std_uint& Value,
			std_uint& StartIndex, register std_uint MaximumLength)
			const throw(FatalException, NumericException)
		{
		register	std_uint	i;
		register	std_uint	n;

		if (StartIndex >= GetLength())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);
		MaximumLength += StartIndex;
		if (MaximumLength > GetLength())
			MaximumLength = GetLength();
		Value = 0;
		for (i = StartIndex; i < MaximumLength; ++i)
			{
			if (!CharacterManager<CHAR_TYPE>::IsDigit((*this) [i]))
				break;
			n = CharacterManager<CHAR_TYPE>::
				CharToNumber((*this) [i]);
			if (Value > (STD_UINT_MAX - n) / DECIMAL_BASE)
				throw make_numeric_exception(NUMERIC_OVERFLOW);
			Value = Value * DECIMAL_BASE + n;
			}
		if (i == StartIndex)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		StartIndex = i;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a part of a String to a std_sint, starting at a given position
//!	and converting at most a given number of characters. \n
//!	The part of the string starting at StartIndex is converted, up to
//!	MaximumLength characters or to first non numeric character. \n
//!	An optional sign is accepted before first digit; if it is not present,
//!	it is assumed to be positive.
//!
//! \param	Value					The reference to the
//!							variable that upon
//!							return will contain the
//!							number.
//! \param	StartIndex				Starting index for the
//!							conversion. Valid range
//!							is
//!							[0 .. GetLength() - 1].
//!							On exit it is updated
//!							with the index of first
//!							not converted character.
//! \param	MaximumLength				The maximum length, that
//!							is, the maximum number
//!							of characters to be
//!							converted.
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If StartIndex is not
//!							smaller than the String
//!							length.
//! \throw	utility_space::ILLEGAL_CONVERSION	If no digit is
//!							converted, because the
//!							String is empty or it
//!							does not start with a
//!							digit, after an optional
//!							sign, or MaximumLength
//!							is zero or it is one
//!							but a sign is present.
//! \throw	numeric_space::NUMERIC_OVERFLOW		If the converted string
//!							cannot be represented as
//!							a std_sint.
//!
//! \returns	None.
//!
//! \note
//!	If the function throws an exception, the value of Value and StartIndex
//!	are undefined.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	void	String<CHAR_TYPE>::ToNumber(std_sint& Value,
			std_uint& StartIndex, std_uint MaximumLength) const
			throw(FatalException, NumericException)
		{
		std_uint	LocalValue;
		bool		Positive;

		if (StartIndex >= GetLength())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);
		if (MaximumLength == 0)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		Positive = true;
		if ((*this) [StartIndex] ==
			CharacterManager<CHAR_TYPE>::GetPlusSign())
			{
			++StartIndex;
			--MaximumLength;
			}
		else
			if ((*this) [StartIndex] ==
				CharacterManager<CHAR_TYPE>::GetMinusSign())
			{
			Positive = false;
			++StartIndex;
			--MaximumLength;
			}
		ToNumber(LocalValue, StartIndex, MaximumLength);
		if (Positive)
			{
			if (LocalValue > STD_SINT_MAX)
				throw make_numeric_exception(NUMERIC_OVERFLOW);
			Value = LocalValue;
			return;
			}

			// Modular properties of unsigned arithmetic ensure that
			// the test is correct.
		if (LocalValue > -static_cast<std_uint>(STD_SINT_MIN))
			throw make_numeric_exception(NUMERIC_OVERFLOW);

			// Modular properties of unsigned arithmetic ensure that
			// the following expression assigns the correct value to
			// Value for all possible values of the operand.
			// The following code is a bit involved, to avoid
			// overflow in intermediate results; a simple cast to
			// std_sint, followed by a change of sign, would suffice
			// on two's complement machines without signed
			// arithmetic overflow detection.
			// I trust most compilers to optimize the rest away.
		if (LocalValue > static_cast<std_uint>(STD_SINT_MAX))
			Value = -static_cast<std_sint>(LocalValue -
				static_cast<std_uint>(STD_SINT_MAX)) -
				STD_SINT_MAX;
		else
			Value = -static_cast<std_sint>(LocalValue);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the initial part of a String, up to first non numeric character,
//!	to a std_uint.
//!
//! \param	Value					The reference to the
//!							variable that upon
//!							return will contain the
//!							number.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If no digit is
//!							converted, because the
//!							String is empty or it
//!							does not start with a
//!							digit.
//! \throw	numeric_space::NUMERIC_OVERFLOW		If the converted string
//!							cannot be represented as
//!							a std_uint.
//!
//! \returns	None.
//!
//! \note
//!	If the function throws an exception, the value of Value is undefined.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::ToNumber(std_uint& Value) const
				throw(FatalException, NumericException)
		{
		std_uint	Start;

		if (GetLength() == 0)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		Start = 0;
		ToNumber(Value, Start, GetLength());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert the initial part of a String, up to first non numeric character,
//!	to a std_sint. \n
//!	An optional sign is accepted before first digit; if it is not present,
//!	it is assumed to be positive.
//!
//! \param	Value					The reference to the
//!							variable that upon
//!							return will contain the
//!							number.
//!
//! \throw	utility_space::ILLEGAL_CONVERSION	If no digit is
//!							converted, because the
//!							String is empty or it
//!							does not start with a
//!							digit, after an optional
//!							sign.
//! \throw	numeric_space::NUMERIC_OVERFLOW		If the converted string
//!							cannot be represented as
//!							a std_sint.
//!
//! \returns	None.
//!
//! \note
//!	If the function throws an exception, the value of Value is undefined.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::ToNumber(std_sint& Value) const
				throw(FatalException, NumericException)
		{
		std_uint	Start;

		if (GetLength() == 0)
			throw make_fatal_exception(ILLEGAL_CONVERSION);
		Start = 0;
		ToNumber(Value, Start, GetLength());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert an unsigned number to string, with a given minimum length; the
//!	object content is replaced by the generated string.
//!
//! \param	Value				The number to be converted.
//! \param	MinimumLength			The minimum string length: the
//!						generated string is padded to
//!						this length, if it is shorter.
//! \param	ZeroFilled			If true, the padding character
//!						is a zero character, otherwise
//!						it is blank.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	INLINE	void	String<CHAR_TYPE>::ToString(std_uint Value,
				std_uint MinimumLength, bool ZeroFilled)
				throw(FatalException)
		{
		Vector<CHAR_TYPE>::Clear();
		AppendNumber(Value, MinimumLength, ZeroFilled);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a signed number to string, with a given minimum length; the
//!	object content is replaced by the generated string.
//!
//! \param	Value				The number to be converted.
//! \param	MinimumLength			The minimum string length: the
//!						generated string is padded to
//!						this length, if it is shorter.
//! \param	ZeroFilled			If true, the padding character
//!						is a zero character, otherwise
//!						it is blank.
//! \param	PositiveSignPresent		If true, the sign will be
//!						present for positive values
//!						also.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	void	String<CHAR_TYPE>::ToString(std_sint Value,
			std_uint MinimumLength, bool ZeroFilled,
			bool PositiveSignPresent) throw(FatalException)
		{
		std_uint	LocalLength;

		Vector<CHAR_TYPE>::Clear();
		LocalLength = ZeroFilled? MinimumLength: 0;
		if (Value >= 0)
			{
			if (PositiveSignPresent)
				{
				Vector<CHAR_TYPE>::
					Append(CharacterManager<CHAR_TYPE>::
					GetPlusSign());
				if (LocalLength > 0)
					--LocalLength;
				}
			AppendNumber(static_cast<std_uint>(Value), LocalLength,
				ZeroFilled);
			}
		else
			{
			Vector<CHAR_TYPE>::Append(CharacterManager<CHAR_TYPE>::
				GetMinusSign());
			if (LocalLength > 0)
				--LocalLength;

				// Modular properties of unsigned arithmetic
				// ensure the correctness of the following
				// expression
			AppendNumber(-static_cast<std_uint>(Value), LocalLength,
				ZeroFilled);
			}
		if (MinimumLength > GetLength())
			{
			assert(!ZeroFilled);
			Vector<CHAR_TYPE>::Insert(CharacterManager<CHAR_TYPE>::
				GetSpace(), 0, MinimumLength - GetLength());
			}
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert an unsigned number to string, with the minimum possible length;
//!	object content is replaced by the generated string.
//!
//! \param	Value				The number to be converted.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	void	String<CHAR_TYPE>::ToString(std_uint Value)
			throw(FatalException)
		{
		Vector<CHAR_TYPE>::Clear();
		AppendNumber(Value, 0, true);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Convert a signed number to string, with the minimum possible length; the
//!	object content is replaced by the generated string.
//!
//! \param	Value				The number to be converted.
//! \param	PositiveSignPresent		If true, the sign will be
//!						present for positive values
//!						also.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	void	String<CHAR_TYPE>::ToString(std_sint Value,
			bool PositiveSignPresent) throw(FatalException)
		{
		ToString(Value, 0, true, PositiveSignPresent);
		}

}
