////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	02/11/2018
//!
//! \par	Function:
//!	Contains the definitions of non inline functions of the
//!	system_space::LinuxSystemManager class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<time.h>
# include	<sys/times.h>
# include	"Standard.h"
# include	"LinuxSystemManager.h"

# if	!defined USE_INLINE
# include	"LinuxSystemManager.inl"
# endif

//! \def	NANOSLEEP_OK
//!	Value returned by nanosleep when the function returns because the
//!	sleeping time expires.
# define	NANOSLEEP_OK			0

namespace	system_space
{

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Destructor. Deallocate thread key space.
//!
//! \throw	None.
//!
//! \returns	Not applicable.
//!
////////////////////////////////////////////////////////////////////////////////

LinuxSystemManager::~LinuxSystemManager(void) noexcept
	{
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the current system time, that is the time, in nanoseconds, from
//!	an unspecified, but fixed, epoch.
//!
//! \throw	None.
//!
//! \returns	std_ulong	The current system time.
//!
//! \see	NANOSECONDS_PER_SECOND
//!
////////////////////////////////////////////////////////////////////////////////

std_ulong	LinuxSystemManager::GetSystemTime(void) const noexcept
	{
	struct	timespec	ts;

	ignore_value(clock_gettime(CLOCK_REALTIME, &ts));
	return ts.tv_sec * NANOSECONDS_PER_SECOND + ts.tv_nsec;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Get the CPU time used by the process, in nanonseconds.
//!
//! \throw	None.
//!
//! \returns	TimeSpan	The used CPU time.
//!
//! \note
//!	If the system cannot determine the CPU time, the function returns
//!	STD_ULONG_MAX.
//!
//! \see	NANOSECONDS_PER_SECOND
//! \see	STD_ULONG_MAX
//!
////////////////////////////////////////////////////////////////////////////////

std_ulong	LinuxSystemManager::GetApplicationCPUTime(void) const noexcept
	{
	struct	tms	TimeStructure;
	std_ulong	Ticks;

	if (times(&TimeStructure) == static_cast<clock_t>(-1))
		return STD_ULONG_MAX;
	Ticks = static_cast<std_ulong>(TimeStructure.tms_utime) +
		static_cast<std_ulong>(TimeStructure.tms_stime);

		// Round the time value to nearest nanosecond.
	return Ticks / TicksPerSecond * NANOSECONDS_PER_SECOND +
		(Ticks % TicksPerSecond * NANOSECONDS_PER_SECOND +
		TicksPerSecond / 2) / TicksPerSecond;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Cause the process to sleep for a given time.
//!
//! \param	SleepTime	Sleep time, in milliseconds.
//!
//! \throw	None.
//!
//! \returns	None
//!
//! \see	NANOSLEEP_OK
//!
////////////////////////////////////////////////////////////////////////////////

void	LinuxSystemManager::Sleep(std_uint SleepTime) const noexcept
	{
	struct	timespec	TimeStruct;
	struct	timespec	RemainingTime;

	TimeStruct.tv_sec = SleepTime / MILLISECONDS_PER_SECOND;
	TimeStruct.tv_nsec = SleepTime % MILLISECONDS_PER_SECOND *
		NANOSECONDS_PER_MILLISECOND;
	while (nanosleep(&TimeStruct, &RemainingTime) != NANOSLEEP_OK)
		TimeStruct = RemainingTime;
	}

}
