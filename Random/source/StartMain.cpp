////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	29/04/2018
//!
//! \par	Function:
//!	Contains the definition of static data and functions of the election
//!	starting program.
//!
////////////////////////////////////////////////////////////////////////////////

# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>

# include	"Standard.h"
# include	"Parameter.h"
# include	"Message.h"
# include	"FatalException.h"
# include	"IOException.h"
# include	"ApplicationException.h"
# include	"ExceptionHandler.h"
# include	"GenericString.h"
# include	"Utility.h"
# include	"File.h"
# include	"LocalUtility.h"
# include	"State.h"

using	namespace	utility_space;
using	namespace	data_structure_space;
using	namespace	io_space;

static	void	Usage(void) throw(IOException);

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Write on stdout a message explaining the usage of the program.
//!
//! \throw	io_space::STDOUT_WRITE_ERROR	If writing on stdout fails.
//!
//! \returns	None.
//!
//! \see	START_USAGE_FORMAT
//! \see	NUMERIC_ERROR_OPTION
//! \see	HASH_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	DEFAULT_STDOUT_PATHNAME
//!
////////////////////////////////////////////////////////////////////////////////

static	void	Usage(void) throw(IOException)
	{
	if (printf(START_USAGE_FORMAT, NUMERIC_ERROR_OPTION, HASH_LENGTH,
		SIGNATURE_LENGTH) < 0)
		throw make_IO_exception(FILE_WRITE_ERROR,
			CharString(DEFAULT_STDOUT_PATHNAME));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Main program for election starting.\n
//!	It stores the hashed key of a guarantor, along with its optional
//!	signature.
//!
//! \param	argc	Number of command line arguments.
//! \param	argv	Array of command line arguments.
//!	
//! \throw	None.
//!
//! \returns	int	A code indicating whether the program terminated
//!			correctly or not.
//!
//! \see	GUARANTOR_RECORD_LENGTH
//! \see	GUARANTOR_HASH_OFFSET
//! \see	HASH_LENGTH
//! \see	SIGNATURE_LENGTH
//! \see	GUARANTOR_HASH_SET_FORMAT
//! \see	ALL_GUARANTORS_HASH_MESSAGE 
//! \see	MISSING_GUARANTORS_HASH_FORMAT
//! \see	ALL_GUARANTORS_HASH_MESSAGE
//! \see	DEFAULT_STDOUT_PATHNAME
//!
//! \fileformat
//! \see	GuarantorsFileFormat
//!
////////////////////////////////////////////////////////////////////////////////

int	main(int argc, char* argv [])
	{
	try
		{
		std_uint	Guarantor;
		CharString	DirectoryPath;
		CharString	PathName;
		StateInfo	ElectionState;
		File		GuarantorFile;
		byte		GuarantorData [GUARANTOR_RECORD_LENGTH];
		byte		Hash [HASH_LENGTH];
		byte		Signature [SIGNATURE_LENGTH];
		byte		Zero [HASH_LENGTH];

		HandleOptions(argc, argv);
		if (argc < 4 || argc > 5)
			{
			Usage();
			return EXIT_FAILURE;
			}
		DirectoryPath = CharString(argv [1]);
		Guarantor = DecodeInteger(argv [2]);
		DecodeHex(argv [3], Hash, HASH_LENGTH);
		if (argc == 5)
			DecodeHex(argv [4], Signature, SIGNATURE_LENGTH);
		ignore_value(memset(Zero, 0, HASH_LENGTH));
		if (memcmp(Hash, Zero, HASH_LENGTH) == 0)
			throw make_application_exception(INVALID_HASH);
		GetState(DirectoryPath, ElectionState);
		if (ElectionState.State != ELECTION_CREATED)
			throw make_application_exception(INVALID_STATE);
		if (Guarantor == 0 or Guarantor > ElectionState.Guarantors)
			throw make_application_exception(INVALID_GUARANTOR);
		PathName = MakeGuarantorsPathName(DirectoryPath);
		GuarantorFile.OpenBinary(PathName, OPEN_UPDATE);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		GuarantorFile.Lock(GUARANTOR_RECORD_LENGTH);
		if (GuarantorFile.Read(GuarantorData, GUARANTOR_RECORD_LENGTH,
			1) != 1)
			throw make_IO_exception(FILE_READ_ERROR, PathName);
		if (memcmp(GuarantorData + GUARANTOR_HASH_OFFSET, Zero,
			HASH_LENGTH) != 0)
			throw make_application_exception(
				GUARANTOR_KEY_ALREADY_SET);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH +
			GUARANTOR_HASH_OFFSET, FILE_SEEK_SET);
		GuarantorFile.Write(Hash, HASH_LENGTH, 1);
		if (argc == 5)
			GuarantorFile.Write(Signature, SIGNATURE_LENGTH, 1);
		GuarantorFile.Seek((Guarantor - 1) * GUARANTOR_RECORD_LENGTH,
			FILE_SEEK_SET);
		GuarantorFile.Unlock(GUARANTOR_RECORD_LENGTH);
		GuarantorFile.Close();
		if (printf(GUARANTOR_HASH_SET_FORMAT, Guarantor) < 0)
			throw make_IO_exception(FILE_WRITE_ERROR,
				CharString(DEFAULT_STDOUT_PATHNAME));
		if (--ElectionState.MissingGuarantors == 0)
			{
			if (printf(ALL_GUARANTORS_HASH_MESSAGE) < 0)
				throw make_IO_exception(FILE_WRITE_ERROR,
					CharString(DEFAULT_STDOUT_PATHNAME));
			}
		else
			PrintMissingGuarantorsHash(ElectionState.
				MissingGuarantors);
		}
	catch (ExceptionBase& Exc)
		{
		ExceptionHandler::GetInstance().HandleException(Exc);
		}
	return EXIT_SUCCESS;
	}
