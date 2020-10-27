////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	29/05/2018
//!
//! \par	Function:
//!	Contains the implementation of the data_structure_space::OrderedVector
//!	class template.
//!
////////////////////////////////////////////////////////////////////////////////

namespace	data_structure_space
{

using	namespace	numeric_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Fill the object with elements taken from a Vector, sorting them in
//!	increasing order. \n
//!	Ordering is defined by the object comparison function. \n
//!	The relative order of elements considered as equal by the comparison
//!	function is undefined. \n
//!	Existing elements in the object, if any, are discarded. \n
//!	Thus upon exit the object has the same number of elements of
//!	SourceVector, sorted so that if i > j, Compare((*this) [i], (*this) [j])
//!	will not return COMPARE_LESS. \n
//!	An attempt to copy zero elements from the beginning of an empty Vector
//!	does nothing. \n
//!	An attempt to copy zero elements from an index different from zero from
//!	an empty Vector throws an exception. \n
//!	The Vector argument must be different from the object itself.
//!
//! \param	SourceVector				Reference to the Vector
//!							of elements to be
//!							sorted.
//! \param	StartIndex				Index of first element
//!							to copy. Valid range is
//!					[0 .. SourceVector.GetPresent() - 1].
//! \param	NumElements				Number of elements to
//!							copy. Valid range is
//!					[0 .. SourceVector.GetPresent()].
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the number of
//!							elements in SourceVector
//!							is less than
//!							StartIndex +
//!							NumElements.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If SourceVector is the
//!							object itself.
//!
//! \returns	None.
//!
//! \note
//!	The comparison function must satisfy the requirements for a correct
//!	comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- Compare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their valued does not
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
//!	.
//!	If these requirements are not satisfied, the behaviour and the content
//!	of the object are unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	void	OrderedVector<BASE_TYPE>::Fill(const Vector<BASE_TYPE>&
			SourceVector, std_uint StartIndex, std_uint NumElements)
			throw(FatalException)
		{
		register	const	BASE_TYPE*	p;
		register	const	std_uint*	IndexPointer;
				const	std_uint*	Last;

		if (static_cast<const Vector<BASE_TYPE> *>(this) ==
			&SourceVector)
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		if (StartIndex + NumElements > 0 &&
			StartIndex + NumElements > SourceVector.GetPresent())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);

		Vector<std_uint>	IndexVector(SourceVector.GetPresent());

		Clear();
		Resize(SourceVector.GetPresent());
		HeapSort(SourceVector, IndexVector);
		p = SourceVector.GetStore() + StartIndex;
		IndexPointer = IndexVector.GetStore();
		Last = IndexPointer + IndexVector.GetPresent();
		while (IndexPointer < Last)
			Vector<BASE_TYPE>::Append(p [*IndexPointer++]);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Given a Vector of elements, create a Vector of indices, containing the
//!	indices of Vector elements sorted in increasing elements order. \n
//!	Ordering is defined by the object comparison function. \n
//!	The relative order of elements considered as equal by the comparison
//!	function is undefined. \n
//!	Thus upon exit the object has the same number of elements of
//!	SourceVector, sorted so that if i > j,
//!	Compare((*this) [IndexVector [i]], (*this) [IndexVector [j]])
//!	will not return COMPARE_LESS. \n
//!	The algorithm used is Floyd's heapsort with a binary heap. \n
//!	The worst case time complexity is O(NlogN).
//!
//! \param	SourceVector	Reference to the Vector of elements to be
//!				sorted.
//! \param	IndexVector	Reference to the Vector of indices.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	The comparison function must satisfy the requirements for a correct
//!	comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- Compare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their valued does not
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
//!	.
//!	If these requirements are not satisfied, the behaviour and the content
//!	of IndexVector are unpredictable.
//!
//! \see	MAX_ADDED_COPIES
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	void	OrderedVector<BASE_TYPE>::HeapSort(register const
			Vector<BASE_TYPE>& SourceVector,
			register Vector<std_uint>& IndexVector) const noexcept
		{
		register	std_uint	i;
		register	std_uint*	p;
		register	std_uint	Temp;
		register	std_uint	Last;
		register	std_uint	Drop;

			// Initialize IndexVector.
		IndexVector.Clear();
		for (i = SourceVector.GetPresent(); i > MAX_ADDED_COPIES;
			i -= MAX_ADDED_COPIES)
			IndexVector.Append(0, MAX_ADDED_COPIES);
		IndexVector.Append(0, i);
		p = IndexVector.GetStore();
		for (i = 0; i < IndexVector.GetPresent();)
			*p++ = i++;
		assert(SourceVector.GetPresent() == IndexVector.GetPresent());

			// Nothing else to do if there are zero or one element.
		if ((i = SourceVector.GetPresent()) <= 1)
			return;

			// Build Heap.
		MakeHeap(SourceVector, IndexVector);
		Drop = Size(--i) - 1;
		Last = PowerOfTwo(Drop);
		p = IndexVector.GetStore() + i;
		for (;;)
			{
				// Sort by deleting max element.
			Temp = *p;
			*p-- = *IndexVector.GetStore();
			SiftDown(SourceVector, IndexVector, i, 0, Temp, Drop);
			if (i-- == Last)
				{
				if (i == 0)
					return;
				--Drop;
				Last /= 2;
				}
			}
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Build the binary heap, using object comparison function.
//!
//! \param	SourceVector	Reference to the Vector of elements to be
//!				sorted.
//! \param	IndexVector	Reference to the Vector of indices. It must have
//!				been initialized with current indices, that is,
//!				integer in increasing order, from 0 to
//!				GetPresent() - 1., otherwise the behaviour is
//!				unpredictable.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	HeapSort
//!
//! \note
//!	The comparison function must satisfy the requirements for a correct
//!	comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- Compare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their valued does not
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
//!	.
//!	If these requirements are not satisfied, the behaviour and the content
//!	of IndexVector are unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	void	OrderedVector<BASE_TYPE>::MakeHeap(register const
			Vector<BASE_TYPE>& SourceVector,
			register Vector<std_uint>& IndexVector) const noexcept
		{
		register		std_uint	i;
		register	const	std_uint*	p;
		register		std_uint	First;
		register		std_uint	Drop;

		assert(IndexVector.GetStore() != static_cast<std_uint *>(NULL));
		assert(SourceVector.GetPresent() == IndexVector.GetPresent());
		Drop = 1;
		First = SourceVector.GetPresent() / 2 - 1;
		p = IndexVector.GetStore() + First;
		for (i = First;; --i, --p)
			{
			if (i == (First - 1) / 2)
				{
				++Drop;
				First = i;
				}
			SiftDown(SourceVector, IndexVector,
				SourceVector.GetPresent(), i, *p, Drop);
			if (i == 0)
				return;
			}
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Provide SiftDown operation of Heapsort.
//!
//! \param	SourceVector	Reference to the Vector of elements to be
//!				sorted.
//! \param	IndexVector	Reference to the Vector of indices.
//! \param	HeapSize	Size of the heap.
//! \param	Vacant		Index for insertion.
//! \param	Missing		Object to be inserted.
//! \param	Drop		The bottom level.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \see	HeapSort
//! \see	MakeHeap
//!
//! \note
//!	The comparison function must satisfy the requirements for a correct
//!	comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- Compare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their valued does not
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
//!	.
//!	If these requirements are not satisfied, the behaviour and the content
//!	of IndexVector are unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	void	OrderedVector<BASE_TYPE>::SiftDown(register const
			Vector<BASE_TYPE>& SourceVector,
			register Vector<std_uint>& IndexVector,
			register std_uint HeapSize, register std_uint Vacant,
			std_uint Missing, register std_uint Drop) const noexcept
		{
		register		std_uint	Child;
		register		std_uint	Count;
		register		std_uint	NextPeek;
		register		std_uint	Parent;
		register		std_uint	Temp;
		register		std_uint*	IndexPointer;
		register	const	BASE_TYPE*	StorePointer;
		register	const	BASE_TYPE*	MissingPointer;

		assert(SourceVector.GetPresent() > 0);
		assert(SourceVector.GetPresent() == IndexVector.GetPresent());
		assert(Missing < SourceVector.GetPresent());
		StorePointer = SourceVector.GetStore();
		MissingPointer = StorePointer + Missing;
		Temp = Vacant;
		Count = 0;
		NextPeek = (Drop + 1) / 2;
		Child = 2 * (Vacant + 1);
		IndexPointer = IndexVector.GetStore();
		assert(IndexPointer != static_cast<std_uint *>(NULL));
		while (Child < HeapSize)
			{
			assert(Child < SourceVector.GetPresent());
			assert(Child >= 1);
			assert(IndexPointer [Child] <
				SourceVector.GetPresent());
			assert(IndexPointer [Child - 1] <
				SourceVector.GetPresent());
			if (Compare(StorePointer [IndexPointer [Child]],
				StorePointer [IndexPointer [Child - 1]]) ==
				COMPARE_LESS)
				--Child;
			IndexPointer [Vacant] = IndexPointer [Child];
			Vacant = Child;
			Child = 2 * (Vacant + 1);
			if (++Count == NextPeek)
				{
				assert(Vacant > 0);
				assert((Vacant - 1) / 2 <
					SourceVector.GetPresent());
				assert(IndexPointer [(Vacant - 1) / 2] <
					SourceVector.GetPresent());
				if (Compare(StorePointer [IndexPointer
					[(Vacant - 1) / 2]], *MissingPointer) ==
					COMPARE_GREATER)
					NextPeek = (Count + Drop + 1) / 2;
				else
					break;
				}
			}
		if (Child == HeapSize)
			{
			IndexPointer [Vacant] = IndexPointer [HeapSize - 1];
			Vacant = HeapSize - 1;
			}
		while (Vacant > Temp)
			{
			assert(Vacant > 0);
			Parent = (Vacant - 1) / 2;
			assert(Parent < SourceVector.GetPresent());
			assert(IndexPointer [Parent] <
				SourceVector.GetPresent());
			if (Compare(StorePointer [IndexPointer [Parent]],
				*MissingPointer) != COMPARE_LESS)
				break;
			assert(Vacant < SourceVector.GetPresent());
			IndexPointer [Vacant] = IndexPointer [Parent];
			Vacant = Parent;
			}
		assert(Vacant < SourceVector.GetPresent());
		IndexPointer [Vacant] = Missing;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default comparison function for searching and sorting.
//!
//! \param	FirstOperand	Reference to first operand for comparison.
//! \param	SecondOperand	Reference to second operand for comparison.
//!
//! \throw	None.
//!
//! \returns	CompareType	Comparison result, that is:
//!				- COMPARE_LESS, if FirstOperand < SecondOperand;
//!				- COMPARE_GREATER, if SecondOperand <
//!					FirstOperand;
//!				- COMPARE_EQUAL, otherwise.
//!				.
//!
//! \note
//!	BASE_TYPE must define an operator < which satisfies the following
//!	conditions:
//!	- irreflexivity		x < x must be false;
//!	- antiSymmetry		x < y implies !(y < x);
//!	- transitivity		x < y and y < z implies x < z.
//!	.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	CompareType	OrderedVector<BASE_TYPE>::DefaultCompare(const
				BASE_TYPE& FirstOperand,
				const BASE_TYPE& SecondOperand) noexcept
		{
		if (FirstOperand < SecondOperand)
			return COMPARE_LESS;
		return SecondOperand < FirstOperand?
			COMPARE_GREATER: COMPARE_EQUAL;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default constructor; construct an OrderedVector object with default size
//!	and default comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(void)
			throw(FatalException): Vector<BASE_TYPE>(),
			Compare(DefaultCompare)
		{
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Single argument constructor; construct an OrderedVector object with
//!	default size and given comparison function.
//!
//! \param	thisCompare			Comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the pointer to the
//!						comparison function is NULL.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(CompareFunctionType
			thisCompare) throw(FatalException): Vector<BASE_TYPE>(),
			Compare(thisCompare)
		{
		if (thisCompare == static_cast<CompareFunctionType>(NULL))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Single argument constructor; construct an OrderedVector with the size
//!	passed as argument and default comparison function.
//!
//! \param	thisSize			Size of the Vector.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(std_uint thisSize)
			throw(FatalException): Vector<BASE_TYPE>(thisSize),
			Compare(DefaultCompare)
		{
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Two argument constructor; construct an OrderedVector with the size
//!	passed as argument and given comparison function.
//!
//! \param	thisSize			Size of the Vector.
//! \param	thisCompare			Comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the pointer to the
//!						comparison function is NULL.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(std_uint thisSize,
			CompareFunctionType thisCompare) throw(FatalException):
			Vector<BASE_TYPE>(thisSize), Compare(thisCompare)
		{
		if (thisCompare == static_cast<CompareFunctionType>(NULL))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Single argument constructor; construct an OrderedVector copying values
//!	from a Vector passed as argument and set default comparison function.
//!
//! \param	thisVector			Reference to the Vector from
//!						which elements are copied.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const Vector<BASE_TYPE>&
			thisVector) throw(FatalException):
			Vector<BASE_TYPE>(thisVector.GetPresent()),
			Compare(DefaultCompare)
		{
		Fill(thisVector, 0, thisVector.GetPresent());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Two arguments constructor; construct an OrderedVector copying values
//!	from a Vector passed as argument and set comparison function passed as
//!	argument.
//!
//! \param	thisVector			Reference to the Vector from
//!						which elements are copied.
//! \param	thisCompare			Comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the pointer to the
//!						comparison function is NULL.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const Vector<BASE_TYPE>&
			thisVector, CompareFunctionType thisCompare)
			throw(FatalException):
			Vector<BASE_TYPE>(thisVector.GetPresent()),
			Compare(thisCompare)
		{
		if (thisCompare == static_cast<CompareFunctionType>(NULL))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		Fill(thisVector, 0, thisVector.GetPresent());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Construct an OrderedVector, copying a specified number of elements from
//!	an existing Vector, starting from a specified index and set default
//!	comparison function. \n
//!	An attempt to copy zero elements from the beginning of an empty Vector
//!	does nothing. \n
//!	An attempt to copy zero elements from an index different from zero from
//!	an empty Vector throws an exception.
//!
//! \param	thisVector				Reference to the Vector
//!							from which elements are
//!							copied.
//! \param	StartIndex				Index of first element
//!							to copy. Valid range is
//!					[0 .. thisVector.GetPresent() - 1].
//! \param	NumElements				Number of elements to
//!							copy. Valid range is
//!					[0 .. thisVector.GetPresent()].
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the number of
//!							elements in source
//!							Vector is less than
//!							StartIndex +
//!							NumElements.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const Vector<BASE_TYPE>&
			thisVector, std_uint StartIndex, std_uint NumElements)
			throw(FatalException): Vector<BASE_TYPE>(NumElements),
			Compare(DefaultCompare)
		{
		Fill(thisVector, StartIndex, NumElements);
		}
	
////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Construct an OrderedVector, copying a specified number of elements from
//!	an existing Vector, starting from a specified index and set comparison
//!	function passed as argument. \n
//!	An attempt to copy zero elements from the beginning of an empty Vector
//!	does nothing. \n
//!	An attempt to copy zero elements from an index different from zero from
//!	an empty Vector throws an exception.
//!
//! \param	thisVector				Reference to the Vector
//!							from which elements are
//! \param	StartIndex				Index of first element
//!							to copy. Valid range is
//!					[0 .. thisVector.GetPresent() - 1].
//! \param	NumElements				Number of elements to
//!							copy. Valid range is
//!					[0 .. thisVector.GetPresent()].
//! \param	thisCompare				Comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the number of
//!							elements in source
//!							Vector is less than
//!							StartIndex +
//!							NumElements.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If the pointer to the
//!							comparison function is
//!							NULL.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const Vector<BASE_TYPE>&
			thisVector, std_uint StartIndex, std_uint NumElements,
			CompareFunctionType thisCompare) throw(FatalException):
			Vector<BASE_TYPE>(NumElements),
			Compare(thisCompare)
		{
		if (thisCompare == static_cast<CompareFunctionType>(NULL))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		Fill(thisVector, StartIndex, NumElements);
		}
	
////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Construct an OrderedVector, copying a specified number of elements from
//!	an existing object, starting from a specified index. \n
//!	An attempt to copy zero elements from the beginning of an empty
//!	OrderedVector does nothing. \n
//!	An attempt to copy zero elements from an index different from zero from
//!	an empty OrderedVector throws an exception.
//!
//! \param	thisVector				Reference to source
//!							OrderedVector object.
//! \param	StartIndex				Starting index of the
//!							source Vector. Valid
//!							range is
//!					[0 .. thisVector.GetPresent() - 1].
//! \param	NumElements				Number of elements to
//!							be copied from the
//!							source OrderedVector.
//!							Valid range is
//!					[0 .. thisVector.GetPresent()].
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the number of
//!							elements in source
//!							OrderedVector is less
//!							than StartIndex +
//!							NumElements.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const
			OrderedVector<BASE_TYPE>& thisVector,
			std_uint StartIndex, std_uint NumElements)
			throw(FatalException):
			Vector<BASE_TYPE>(static_cast<const Vector<BASE_TYPE> &>
			(thisVector), StartIndex, NumElements),
			Compare(thisVector.Compare)
		{
		assert(GetSize() == 0 ||
			GetStore() != static_cast<BASE_TYPE *>(NULL));
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Copy constructor. \n
//!	The OrderedVector argument must be different from the object itself.
//!
//! \param	thisVector			Reference to source
//!						OrderedVector object.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the OrderedVector argument is
//!						the object itself.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(const
			OrderedVector<BASE_TYPE>& thisVector)
			throw(FatalException):
			Vector<BASE_TYPE>(static_cast<const Vector<BASE_TYPE> &>
			(thisVector)), Compare(thisVector.Compare)
		{
		assert(GetSize() == 0 ||
			GetStore() != static_cast<BASE_TYPE *>(NULL));
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move constructor. \n
//!	The OrderedVector argument must be different from the object itself.
//!
//! \param	thisVector			Reference to source
//!						OrderedVector object.
//!
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the OrderedVector argument is
//!						the object itself.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::OrderedVector(OrderedVector&&
			thisVector) throw(FatalException):
			Vector<BASE_TYPE>(static_cast<const Vector<BASE_TYPE> &>
			(thisVector)), Compare(thisVector.Compare)
		{
		assert(GetSize() == 0 ||
			GetStore() != static_cast<BASE_TYPE *>(NULL));
		}

///////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
///////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>::~OrderedVector(void) noexcept
		{
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Assignment operator.
//!
//! \param	thisVector			Reference to source
//!						OrderedVector object.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	OrderedVector<BASE_TYPE>&	Reference to the assigned
//!						OrderedVector object.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>&
			OrderedVector<BASE_TYPE>::operator = (const
				OrderedVector<BASE_TYPE>& thisVector)
				throw(FatalException)
		{
		static_cast<Vector<BASE_TYPE> &>(*this) =
			static_cast<const Vector<BASE_TYPE>& >(thisVector);
		Compare = thisVector.Compare;
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Move assignment operator.
//!
//! \param	thisVector			Reference to source
//!						OrderedVector object.
//!
//! \throw	None.
//!
//! \returns	OrderedVector<BASE_TYPE>&	Reference to the assigned
//!						Ordered Vector object.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>&
			OrderedVector<BASE_TYPE>::operator = (OrderedVector&&
			thisVector) noexcept
		{
		static_cast<Vector<BASE_TYPE> &>(*this) =
			static_cast<Vector<BASE_TYPE>& >(thisVector);
		Compare = thisVector.Compare;
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Assignment operator. Copy values from a Vector passed as argument,
//!	ordering them.
//!
//! \param	thisVector			Reference to the Vector from
//!						which elements are copied.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	OrderedVector<BASE_TYPE>&
			OrderedVector<BASE_TYPE>::operator = (const
				Vector<BASE_TYPE>& thisVector)
				throw(FatalException)
		{
		Fill(thisVector, 0, thisVector.GetPresent());
		return *this;
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Subscript operator, used to get access to the elements of a
//!	OrderedVector.
//!
//! \param	Index					Index of the element to
//!							be retrieved. Valid
//!							range is
//!							[0 .. GetPresent() - 1].
//!
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the index is not less
//!							than the number of
//!							contained objects.
//!
//! \returns	const	BASE_TYPE&			Reference to the
//!							selected element.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	const	BASE_TYPE&	OrderedVector<BASE_TYPE>::operator []
						(std_uint Index) const
						throw(FatalException)
		{
		if (Index >= GetPresent())
			throw make_fatal_exception(INDEX_OUT_OF_BOUNDS);
		return GetStore() [Index];
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Replace existing elements with all elements from the source Vector. \n
//!	Replacing with an empty Vector clears the object. \n
//!	The Vector argument must be different from the object itself.
//!
//! \param	thisVector			Reference to source Vector
//!						object.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the Vector argument is the
//!						object itself.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	void	OrderedVector<BASE_TYPE>::Sort(const Vector<BASE_TYPE>&
				thisVector) throw(FatalException)
		{
		Sort(thisVector, 0, thisVector.GetPresent());
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Replace existing elements with a part of the source Vector. \n
//!	An attempt to replace with zero elements from an index different from
//!	zero from an empty Vector throws an exception. \n
//!	An attempt to replace with zero elements clears the object. \n
//!	The Vector argument must be different from the object itself.
//!
//! \param	thisVector				Reference to the Vector
//!							from which elements will
//!							be copied.
//! \param	StartIndex				Index of first element
//!							to append. Valid range
//!							is
//!					[0 .. thisVector.GetPresent() - 1].
//! \param	NumElements				Number of elements to
//!							append. Valid range is
//!					[0 .. thisVector.GetPresent()].
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	utility_space::INDEX_OUT_OF_BOUNDS	If the number of
//!							elements in source
//!							Vector is less than
//!							StartIndex +
//!							NumElements.
//! \throw	utility_space::ILLEGAL_ARGUMENT		If the Vector argument
//!							is the object itself.
//!
//! \returns	None.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	void	OrderedVector<BASE_TYPE>::Sort(const Vector<BASE_TYPE>&
				thisVector, std_uint StartIndex,
				std_uint NumElements) throw(FatalException)
		{
		if (static_cast<const Vector<BASE_TYPE> *>(this) == &thisVector)
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		Clear();
		Fill(thisVector, StartIndex, NumElements);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Given a Vector of elements, create a Vector of indices, containing the
//!	indices of Vector elements, if sorted in increasing elements order. \n
//!	Ordering is defined by the comparison function passed as argument. \n
//!	The relative order of elements considered as equal by the comparison
//!	function is undefined. \n
//!	Thus after creating the Vector of indices, if i > j,
//!	DefaultCompare(thisVector [IndexVector [i]],
//!	thisVector [IndexVector [j]]) will not return COMPARE_LESS.
//!
//! \param	thisVector			Reference to the Vector to be
//!						sorted.
//! \param	IndexVector			Reference to the Vector that
//!						upon return contains the indices
//!						of thisVector elements, sorted
//!						in increasing elements order,
//!						according to the comparison
//!						operator of BASE_TYPE.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If thisVector and IndexVector
//!						refer the same Vector.
//!
//! \returns	None.
//!
//! \note
//!	BASE_TYPE must define an operator < which satisfies the following
//!	conditions:
//!	- irreflexivity		x < x must be false;
//!	- antiSymmetry		x < y implies !(y < x);
//!	- transitivity		x < y and y < z implies x < z.
//!	.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	void	OrderedVector<BASE_TYPE>::SortIndices(const
				Vector<BASE_TYPE>& thisVector,
				Vector<std_uint>& IndexVector)
				throw(FatalException)
		{
		if (static_cast<const void *>(&thisVector) ==
			static_cast<void *>(&IndexVector))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		OrderedVector<BASE_TYPE>(DefaultCompare).HeapSort(thisVector,
			IndexVector);
		}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Given a Vector of elements, create a Vector of indices, containing the
//!	indices of Vector elements, if sorted in increasing elements order. \n
//!	Ordering is defined by the comparison function passed as argument. \n
//!	The relative order of elements considered as equal by the comparison
//!	function is undefined. \n
//!	Thus after creating the Vector of indices, if i > j,
//!	Compare(thisVector [IndexVector [i]], thisVector [IndexVector [j]])
//!	will not return COMPARE_LESS.
//!
//! \param	thisVector			Reference to the Vector to be
//!						sorted.
//! \param	IndexVector			Reference to the Vector that
//!						upon return contains the indices
//!						of thisVector elements, sorted
//!						in increasing elements order,
//!						according to the comparison
//!						function.
//! \param	thisCompare			Comparison function.
//!
//! \throw	utility_space::OUT_OF_MEMORY	If memory allocation fails.
//! \throw	utility_space::ILLEGAL_ARGUMENT	If the pointer to the
//!						comparison function is NULL or
//!						if thisVector and IndexVector
//!						refer the same Vector.
//!
//! \returns	None.
//!
//! \note
//!	The comparison function must satisfy the requirements for a correct
//!	comparison function, that is it must be consistent, reflexive,
//!	antisymmetrical and transitive:
//!	- thisCompare(x, y) must return a value that depends uniquely
//!		upon x and y and is always the same if their valued does not
//!		change;
//!	- thisCompare(x, x) must return COMPARE_EQUAL;
//!	- if thisCompare(x, y) returns COMPARE_EQUAL, then also
//!		thisCompare(y, x) must return COMPARE_EQUAL;
//!	- if thisCompare(x, y) returns COMPARE_GREATER, then
//!		thisCompare(y, x) must return COMPARE_LESS;
//!	- if thisCompare(x, y) returns COMPARE_LESS, then
//!		thisCompare(y, x) must return COMPARE_GREATER;
//!	- if thisCompare(x, y) returns COMPARE_GREATER, and
//!		thisCompare(y, z) does not return COMPARE_LESS, then
//!		thisCompare(x, z) must return COMPARE_GREATER;
//!	- if thisCompare(x, y) returns COMPARE_LESS, and
//!		thisCompare(y, z) does not return COMPARE_GREATER, then
//!		thisCompare(x, z) must return COMPARE_LESS;
//!	- if thisCompare(x, y) returns COMPARE_EQUAL, and
//!		thisCompare(y, z) returns COMPARE_EQUAL, then
//!		thisCompare(x, z) must return COMPARE_EQUAL;
//!	.
//!	If these requirements are not satisfied, the behaviour and the content
//!	of the Vector are unpredictable.
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	INLINE	void	OrderedVector<BASE_TYPE>::SortIndices(const
				Vector<BASE_TYPE>& thisVector,
				Vector<std_uint>& IndexVector,
				CompareFunctionType thisCompare)
				throw(FatalException)
		{
		if (thisCompare == static_cast<CompareFunctionType>(NULL))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		if (static_cast<const void *>(&thisVector) ==
			static_cast<void *>(&IndexVector))
			throw make_fatal_exception(ILLEGAL_ARGUMENT);
		OrderedVector<BASE_TYPE>(thisCompare).HeapSort(thisVector,
			IndexVector);
		}

}
