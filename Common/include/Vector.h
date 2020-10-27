////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	14/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the data_structure_space::Vector class
//!	template.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined VECTOR_H

# define	VECTOR_H

# include	"FatalException.h"

namespace	data_structure_space
{

using	namespace	utility_space;

//! \def	DEFAULT_VECTOR_SIZE
//!	Default size for Vector creation.
# define	DEFAULT_VECTOR_SIZE			100

//! \def	VECTOR_GROWTH_NUMERATOR
//!	Numerator for vector growth ratio \n.
//!	During Append operation, when index reaches Vector size, the size is
//!	is multiplied for VECTOR_GROWTH_NUMERATOR / VECTOR_GROWTH_DENOMINATOR.
# define	VECTOR_GROWTH_NUMERATOR			3

//! \def	VECTOR_GROWTH_DENOMINATOR
//!	Denominator for vector growth ratio \n.
//!	During Append operation, when index reaches Vector size, the size is
//!	is multiplied for VECTOR_GROWTH_NUMERATOR / VECTOR_GROWTH_DENOMINATOR.
# define	VECTOR_GROWTH_DENOMINATOR		2

//! \def	MAX_ADDED_COPIES
//!	Maximum number of copies that can be inserted in a Vector in a single
//!	operation.
# define	MAX_ADDED_COPIES			(STD_UINT_MAX / 2)

template<class SORTED_BASE_TYPE>	class OrderedVector;

////////////////////////////////////////////////////////////////////////////////
//! \class	Vector
//!	The Vector class template represents a growable array of objects. Like
//!	an array, it contains components that can be accessed using an integer
//!	index, but its size grows automatically to accommodate new items.
//!
//! \tparam	BASE_TYPE		Class of the elements; it can be any
//!					class or built-in type, which has the
//!					following accessible methods (either by
//!					default or explicitly declared):
//!					- constructor without arguments,
//!					- destructor,
//!					- assignment operator,
//!					- new [] operator,
//!					- delete [] operator.
//!					.
//!					The constructor, assignment operator and
//!					new [] operator can throw an
//!					utility_space::OUT_OF_MEMORY
//!					FatalException; the destructor and
//!					delete [] operator shall not throw any
//!					exception.
//!
//! \see	OrderedVector		Declared as friend to allow access to
//!					GetStore.
//! \see	Set			Declared as friend to allow access to
//!					GetStore.
//!
//! \see	DEFAULT_VECTOR_SIZE
//! \see	VECTOR_GROWTH_NUMERATOR
//! \see	VECTOR_GROWTH_DENOMINATOR
//!
////////////////////////////////////////////////////////////////////////////////

template<class BASE_TYPE>
	class	Vector
	{
	template<class SORTED_BASE_TYPE>
		friend	class	OrderedVector;

	template<class ELEMENT_TYPE>
		friend	class	Set;

	private:

//! \property Store
//!	Storage that contains the Vector elements.
				BASE_TYPE*	Store;

//! \property Size
//!	Number of allocated elements in the Vector.
				std_uint	Size;

//! \property Present
//!	Number of existing elements in the Vector.
				std_uint	Present;

				void		Free(void) noexcept;

				void		MakeCopy(const Vector&
							thisVector)
							throw(FatalException);

				void		Grow(void)
							throw(FatalException);

		static		void		Copy(register BASE_TYPE* Target,
							register const
							BASE_TYPE* Source,
							std_uint NumElements)
							noexcept;

	protected:

				BASE_TYPE*	GetStore(void) noexcept;

			const	BASE_TYPE*	GetStore(void) const noexcept;

				void		SetPresent(std_uint thisPresent)
							throw(FatalException);

	public:

						Vector(void)
							throw(FatalException);

				explicit	Vector(std_uint thisSize)
							throw(FatalException);

						Vector(const BASE_TYPE& Value,
							std_uint thisSize)
							throw(FatalException);

						Vector(const Vector& thisVector,
							std_uint StartIndex,
							std_uint NumElements)
							throw(FatalException);

						Vector(const Vector& thisVector)
							throw(FatalException);

						Vector(Vector&& thisVector)
							throw(FatalException);

						~Vector(void) noexcept;

				Vector&		operator = (const Vector&
							thisVector)
							throw(FatalException);

				Vector&		operator = (Vector&& thisVector)
							noexcept;

				BASE_TYPE&	operator [] (std_uint Index)
							throw(FatalException);

			const	BASE_TYPE&	operator [] (std_uint Index)
							const
							throw(FatalException);

				std_uint	GetSize(void) const noexcept;

				std_uint	GetPresent(void) const noexcept;

				bool		IsEmpty(void) const noexcept;

				void		Clear(void) noexcept;

				void		Append(const BASE_TYPE& Value)
							throw(FatalException);

				void		Append(const BASE_TYPE& Value,
							std_uint NumCopies)
							throw(FatalException);

				void		Append(const Vector& thisVector)
							throw(FatalException);

				void		Append(const Vector& thisVector,
							std_uint StartIndex,
							std_uint NumElements)
							throw(FatalException);

				void		Replace(const BASE_TYPE &Value,
							std_uint Index)
							throw(FatalException);

				void		Insert(register const
							BASE_TYPE& Value,
							register std_uint Index)
							throw(FatalException);

				void		Insert(register const
							BASE_TYPE& Value,
							register std_uint
							StartIndex,
							register std_uint
							NumCopies)
							throw(FatalException);

				void		RemoveRear(std_uint NumElements)
							throw(FatalException);

				void		Remove(std_uint StartIndex)
							throw(FatalException);

				void		Remove(std_uint StartIndex,
							std_uint NumElements)
							throw(FatalException);

				void		Resize(std_uint NewSize)
							throw(FatalException);

				void		Trim(void)
							throw(FatalException);

	};

}

# include	"Vector.tpl"

# endif
