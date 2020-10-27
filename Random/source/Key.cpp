////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	14/05/2018
//!
//! \par	Function:
//!	Contains the definition of the ComputeKey function.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<string.h>

# include	"Standard.h"
# include	"File.h"
# include	"Key.h"
# include	"LocalUtility.h"

namespace	application_space
{

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Compute the exclusive or of all guarantors' keys.
//!
//! \param	DirectoryPath				Path of the directory
//!							containing the files of
//!							the election.
//! \param	Guarantors				Number of guarantors.
//! \param	GuarantorsKey				Array that upon return
//!							will contain the
//!							exclusive or of all
//!							guarantors' keys.
//!
//! \throw	utility_space::OUT_OF_MEMORY		If memory allocation
//!							fails.
//! \throw	io_space::FILE_INVALID_PATH_NAME	If the path name is not
//!							valid.
//! \throw	io_space::FILE_IO_ERROR			If an I/O error occurs.
//! \throw	io_space::FILE_DOES_NOT_EXIST		If the guarantors file
//!							does not exist.
//! \throw	io_space::FILE_PERMISSION_DENIED	If user has no
//!							permission to open the
//!							guarantors file or if
//!							the path name
//!							corresponds to a
//!							directory.
//! \throw	io_space::FILE_READ_ERROR		If an error occurs while
//!							reading the guarantors
//!							file.
//! \throw	io_space::FILE_CLOSE_ERROR		If an error occurs while
//!							closing the guarantors
//!							file.
//! \throw	io_space::FILE_SEEK_ERROR		If the guarantors file
//!							cannot be seeked.
//!
//! \returns	None.
//!
//! \see	KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	ComputeKey(const CharString& DirectoryPath,
		register std_uint Guarantors,
		register byte GuarantorsKey [KEY_LENGTH])
		throw(FatalException, IOException)
	{
	register	std_uint	Index;
			CharString	PathName;
			File		GuarantorFile;
			byte		Key [KEY_LENGTH];

	ignore_value(memset(GuarantorsKey, 0, KEY_LENGTH));
	PathName = MakeGuarantorsPathName(DirectoryPath);
	GuarantorFile.OpenBinary(PathName, OPEN_READ);
	for (Index = 0; Index < Guarantors; ++Index)
		{
		GuarantorFile.Seek(Index * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		if (GuarantorFile.Read(Key, KEY_LENGTH, 1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		MixKeys(Key, GuarantorsKey);
		}
	GuarantorFile.Close();
	}

}
