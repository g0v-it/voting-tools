////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	02/11/2018
//!
//! \par	Function:
//!	Contains the declarations of the system_space::LinuxSystemManager class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined LINUX_SYSTEM_MANAGER_H

# define	LINUX_SYSTEM_MANAGER_H

# include	"SystemManager.h"

# include	<unistd.h>

namespace	system_space
{

////////////////////////////////////////////////////////////////////////////////
//! /class	LinuxSystemManager
//!	This singleton class is a concrete class derived from SystemManager,
//!	implementing all Linux specific system services.
//!
//! \see	SystemManager::GetInstance	Declared as friend to allow
//!						access to constructor.
//!
////////////////////////////////////////////////////////////////////////////////

class	LinuxSystemManager: public SystemManager
	{

		friend	SystemManager*	SystemManager::GetInstance(void);

	private:

//! \property	TicksPerSecond
//!	Number of ticks per second. \n
//!	It is never modified after instance creation.
		const	std_uint	TicksPerSecond;

					LinuxSystemManager(void) noexcept;

					LinuxSystemManager(const
						LinuxSystemManager& thisSystem)
						noexcept = delete;

			LinuxSystemManager&	operator = (const
					LinuxSystemManager& thisSystem)
						noexcept = delete;

			LinuxSystemManager&	operator = (
					LinuxSystemManager&& thisSystem)
						noexcept = delete;

	public:

		virtual			~LinuxSystemManager(void) noexcept;

		virtual	std_ulong	GetSystemTime(void) const noexcept;

		virtual	std_ulong	GetApplicationCPUTime(void) const
						noexcept;

		virtual void		Sleep(std_uint SleepTime) const
						noexcept;

	};

}

# if	defined USE_INLINE
# include	"LinuxSystemManager.inl"
# endif

# endif
