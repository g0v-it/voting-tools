////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	09/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the data_structure_space::String class
//!	template and of the CharString and WCharString classes.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined GENERIC_STRING_H

# define	GENERIC_STRING_H

# if	!defined NDEBUG
# include	<typeinfo>	// Defines typeid() used in .tpl
# endif

# include	<string.h>

# include	"FatalException.h"
# include	"NumericException.h"
# include	"Vector.h"
# include	"CharacterManager.h"

namespace	data_structure_space
{

	using	namespace	utility_space;
	using	namespace	numeric_space;

////////////////////////////////////////////////////////////////////////////////
//! \class	String
//!	The String class template provides functions and operators for string
//!	handling. \n
//!	String objects are kept as a Vector of characters, terminated with a
//!	terminator cannot of the appropriate type. \n
//!	The string terminator cannot be part of a String; any attempt to insert
//!	such a character into a String will cause an exception to be raised.
//!
//! \tparam	CHAR_TYPE	Template parameter CHAR_TYPE is the type of the
//!				characters forming the string. It can be either
//!				char or wchar_t.
//!
//! \see	CharString
//! \see	WCharString
//! \see	DECIMAL_BASE
//!
////////////////////////////////////////////////////////////////////////////////

template<typename CHAR_TYPE>
	class	String: private Vector<CHAR_TYPE>
	{
	private:

				void		Append(CHAR_TYPE Character)
							throw(FatalException);

				void		AppendNumber(register std_uint
							Value,
							std_uint MinimumLength,
							bool ZeroFilled)
							throw(FatalException);

	public:

						String(void)
							throw(FatalException);

				explicit	String(std_uint Size)
							throw(FatalException);

				explicit	String(register const CHAR_TYPE*
							SourceString)
							throw(FatalException);

						String(const String<CHAR_TYPE>&
							thisString)
							throw(FatalException);

						String(String<CHAR_TYPE>&&
							thisString)
							throw(FatalException);

				bool		IsEmpty(void) const noexcept;

				std_uint	GetLength(void) const noexcept;

				void		Clear(void) noexcept;

			const	CHAR_TYPE*	GetString(void) const noexcept;

			const	String&		operator = (const String&
							Argument)
							throw(FatalException);

			const	String&		operator = (String&& Argument)
							throw(FatalException);

			const	CHAR_TYPE&	operator [] (std_uint Index)
							const
							throw(FatalException);

				bool		operator == (const String&
							Operand) const noexcept;

				bool		operator != (const String&
							Operand) const noexcept;

				bool		operator > (const String&
							Operand) const noexcept;

				bool		operator < (const String&
							Operand) const noexcept;

				bool		operator >= (const String&
							Operand) const noexcept;

				bool		operator <= (const String&
							Operand) const noexcept;

				String		operator + (CHAR_TYPE Argument)
							const
							throw(FatalException);

			const	String&		operator += (CHAR_TYPE Argument)
							throw(FatalException);

				String		operator + (const String&
							Argument) const
							throw(FatalException);

			const	String&		operator += (const String&
							Argument)
							throw(FatalException);

				CompareType	Compare(const String& Argument)
							const noexcept;

				void		RemoveRear(std_uint
							NumCharacters)
							throw(FatalException);

				void		RemoveFrom(std_uint StartIndex)
							throw(FatalException);

				void		ToNumber(register std_uint&
							Value,
							std_uint& StartIndex,
							register std_uint
							MaximumLength) const
							throw(FatalException,
							NumericException);

				void		ToNumber(std_sint& Value,
							std_uint& StartIndex,
							std_uint MaximumLength)
							const
							throw(FatalException,
							NumericException);

				void		ToNumber(std_uint& Value) const
							throw(FatalException,
							NumericException);

				void		ToNumber(std_sint& Value) const
							throw(FatalException,
							NumericException);

				void		ToString(std_uint Value,
							std_uint MinimumLength,
							bool ZeroFilled)
							throw(FatalException);

				void		ToString(std_sint Value,
							std_uint MinimumLength,
							bool ZeroFilled,
							bool
							PositiveSignPresent)
							throw(FatalException);

				void		ToString(std_uint Value)
							throw(FatalException);

				void		ToString(std_sint Value,
							bool
							PositiveSignPresent)
							throw(FatalException);

		static		std_uint	ComputeLength(const CHAR_TYPE*
							Array)
							throw(FatalException);

		static		CompareType	Compare(const String&
							FirstArgument,
							const String&
							SecondArgument)
							noexcept;

				using		Vector<CHAR_TYPE>::GetSize;

				using		Vector<CHAR_TYPE>::Resize;

				using		Vector<CHAR_TYPE>::Trim;

	};

////////////////////////////////////////////////////////////////////////////////
//! \class	CharString
//!	CharString instantiates the data_structure_space::String class template,
//!	using <b>char</b> as template parameter.
//!
////////////////////////////////////////////////////////////////////////////////

	typedef		String<char>	CharString;

////////////////////////////////////////////////////////////////////////////////
//! \class	WCharString
//!	WCharString instantiates the data_structure_space::String class
//!	template, using <b>wchar_t</b> as template parameter.
//!
////////////////////////////////////////////////////////////////////////////////

	typedef		String<wchar_t>	WCharString;

}

# include	"GenericString.tpl"

# endif
