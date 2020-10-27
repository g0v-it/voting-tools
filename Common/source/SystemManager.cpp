////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	31/10/2018
//!
//! \par	Function:
//!	Contains the implementation of non inline functions of the
//!	system_space::SystemManager abstract class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"SystemManager.h"
# include	"ActualSystemManager.h"

# if	!defined USE_INLINE
# include	"SystemManager.inl"
# endif

namespace	system_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Default destructor.
//!
//! \throw	None.
//!
//! \return	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

SystemManager::~SystemManager(void) noexcept
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Return the time elapsed since application start.
//!
//! \throw	None.
//!
//! \return	std_ulong	Time elapsed since application start.
//!
////////////////////////////////////////////////////////////////////////////////

std_ulong	SystemManager::GetApplicationTime(void) const noexcept
	{
	return GetSystemTime() - ApplicationStartTime;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Returns a pointer to the singleton instance of the SystemManager object,
//!	depending upon actual SystemManager. \n
//!	The instance is created as a static member of the function, instead of
//!	static member of the class. Though this is a little inefficient, it
//!	ensures the order of creation of objects.
//!
//! \throw	None.
//!
//! \returns	SystemManager*	Pointer to current SystemManager object.
//!
////////////////////////////////////////////////////////////////////////////////

SystemManager*	SystemManager::GetInstance(void) noexcept
	{
	static	ActualSystemManager	SystemManagerInstance;

	return &SystemManagerInstance;
	}

}
