////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	09/04/2018
//!
//! \par	Function:
//!	Contains the definition of specific instantiations of functions of the
//!	data_structure_space::String class template.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"GenericString.h"

# include	<string.h>
# include	<wchar.h>

namespace	data_structure_space
{

	using	namespace	utility_space;
	using	namespace	numeric_space;

//	Warning: use String<char> and String<wchar_t> instead of CharString and
//	WCharString in definitions, otherwise Doxygen will issue a warning and
//	will not generate documentation.

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the length of a zero terminated string, that is, the number of
//!	characters before the string terminator. \n
//!	Implementation valid when the template parameter is char
//!
//! \warning	If the string is not zero terminated, the behaviour is
//!	undefined.
//!
//! \param	Array				Pointer to the string.
//!
//! \throw	utility_space::INVALID_POINTER	If the pointer is NULL.
//!
//! \returns	gns_uint			Length of the string.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	std_uint	String<char>::ComputeLength(const char* Array)
				throw(FatalException)
		{
		return static_cast<std_uint>(strlen(Array));
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the length of a zero terminated string, that is, the number of
//!	characters before the string terminator. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \warning	If the string is not zero terminated, the behaviour is
//!	undefined.
//!
//! \param	Array				Pointer to the string.
//!
//! \throw	utility_space::INVALID_POINTER	If the pointer is NULL.
//!
//! \returns	gns_uint			Length of the string.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	std_uint	String<wchar_t>::ComputeLength(const wchar_t* Array)
				throw(FatalException)
		{
		return static_cast<std_uint>(wcslen(Array));
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compare two strings, returning the comparison result. \n
//!	Implementation valid when the template parameter is char.
//!
//! \param	FirstArgument	First String to be compared.
//! \param	SecondArgument	Second String to be compared.
//!
//! \throw	None.
//!
//! \returns	CompareType	The comparison result:
//!				- COMPARE_EQUAL, if FirstArgument and
//!					SecondArgument are equal;
//!				- COMPARE_GREATER, if FirstArgument is lexically
//!					greater than SecondArgument;
//!				- COMPARE_LESS, if FirstArgument is lexically
//!					less than SecondArgument.
//!				.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	CompareType	String<char>::Compare(const CharString& FirstArgument,
				const CharString& SecondArgument) noexcept
		{
		int	Result;
		
		assert(FirstArgument.GetString() [FirstArgument.GetLength()] ==
			CharacterManager<char>::GetEOS());
		assert(SecondArgument.GetString()
			[SecondArgument.GetLength()] ==
			CharacterManager<char>::GetEOS());

		Result = strcmp(FirstArgument.GetString(),
			SecondArgument.GetString());
		if (Result == 0)
			return COMPARE_EQUAL;
		return Result > 0? COMPARE_GREATER: COMPARE_LESS;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compare two strings, returning the comparison result. \n
//!	Implementation valid when the template parameter is wchar_t.
//!
//! \param	FirstArgument	First String to be compared.
//! \param	SecondArgument	Second String to be compared.
//!
//! \throw	None.
//!
//! \returns	CompareType	The comparison result:
//!				- COMPARE_EQUAL, if FirstArgument and
//!					SecondArgument are equal;
//!				- COMPARE_GREATER, if FirstArgument is lexically
//!					greater than SecondArgument;
//!				- COMPARE_LESS, if FirstArgument is lexically
//!					less than SecondArgument.
//!				.
//!
////////////////////////////////////////////////////////////////////////////////

template<>
	CompareType	String<wchar_t>::Compare(const WCharString&
				FirstArgument,
				const WCharString& SecondArgument) noexcept
		{
		int	Result;
		
		assert(FirstArgument.GetString() [FirstArgument.GetLength()] ==
			CharacterManager<char>::GetEOS());
		assert(SecondArgument.GetString()
			[SecondArgument.GetLength()] ==
			CharacterManager<char>::GetEOS());

		Result = wcscmp(FirstArgument.GetString(),
			SecondArgument.GetString());
		if (Result == 0)
			return COMPARE_EQUAL;
		return Result > 0? COMPARE_GREATER: COMPARE_LESS;
		}

}
