////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	30/04/2018
//!
//! \par	Function:
//!	Contains the declaration of the hash function.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined HASH_H
# define	HASH_H

# include	"Parameter.h"

namespace	application_space
{

void	ComputeHash(const byte Key [KEY_LENGTH],
		register byte Hash [HASH_LENGTH]) noexcept;

}

# endif
