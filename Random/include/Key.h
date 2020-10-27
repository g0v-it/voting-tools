////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	14/05/2018
//!
//! \par	Function:
//!	Contains the declaration of the ComputeKey function.
//!
////////////////////////////////////////////////////////////////////////////////

# if	!defined KEY_H
# define	KEY_H

# include	"Parameter.h"
# include	"GenericString.h"
# include	"State.h"

namespace	application_space
{

void	ComputeKey(const CharString& DirectoryPath,
		register std_uint Guarantors,
		register byte GuarantorsKey [KEY_LENGTH])
		throw(FatalException, IOException);

}

# endif

