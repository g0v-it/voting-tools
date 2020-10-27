////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	04/07/2008
//!
//! \par	Function
//!	General purpose include file for all projects written in C++. \n
//!	This file contains general purpose type and macro definitions.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined STANDARD_H

# define	STANDARD_H

# include	<assert.h>
# include	<limits.h>
# include	<stdlib.h>

	// Supported processors
//! \def	INTEL_X86
//!	Constant used to specify Intel *86 processors.
# define	INTEL_X86			1

	// Supported operating systems
//! \def	LINUX
//!	Constant used to specify Linux as operating system.
# define	LINUX				1

//! \def	MS_WINDOWS
//!	Constant used to specify MS Windows as operating system.
# define	MS_WINDOWS			2

	// Supported compilers
//! \def	GNU_4
//!	Constant used to specify GNU compiler version 4.
# define	GNU_4				1

//! \def	VISUAL_NET_2005	
//!	Constant used to specify Visual .Net 2005 compiler.
# define	VISUAL_NET_2005			2

	// Supported memory monitoring modes
//! \def	MEMORY_MONITOR_YES
//!	Constant used to specify memory monitoring.
# define	MEMORY_MONITOR_YES		1

//! \def	MEMORY_MONITOR_NO
//!	Constant used to specify no memory monitoring.
# define	MEMORY_MONITOR_NO		0

	// Check the definition of PROCESSOR: must be INTEL_X86.
# if	!defined PROCESSOR
# error	PROCESSOR not defined
# endif

# if PROCESSOR != INTEL_X86
# error	PROCESSOR not supported
# endif

	// Check the definition of SYSTEM: must be LINUX or MS_WINDOWS.
# if	!defined SYSTEM
# error	SYSTEM not defined
# endif

# if SYSTEM != LINUX && SYSTEM != MS_WINDOWS
# error	SYSTEM not supported
# endif

# if	!defined COMPILER
# error	COMPILER not defined
# endif

	// Check the definition of COMPILER: must be GNU_4 or VISUAL_NET_2005.
# if COMPILER != GNU_4 && COMPILER != VISUAL_NET_2005
# error	COMPILER not supported
# endif

# if COMPILER == VISUAL_NET_2005
////////////////////////////////////////////////////////////////////////////////
// warning C4290: C++ exception specification ignored except to indicate
// a function is not __declspec(nothrow)
//
// A function is declared using exception specification, which Visual C++
// accepts, but does not implement. Code with exception specifications that are
// ignored during compilation may need to be recompiled and linked to be reused
// in future versions supporting exception specifications.
// To avoid a large number of warnings, this warning is removed with the
// following pragma, which is specific of the compiler version in use.
////////////////////////////////////////////////////////////////////////////////
# pragma warning(disable: 4290)
# endif


	// Enable inlining, if required.

# if	defined USE_INLINE

//! \def	INLINE
//!	Used to enable inlining of functions.
# define	INLINE				inline

# else

//! \def	INLINE
//!	Used to disable inlining of functions.
# define	INLINE

# endif

# if	!defined GLOBAL

//! \def	GLOBAL
//!	Used to declare global variables in included files.
# define	GLOBAL				extern

# endif

	// Check the definition of MONITOR_MEMORY: must be MEMORY_MONITOR_NO,
	// MEMORY_MONITOR_YES or undefined, defaulting to MEMORY_MONITOR_NO.
# if	defined MONITOR_MEMORY

# if MONITOR_MEMORY != MEMORY_MONITOR_YES && MONITOR_MEMORY != MEMORY_MONITOR_NO
# error	MONITOR_MEMORY not supported
# endif

# else

//! \def	MONITOR_MEMORY
//!	Used to enable memory monitoring. As if affect performances, it is
//!	disabled by default.
# define	MONITOR_MEMORY			MEMORY_MONITOR_NO

# endif

//! \def	LOCAL
//!	Used to declare variables and functions with file scope.
# define	LOCAL				static

//! \def	DECIMAL_BASE
//!	Base used in number conversions. All digits in the decimal system have a
//!	value smaller than this.
# define	DECIMAL_BASE			10

//! \def	HEXADECIMAL_BASE
//!	Hexadecimal base used in number conversions. All hexadecimal digits have
//!	a value smaller than this.
# define	HEXADECIMAL_BASE		16

	// Machine independent type definitions

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	ArithmeticTypes	Arithmetic types
//!	Definitions of machine independent arithmetic types and related
//!	constants.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

//! \typedef	std_tiny_int
//!	Smallest signed integer type; at least 8 bits.
typedef		signed char	std_tiny_int;

//! \typedef	std_tiny_uint
//!	Smallest unsigned integer type; at least 8 bits.
typedef		unsigned char	std_tiny_uint;

//! \def	STD_TINY_SINT_MIN
//!	Minimum value of a std_tiny_int.
# define	STD_TINY_SINT_MIN		SCHAR_MIN

//! \def	STD_TINY_SINT_MAX
//!	Maximum value of a std_tiny_int.
# define	STD_TINY_SINT_MAX		SCHAR_MAX

//! \def	STD_TINY_UINT_MAX
//!	Maximum value of a std_tiny_uint.
# define	STD_TINY_UINT_MAX		UCHAR_MAX

# if INT_MAX >= 0x7FFFFFFF

//! \typedef	std_sint
//!	Normal signed integer type; at least 32 bits.
typedef		signed int	std_sint;

//! \typedef	std_uint
//!	Normal unsigned integer type; at least 32 bits.
typedef		unsigned int	std_uint;

//! \def	STD_SINT_MIN
//!	Minimum value of a std_sint.
# define	STD_SINT_MIN			INT_MIN

//! \def	STD_SINT_MAX
//!	Maximum value of a std_sint.
# define	STD_SINT_MAX			INT_MAX

//! \def	STD_UINT_MAX
//!	Maximum value of a std_uint.
# define	STD_UINT_MAX			UINT_MAX

# else

//! \typedef	std_sint
//!	Normal signed integer type; at least 32 bits.
typedef		long	std_sint;

//! \typedef	std_uint
//!	Normal unsigned integer type; at least 32 bits.
typedef		unsigned long	std_uint;

//! \def	STD_SINT_MIN
//!	Minimum value of a std_sint.
# define	STD_SINT_MIN			LONG_MIN

//! \def	STD_SINT_MAX
//!	Maximum value of a std_sint.
# define	STD_SINT_MAX			LONG_MAX

//! \def	STD_UINT_MAX
//!	Maximum value of a std_uint.
# define	STD_UINT_MAX			ULONG_MAX

# endif

//! \def	STD_UINT_BITS
//!	Number of bits in a std_uint.
# define	STD_UINT_BITS			(sizeof(std_uint) * CHAR_BIT)

//! \def	STD_UINT_MAX_DIGITS
//!	Maximum number of decimal digits used to represent a std_uint, computed
//!	with some margin. The number can actually be greater than the maximum
//!	number of digits, but never smaller.
# define	STD_UINT_MAX_DIGITS		(STD_UINT_BITS * 31 / 100 + 1)

//! \def	SAFE_POWER_OF_TEN_IN_STD_UINT
//!	Exponent of the maximum power of ten that can be represented in a
//!	std_uint, computed with some safety margin. The number can actually be
//!	smaller than the maximum power of ten, but never greater.
# define	SAFE_POWER_OF_TEN_IN_STD_UINT	(STD_UINT_BITS * 30 / 100)

# if INT_MAX >= 0x7FFFFFFFFFFFFFFF

//! \typedef	std_slong
//!	Normal signed long integer type; at least 64 bits.
typedef		signed int	std_slong;

//! \typedef	std_ulong
//!	Normal unsigned long integer type; at least 64 bits.
typedef		unsigned int	std_ulong;

//! \def	STD_SLONG_MIN
//!	Minimum value of a std_slong.
# define	STD_SLONG_MIN			INT_MIN

//! \def	STD_SLONG_MAX
//!	Maximum value of a std_slong.
# define	STD_SLONG_MAX			INT_MAX

//! \def	STD_ULONG_MAX
//!	Maximum value of a std_ulong.
# define	STD_ULONG_MAX			UINT_MAX

# elif LONG_MAX >= 0x7FFFFFFFFFFFFFFF

//! \typedef	std_slong
//!	Normal signed long integer type; at least 64 bits.
typedef		long	std_slong;

//! \typedef	std_ulong
//!	Normal unsigned long integer type; at least 64 bits.
typedef		unsigned long	std_ulong;

//! \def	STD_SLONG_MIN
//!	Minimum value of a std_slong.
# define	STD_SLONG_MIN			LONG_MIN

//! \def	STD_SLONG_MAX
//!	Maximum value of a std_slong.
# define	STD_SLONG_MAX			LONG_MAX

//! \def	STD_ULONG_MAX
//!	Maximum value of a std_ulong.
# define	STD_ULONG_MAX			ULONG_MAX

# else

//! \typedef	std_slong
//!	Normal signed long integer type; at least 64 bits.
typedef		long long	std_slong;

//! \typedef	std_ulong
//!	Normal unsigned long integer type; at least 64 bits.
typedef		unsigned long long	std_ulong;

//! \def	STD_SLONG_MIN
//!	Minimum value of a std_slong.
# define	STD_SLONG_MIN			LLONG_MIN

//! \def	STD_SLONG_MAX
//!	Maximum value of a std_slong.
# define	STD_SLONG_MAX			LLONG_MAX

//! \def	STD_ULONG_MAX
//!	Maximum value of a std_ulong.
# define	STD_ULONG_MAX			ULLONG_MAX

# endif

//! \def	STD_ULONG_BITS
//!	Number of bits in a std_ulong.
# define	STD_ULONG_BITS			(sizeof(std_ulong) * CHAR_BIT)

//! \def	STD_ULONG_MAX_DIGITS
//!	Maximum number of decimal digits used to represent a std_ulong, computed
//!	with some margin. The number can actually be greater than the maximum
//!	number of digits, but never smaller.
# define	STD_ULONG_MAX_DIGITS		(STD_ULONG_BITS * 31 / 100 + 1)

//! \def	SAFE_POWER_OF_TEN_IN_STD_ULONG
//!	Exponent of the maximum power of ten that can be represented in a
//!	std_ulong, computed with some safety margin. The number can actually be
//!	smaller than the maximum power of ten, but never greater.
# define	SAFE_POWER_OF_TEN_IN_STD_ULONG	(STD_ULONG_BITS * 30 / 100)

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	RepresentationOrientedTypes	Representation oriented types
//!	Definitions of machine independent representation oriented types.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

# if UCHAR_MAX == 0xFF

//! \typedef	byte
//!	byte type; exactly 8 bits.
typedef		unsigned char	byte;

//! \def	BYTE_MAX
//!	Maximum value of a byte.
# define	BYTE_MAX			UCHAR_MAX

//! \def	BYTE_BITS
//!	Number of bits in a byte
# define	BYTE_BITS			CHAR_BIT

# else
# error	byte is not available
# endif

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

//! \enum	CompareType
//!	Enumerative type for comparison results.
enum	CompareType
	{
		//! Less than
	COMPARE_LESS,

		//! Equal
	COMPARE_EQUAL,

		//! Greater than
	COMPARE_GREATER
	};

# if	defined __cplusplus

	// C++ specific definitions

//! \def	PURE_VIRTUAL
//!	Used for C++ pure virtual functions, to make their declaration more
//!	readable.
# define	PURE_VIRTUAL			0

////////////////////////////////////////////////////////////////////////////////
//	checked_cast	Macro to be used for safe C++ cast
////////////////////////////////////////////////////////////////////////////////

# if	defined DEBUGGING
//! \def	checked_cast
//!	Macro to be used to get C++ dynamic_cast during debugging.
# define	checked_cast			dynamic_cast

# else

//! \def	checked_cast
//!	Macro to be used to get C++ static_cast for product release.
# define	checked_cast			static_cast

# endif

# endif


////////////////////////////////////////////////////////////////////////////////
//!
//! \defgroup	CommonMacros	Common Macros
//!	Definitions of commonly used macros.
//!
//!	\{
//!
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//! \def	ignore_value(expression)
//!	Ignore the value of an expression, casting it to void.
//!	Mostly useful for function calls.
//!
//! \param	expression	The expression
//!
////////////////////////////////////////////////////////////////////////////////

# define	ignore_value(expression) \
			(static_cast<void>(expression))

////////////////////////////////////////////////////////////////////////////////
//! \def	number_of_elements(array)
//!	Computes the number of elements in a statically allocated array.
//!
//! \param	array	The array name
//!
////////////////////////////////////////////////////////////////////////////////

# define	number_of_elements(array) \
			(sizeof(array) / sizeof((array) [0]))

////////////////////////////////////////////////////////////////////////////////
//! \def	make_string(text)
//!	Converts a fragment of code to string.
//!	The parameter is taken literally without any macro expansion.
//!
//! \param	text	The fragment of code to be converted.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_string(text)		#text

////////////////////////////////////////////////////////////////////////////////
//! \def	make_evaluated_string(text)
//!	Converts a fragment of code to string.
//!	Any macro in the parameter is expanded before conversion.
//!
//! \param	text	The fragment of code to be converted.
//!
////////////////////////////////////////////////////////////////////////////////

# define	make_evaluated_string(text)	make_string(text)

////////////////////////////////////////////////////////////////////////////////
//! \def	increment(value, type, delta)
//!	Add a number to an enumerated value.
//!
//! \param	value		The value.
//! \param	type		The enumerated type.
//! \param	delta		The value to be added.
//!
////////////////////////////////////////////////////////////////////////////////

# define	increment(value, type, delta) \
			(static_cast<type>(static_cast<int>(value) + \
			static_cast<int>(delta)))

////////////////////////////////////////////////////////////////////////////////
//! \def	decrement(value, type, delta)
//!	Subtract a number from an enumerated value.
//!
//! \param	value	The value.
//! \param	type	The enumerated type.
//! \param	delta	The value to be subtracted.
//!
////////////////////////////////////////////////////////////////////////////////

# define	decrement(value, type, delta) \
			(static_cast<type>(static_cast<int>(value) - \
			static_cast<int>(delta)))

////////////////////////////////////////////////////////////////////////////////
//!	\}
////////////////////////////////////////////////////////////////////////////////

	// Skip global operators declarations (for very simple applications).
# if	!defined SKIP_GLOBAL_OPERATORS
# include	"GlobalOperators.h"
# endif

# endif
