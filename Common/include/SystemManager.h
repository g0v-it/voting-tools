////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	31/10/2018
//!
//! \par	Function:
//!	Contains the declaration of the system_space::SystemManager abstract
//!	class.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined SYSTEM_MANAGER_H

# define	SYSTEM_MANAGER_H

//! \def	MILLISECONDS_PER_SECOND
//!	Number of milliseconds per second.
# define	MILLISECONDS_PER_SECOND		1000

//! \def	SECONDS_PER_MINUTE
//!	Number of second per minute.
# define	SECONDS_PER_MINUTE		60

//! \def	MILLISECONDS_PER_MINUTE
//!	Number of milliseconds per minute.
//!
//! \see	SECONDS_PER_MINUTE
//! \see	MILLISECONDS_PER_SECOND
# define	MILLISECONDS_PER_MINUTE \
	(SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND)

//! \def	NANOSECONDS_PER_MILLISECOND
//!	Number of nanoseconds per millisecond.
# define	NANOSECONDS_PER_MILLISECOND	1000000

//! \def	NANOSECONDS_PER_SECOND
//!	Number of nanoseconds per second.
//!
//! \see	MILLISECONDS_PER_SECOND
//! \see	NANOSECONDS_PER_MILLISECOND
# define	NANOSECONDS_PER_SECOND \
	(MILLISECONDS_PER_SECOND * NANOSECONDS_PER_MILLISECOND)

namespace	system_space
{

////////////////////////////////////////////////////////////////////////////////
//! \class	SystemManager
//!	Abstract class, which declares all the basic system related services as
//!	pure virtual functions. \n
//!	Services are implemented for every system through a concrete OS specific
//!	derived class. \n
//!	The SystemManager class is a singleton. The class defines the
//!	GetInstance function, which returns the pointer to current SystemManager
//!	object.
//!
////////////////////////////////////////////////////////////////////////////////

class	SystemManager
	{
	private:

					SystemManager(const SystemManager&
						thisSystemManager) = delete;

					SystemManager(SystemManager&&
						thisSystemManager) = delete;

			SystemManager&	operator = (const SystemManager&
						thisSystemManager) = delete;

			SystemManager&	operator = (SystemManager&&
						thisSystemManager) = delete;

	protected:

//! \property	ApplicationStartTime
//!	Application start time, that is the time, in nanoseconds, from an
//!	unspecified, but fixed, epoch.
			std_ulong	ApplicationStartTime;

		explicit		SystemManager(void) noexcept;

		virtual			~SystemManager(void) noexcept;

	public:

		virtual	std_ulong	GetSystemTime(void) const noexcept =
						PURE_VIRTUAL;

		virtual	std_ulong	GetApplicationTime(void) const noexcept;

		virtual	std_ulong	GetApplicationCPUTime(void) const
						noexcept = PURE_VIRTUAL;

		virtual void		Sleep(std_uint SleepTime) const
						noexcept = PURE_VIRTUAL;

		static	SystemManager*	GetInstance(void) noexcept;

	};

}

# if	defined USE_INLINE
# include	"SystemManager.inl"
# endif

# endif
