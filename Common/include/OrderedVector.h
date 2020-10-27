////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	29/05/2018
//!
//! \par	Function:
//!	Contains the declaration of the data_structure_space::OrderedVector
//!	class template.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined ORDERED_VECTOR_H

# define	ORDERED_VECTOR_H

# include	"FatalException.h"
# include	"Vector.h"
# include	"Utility.h"

namespace	data_structure_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	OrderedVector
//!	The OrderedVector class template represents an ordered growable array of
//!	objects. Like an array, it contains components that can be accessed
//!	using an integer index, but its size grows automatically to accommodate
//!	new items. \n
//!	Elements are kept in increasing order, as defined by the ordering
//!	function. \n
//!	The relative order of elements considered as equal by the comparison
//!	function is undefined.
//!
//! \tparam	BASE_TYPE	Class of the elements; it can be any class or
//!				built-in type, which has the following
//!				accessible methods (either by default or
//!				explicitly declared):
//!				- constructor without arguments,
//!				- destructor,
//!				- assignment operator,
//!				- new [] operator,
//!				- delete [] operator.
//!				- < comparison operator,
//!				- == comparison operator.
//!				.
//!				The constructor, assignment operator and new []
//!				operator can throw an
//!				utility_space::OUT_OF_MEMORY FatalException;
//!				other methods in the above list shall not throw
//!				any exception.
//!
//! \note
//!	Ordering is defined by default by the < operator, unless a comparison
//!	function, with two constant references to BASE_TYPE as arguments and
//!	returning a CompareType value, is provided during object creation, in
//!	which case the < and == operators are not used and they do not need to
//!	be defined.
//!
//! \note
//!	Insertion of multiple elements considered as equal by the comparison
//!	function is allowed.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	class	OrderedVector: private Vector<BASE_TYPE>
	{
	private:

//! \typedef	CompareFunctionType
//!	Pointer to a function used to compare values in an OrderedVector.
//!
//! \note
//!	The pointed to function Compare must satisfy the requirements for a
//!	correct comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- Compare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their value does not
//!		change;
//!	- Compare(x, x) must return COMPARE_EQUAL;
//!	- if Compare(x, y) returns COMPARE_EQUAL, then also
//!		Compare(y, x) must return COMPARE_EQUAL;
//!	- if Compare(x, y) returns COMPARE_GREATER, then
//!		Compare(y, x) must return COMPARE_LESS;
//!	- if Compare(x, y) returns COMPARE_LESS, then
//!		Compare(y, x) must return COMPARE_GREATER;
//!	- if Compare(x, y) returns COMPARE_GREATER, and
//!		Compare(y, z) does not return COMPARE_LESS, then
//!		Compare(x, z) must return COMPARE_GREATER;
//!	- if Compare(x, y) returns COMPARE_LESS, and
//!		Compare(y, z) does not return COMPARE_GREATER, then
//!		Compare(x, z) must return COMPARE_LESS;
//!	- if Compare(x, y) returns COMPARE_EQUAL, and
//!		Compare(y, z) returns COMPARE_EQUAL, then
//!		Compare(x, z) must return COMPARE_EQUAL;
//!	If these requirements are not satisfied, the behaviour and the content
//!	of the OrderedArray object are unpredictable.
		typedef	CompareType	(*CompareFunctionType)(const BASE_TYPE&
						FirstOperand,
						const BASE_TYPE& SecondOperand);

//! \property Compare
//!	Pointer to the comparison function used to define ordering. \n
//!	Is is never changed after object creation.
			CompareFunctionType	Compare;

			void		Fill(const Vector<BASE_TYPE>&
						SourceVector,
						std_uint StartIndex,
						std_uint NumElements)
						throw(FatalException);

			void		HeapSort(register const
						Vector<BASE_TYPE>& SourceVector,
						register Vector<std_uint>&
						IndexVector) const noexcept;

			void		MakeHeap(register const
						Vector<BASE_TYPE>& SourceVector,
						register Vector<std_uint>&
						IndexVector) const noexcept;

			void		SiftDown(register const
						Vector<BASE_TYPE>& SourceVector,
						register Vector<std_uint>&
						IndexVector,
						register std_uint HeapSize,
						register std_uint Vacant,
						std_uint Missing,
						register std_uint Drop) const
						noexcept;

		static	CompareType	DefaultCompare(const BASE_TYPE&
						FirstOperand,
						const BASE_TYPE& SecondOperand)
						noexcept;

		using	Vector<BASE_TYPE>::GetStore;

	public:

					OrderedVector(void)
						throw(FatalException);

			explicit	OrderedVector(CompareFunctionType
						thisCompare)
						throw(FatalException);

			explicit	OrderedVector(std_uint thisSize)
						throw(FatalException);

					OrderedVector(std_uint thisSize,
						CompareFunctionType thisCompare)
						throw(FatalException);

			explicit	OrderedVector(const Vector<BASE_TYPE>&
						thisVector)
						throw(FatalException);

					OrderedVector(const Vector<BASE_TYPE>&
						thisVector, CompareFunctionType
						thisCompare)
						throw(FatalException);

					OrderedVector(const Vector<BASE_TYPE>&
						thisVector, std_uint StartIndex,
						std_uint NumElements)
						throw(FatalException);
	
					OrderedVector(const Vector<BASE_TYPE>&
						thisVector, std_uint StartIndex,
						std_uint NumElements,
						CompareFunctionType thisCompare)
						throw(FatalException);
	
					OrderedVector(const
						OrderedVector<BASE_TYPE>&
						thisVector, std_uint StartIndex,
						std_uint NumElements)
						throw(FatalException);

					OrderedVector(const OrderedVector&
						thisVector)
						throw(FatalException);

					OrderedVector(OrderedVector&&
						thisVector)
						throw(FatalException);

					~OrderedVector(void) noexcept;

			OrderedVector<BASE_TYPE>&	operator = (const
						OrderedVector<BASE_TYPE>&
						thisVector)
						throw(FatalException);

			OrderedVector<BASE_TYPE>&	operator =
						(OrderedVector<BASE_TYPE>&&
						thisVector) noexcept;

			OrderedVector<BASE_TYPE>&	operator = (const Vector
						<BASE_TYPE>& thisVector)
						throw(FatalException);

		const	BASE_TYPE&	operator [] (std_uint Index) const
						throw(FatalException);

			void		Sort(const Vector<BASE_TYPE>&
						thisVector)
						throw(FatalException);

			void		Sort(const Vector<BASE_TYPE>&
						thisVector, std_uint StartIndex,
						std_uint NumElements)
						throw(FatalException);

		static	void		SortIndices(const Vector<BASE_TYPE>&
						thisVector,
						Vector<std_uint>& IndexVector)
						throw(FatalException);

		static	void		SortIndices(const Vector<BASE_TYPE>&
						thisVector,
						Vector<std_uint>& IndexVector,
						CompareFunctionType
						thisCompare)
						throw(FatalException);

		using	Vector<BASE_TYPE>::GetSize;

		using	Vector<BASE_TYPE>::GetPresent;

		using	Vector<BASE_TYPE>::IsEmpty;

		using	Vector<BASE_TYPE>::Clear;

		using	Vector<BASE_TYPE>::RemoveRear;

		using	Vector<BASE_TYPE>::Remove;

		using	Vector<BASE_TYPE>::Resize;

		using	Vector<BASE_TYPE>::Trim;

	};

}

# include	"OrderedVector.tpl"

# endif
