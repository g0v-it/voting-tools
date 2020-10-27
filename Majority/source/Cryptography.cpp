////////////////////////////////////////////////////////////////////////////////
//! \file
//!
//! \author	Mauro Fiorentini
//!
//! \date	19/04/2018
//!
//!	It contains the definitions of static attributes and non inline
//!	functions of the utility_space::Cryptography class.
//!
////////////////////////////////////////////////////////////////////////////////

# include	"Standard.h"
# include	"Cryptography.h"

# if !defined	USE_INLINE
# include	"Cryptography.inl"
# endif

//! \def	KEY_SHUFFLING_STEPS
//!	Number of key shuffling steps
# define	KEY_SHUFFLING_STEPS		8

#include	<stdio.h>
namespace	utility_space
{

const	std_uint	Cryptography::ModuleTable [WORD_FEISTEL_STEPS] =
	{
	4284967259,
	4254967259,
	4194967291,
	4164967243,
	4124967293,
	4224967291,
	4274967293,
	4294967291,
	};

const	byte	Cryptography::SubsTable [BYTE_MAX + 1] =
	{
	0xA9, 0x38, 0x1C, 0x82, 0x4A, 0x02, 0x67, 0x29,
	0xBA, 0xDC, 0x33, 0xE4, 0x21, 0x1F, 0x96, 0x65,
	0xDB, 0xF6, 0x94, 0x2C, 0x5E, 0xBF, 0x40, 0x75,
	0x62, 0xF5, 0x53, 0x92, 0x7A, 0xA7, 0x27, 0x7E,
	0xA8, 0xD4, 0x3B, 0xBC, 0x46, 0xC6, 0x81, 0x9F,
	0x10, 0xCF, 0x35, 0xAC, 0x0C, 0xC9, 0x5D, 0x98,
	0xFC, 0x1A, 0xDA, 0x5B, 0x74, 0xB4, 0xCD, 0x31,
	0xA5, 0x63, 0xDE, 0x4D, 0x15, 0xAB, 0x2E, 0xB8,
	0xD5, 0xB3, 0x6A, 0x9C, 0x14, 0xE5, 0x1B, 0x56,
	0x93, 0x66, 0x0A, 0xCC, 0x59, 0x23, 0x39, 0xD0,
	0x07, 0x7B, 0x25, 0xA4, 0x1D, 0x97, 0x9D, 0x0F,
	0xEB, 0x8E, 0xD7, 0xAE, 0xEF, 0xE2, 0xF2, 0xA6,
	0x71, 0xA1, 0x50, 0x55, 0x37, 0x64, 0x3D, 0x19, 
	0x91, 0x77, 0x42, 0x0B, 0xFA, 0x52, 0xE0, 0xC8,
	0xAD, 0x6C, 0xED, 0xCB, 0xD6, 0xB0, 0x86, 0xE7,
	0x43, 0x9A, 0x88, 0x03, 0xE8, 0x99, 0x57, 0x2A,
	0xC4, 0x08, 0xFB, 0x0D, 0x6F, 0xF9, 0x17, 0x78,
	0xE1, 0xD2, 0x7F, 0x80, 0x49, 0x2D, 0x8C, 0x60,
	0xF4, 0xB9, 0x01, 0xB2, 0x6B, 0x5F, 0xB7, 0x28,
	0xC5, 0x4C, 0xD3, 0x3A, 0xC3, 0x73, 0x47, 0x76,
	0xEE, 0xF0, 0x69, 0xE9, 0x20, 0x5C, 0x18, 0x4F,
	0x09, 0xAA, 0x12, 0xEA, 0x87, 0x16, 0x3E, 0x61,
	0x89, 0xFD, 0xD1, 0x7D, 0x9E, 0xBD, 0x36, 0x4E,
	0xB6, 0xDD, 0x3C, 0x6E, 0x9B, 0xC7, 0xF7, 0xFE,
	0xE6, 0x48, 0x6D, 0xFF, 0xEC, 0x83, 0x32, 0x70,
	0x22, 0x00, 0x5A, 0x44, 0xE3, 0x72, 0x79, 0x68,
	0xC2, 0x06, 0xB1, 0xF3, 0xC1, 0x05, 0x8A, 0x30,
	0xBB, 0x58, 0x26, 0xCA, 0x24, 0xD9, 0x7C, 0x11,
	0x2B, 0xB5, 0x1E, 0xA0, 0x34, 0x8D, 0xF1, 0x90,
	0x04, 0x41, 0xAF, 0x13, 0x4B, 0x0E, 0x54, 0xD8,
	0x84, 0xA3, 0x8B, 0xDF, 0x3F, 0xCE, 0x85, 0xA2,
	0xF8, 0x45, 0xC0, 0xBE, 0x8F, 0x95, 0x51, 0x2F,
	};

const	std_uint	Cryptography::DiffuseTable [sizeof(std_uint)]
				[BYTE_MAX + 1] =
	{
		{
		0x00000000, 0x00000008, 0x00000100, 0x00000108,
		0x00020000, 0x00020008, 0x00020100, 0x00020108,
		0x01000000, 0x01000008, 0x01000100, 0x01000108,
		0x01020000, 0x01020008, 0x01020100, 0x01020108,
		0x00000080, 0x00000088, 0x00000180, 0x00000188,
		0x00020080, 0x00020088, 0x00020180, 0x00020188,
		0x01000080, 0x01000088, 0x01000180, 0x01000188,
		0x01020080, 0x01020088, 0x01020180, 0x01020188,
		0x00004000, 0x00004008, 0x00004100, 0x00004108,
		0x00024000, 0x00024008, 0x00024100, 0x00024108,
		0x01004000, 0x01004008, 0x01004100, 0x01004108,
		0x01024000, 0x01024008, 0x01024100, 0x01024108,
		0x00004080, 0x00004088, 0x00004180, 0x00004188,
		0x00024080, 0x00024088, 0x00024180, 0x00024188,
		0x01004080, 0x01004088, 0x01004180, 0x01004188,
		0x01024080, 0x01024088, 0x01024180, 0x01024188,
		0x00200000, 0x00200008, 0x00200100, 0x00200108,
		0x00220000, 0x00220008, 0x00220100, 0x00220108,
		0x01200000, 0x01200008, 0x01200100, 0x01200108,
		0x01220000, 0x01220008, 0x01220100, 0x01220108,
		0x00200080, 0x00200088, 0x00200180, 0x00200188,
		0x00220080, 0x00220088, 0x00220180, 0x00220188,
		0x01200080, 0x01200088, 0x01200180, 0x01200188,
		0x01220080, 0x01220088, 0x01220180, 0x01220188,
		0x00204000, 0x00204008, 0x00204100, 0x00204108,
		0x00224000, 0x00224008, 0x00224100, 0x00224108,
		0x01204000, 0x01204008, 0x01204100, 0x01204108,
		0x01224000, 0x01224008, 0x01224100, 0x01224108,
		0x00204080, 0x00204088, 0x00204180, 0x00204188,
		0x00224080, 0x00224088, 0x00224180, 0x00224188,
		0x01204080, 0x01204088, 0x01204180, 0x01204188,
		0x01224080, 0x01224088, 0x01224180, 0x01224188,
		0x10000000, 0x10000008, 0x10000100, 0x10000108,
		0x10020000, 0x10020008, 0x10020100, 0x10020108,
		0x11000000, 0x11000008, 0x11000100, 0x11000108,
		0x11020000, 0x11020008, 0x11020100, 0x11020108,
		0x10000080, 0x10000088, 0x10000180, 0x10000188,
		0x10020080, 0x10020088, 0x10020180, 0x10020188,
		0x11000080, 0x11000088, 0x11000180, 0x11000188,
		0x11020080, 0x11020088, 0x11020180, 0x11020188,
		0x10004000, 0x10004008, 0x10004100, 0x10004108,
		0x10024000, 0x10024008, 0x10024100, 0x10024108,
		0x11004000, 0x11004008, 0x11004100, 0x11004108,
		0x11024000, 0x11024008, 0x11024100, 0x11024108,
		0x10004080, 0x10004088, 0x10004180, 0x10004188,
		0x10024080, 0x10024088, 0x10024180, 0x10024188,
		0x11004080, 0x11004088, 0x11004180, 0x11004188,
		0x11024080, 0x11024088, 0x11024180, 0x11024188,
		0x10200000, 0x10200008, 0x10200100, 0x10200108,
		0x10220000, 0x10220008, 0x10220100, 0x10220108,
		0x11200000, 0x11200008, 0x11200100, 0x11200108,
		0x11220000, 0x11220008, 0x11220100, 0x11220108,
		0x10200080, 0x10200088, 0x10200180, 0x10200188,
		0x10220080, 0x10220088, 0x10220180, 0x10220188,
		0x11200080, 0x11200088, 0x11200180, 0x11200188,
		0x11220080, 0x11220088, 0x11220180, 0x11220188,
		0x10204000, 0x10204008, 0x10204100, 0x10204108,
		0x10224000, 0x10224008, 0x10224100, 0x10224108,
		0x11204000, 0x11204008, 0x11204100, 0x11204108,
		0x11224000, 0x11224008, 0x11224100, 0x11224108,
		0x10204080, 0x10204088, 0x10204180, 0x10204188,
		0x10224080, 0x10224088, 0x10224180, 0x10224188,
		0x11204080, 0x11204088, 0x11204180, 0x11204188,
		0x11224080, 0x11224088, 0x11224180, 0x11224188
		},
		{
		0x00000000, 0x00000010, 0x00000800, 0x00000810,
		0x00040000, 0x00040010, 0x00040800, 0x00040810,
		0x02000000, 0x02000010, 0x02000800, 0x02000810,
		0x02040000, 0x02040010, 0x02040800, 0x02040810,
		0x00000001, 0x00000011, 0x00000801, 0x00000811,
		0x00040001, 0x00040011, 0x00040801, 0x00040811,
		0x02000001, 0x02000011, 0x02000801, 0x02000811,
		0x02040001, 0x02040011, 0x02040801, 0x02040811,
		0x00008000, 0x00008010, 0x00008800, 0x00008810,
		0x00048000, 0x00048010, 0x00048800, 0x00048810,
		0x02008000, 0x02008010, 0x02008800, 0x02008810,
		0x02048000, 0x02048010, 0x02048800, 0x02048810,
		0x00008001, 0x00008011, 0x00008801, 0x00008811,
		0x00048001, 0x00048011, 0x00048801, 0x00048811,
		0x02008001, 0x02008011, 0x02008801, 0x02008811,
		0x02048001, 0x02048011, 0x02048801, 0x02048811,
		0x00400000, 0x00400010, 0x00400800, 0x00400810,
		0x00440000, 0x00440010, 0x00440800, 0x00440810,
		0x02400000, 0x02400010, 0x02400800, 0x02400810,
		0x02440000, 0x02440010, 0x02440800, 0x02440810,
		0x00400001, 0x00400011, 0x00400801, 0x00400811,
		0x00440001, 0x00440011, 0x00440801, 0x00440811,
		0x02400001, 0x02400011, 0x02400801, 0x02400811,
		0x02440001, 0x02440011, 0x02440801, 0x02440811,
		0x00408000, 0x00408010, 0x00408800, 0x00408810,
		0x00448000, 0x00448010, 0x00448800, 0x00448810,
		0x02408000, 0x02408010, 0x02408800, 0x02408810,
		0x02448000, 0x02448010, 0x02448800, 0x02448810,
		0x00408001, 0x00408011, 0x00408801, 0x00408811,
		0x00448001, 0x00448011, 0x00448801, 0x00448811,
		0x02408001, 0x02408011, 0x02408801, 0x02408811,
		0x02448001, 0x02448011, 0x02448801, 0x02448811,
		0x20000000, 0x20000010, 0x20000800, 0x20000810,
		0x20040000, 0x20040010, 0x20040800, 0x20040810,
		0x22000000, 0x22000010, 0x22000800, 0x22000810,
		0x22040000, 0x22040010, 0x22040800, 0x22040810,
		0x20000001, 0x20000011, 0x20000801, 0x20000811,
		0x20040001, 0x20040011, 0x20040801, 0x20040811,
		0x22000001, 0x22000011, 0x22000801, 0x22000811,
		0x22040001, 0x22040011, 0x22040801, 0x22040811,
		0x20008000, 0x20008010, 0x20008800, 0x20008810,
		0x20048000, 0x20048010, 0x20048800, 0x20048810,
		0x22008000, 0x22008010, 0x22008800, 0x22008810,
		0x22048000, 0x22048010, 0x22048800, 0x22048810,
		0x20008001, 0x20008011, 0x20008801, 0x20008811,
		0x20048001, 0x20048011, 0x20048801, 0x20048811,
		0x22008001, 0x22008011, 0x22008801, 0x22008811,
		0x22048001, 0x22048011, 0x22048801, 0x22048811,
		0x20400000, 0x20400010, 0x20400800, 0x20400810,
		0x20440000, 0x20440010, 0x20440800, 0x20440810,
		0x22400000, 0x22400010, 0x22400800, 0x22400810,
		0x22440000, 0x22440010, 0x22440800, 0x22440810,
		0x20400001, 0x20400011, 0x20400801, 0x20400811,
		0x20440001, 0x20440011, 0x20440801, 0x20440811,
		0x22400001, 0x22400011, 0x22400801, 0x22400811,
		0x22440001, 0x22440011, 0x22440801, 0x22440811,
		0x20408000, 0x20408010, 0x20408800, 0x20408810,
		0x20448000, 0x20448010, 0x20448800, 0x20448810,
		0x22408000, 0x22408010, 0x22408800, 0x22408810,
		0x22448000, 0x22448010, 0x22448800, 0x22448810,
		0x20408001, 0x20408011, 0x20408801, 0x20408811,
		0x20448001, 0x20448011, 0x20448801, 0x20448811,
		0x22408001, 0x22408011, 0x22408801, 0x22408811,
		0x22448001, 0x22448011, 0x22448801, 0x22448811
		},
		{
		0x00000000, 0x00000020, 0x00001000, 0x00001020,
		0x00080000, 0x00080020, 0x00081000, 0x00081020,
		0x04000000, 0x04000020, 0x04001000, 0x04001020,
		0x04080000, 0x04080020, 0x04081000, 0x04081020,
		0x00000002, 0x00000022, 0x00001002, 0x00001022,
		0x00080002, 0x00080022, 0x00081002, 0x00081022,
		0x04000002, 0x04000022, 0x04001002, 0x04001022,
		0x04080002, 0x04080022, 0x04081002, 0x04081022,
		0x00000100, 0x00000120, 0x00001100, 0x00001120,
		0x00080100, 0x00080120, 0x00081100, 0x00081120,
		0x04000100, 0x04000120, 0x04001100, 0x04001120,
		0x04080100, 0x04080120, 0x04081100, 0x04081120,
		0x00000102, 0x00000122, 0x00001102, 0x00001122,
		0x00080102, 0x00080122, 0x00081102, 0x00081122,
		0x04000102, 0x04000122, 0x04001102, 0x04001122,
		0x04080102, 0x04080122, 0x04081102, 0x04081122,
		0x00800000, 0x00800020, 0x00801000, 0x00801020,
		0x00880000, 0x00880020, 0x00881000, 0x00881020,
		0x04800000, 0x04800020, 0x04801000, 0x04801020,
		0x04880000, 0x04880020, 0x04881000, 0x04881020,
		0x00800002, 0x00800022, 0x00801002, 0x00801022,
		0x00880002, 0x00880022, 0x00881002, 0x00881022,
		0x04800002, 0x04800022, 0x04801002, 0x04801022,
		0x04880002, 0x04880022, 0x04881002, 0x04881022,
		0x00800100, 0x00800120, 0x00801100, 0x00801120,
		0x00880100, 0x00880120, 0x00881100, 0x00881120,
		0x04800100, 0x04800120, 0x04801100, 0x04801120,
		0x04880100, 0x04880120, 0x04881100, 0x04881120,
		0x00800102, 0x00800122, 0x00801102, 0x00801122,
		0x00880102, 0x00880122, 0x00881102, 0x00881122,
		0x04800102, 0x04800122, 0x04801102, 0x04801122,
		0x04880102, 0x04880122, 0x04881102, 0x04881122,
		0x40000000, 0x40000020, 0x40001000, 0x40001020,
		0x40080000, 0x40080020, 0x40081000, 0x40081020,
		0x44000000, 0x44000020, 0x44001000, 0x44001020,
		0x44080000, 0x44080020, 0x44081000, 0x44081020,
		0x40000002, 0x40000022, 0x40001002, 0x40001022,
		0x40080002, 0x40080022, 0x40081002, 0x40081022,
		0x44000002, 0x44000022, 0x44001002, 0x44001022,
		0x44080002, 0x44080022, 0x44081002, 0x44081022,
		0x40000100, 0x40000120, 0x40001100, 0x40001120,
		0x40080100, 0x40080120, 0x40081100, 0x40081120,
		0x44000100, 0x44000120, 0x44001100, 0x44001120,
		0x44080100, 0x44080120, 0x44081100, 0x44081120,
		0x40000102, 0x40000122, 0x40001102, 0x40001122,
		0x40080102, 0x40080122, 0x40081102, 0x40081122,
		0x44000102, 0x44000122, 0x44001102, 0x44001122,
		0x44080102, 0x44080122, 0x44081102, 0x44081122,
		0x40800000, 0x40800020, 0x40801000, 0x40801020,
		0x40880000, 0x40880020, 0x40881000, 0x40881020,
		0x44800000, 0x44800020, 0x44801000, 0x44801020,
		0x44880000, 0x44880020, 0x44881000, 0x44881020,
		0x40800002, 0x40800022, 0x40801002, 0x40801022,
		0x40880002, 0x40880022, 0x40881002, 0x40881022,
		0x44800002, 0x44800022, 0x44801002, 0x44801022,
		0x44880002, 0x44880022, 0x44881002, 0x44881022,
		0x40800100, 0x40800120, 0x40801100, 0x40801120,
		0x40880100, 0x40880120, 0x40881100, 0x40881120,
		0x44800100, 0x44800120, 0x44801100, 0x44801120,
		0x44880100, 0x44880120, 0x44881100, 0x44881120,
		0x40800102, 0x40800122, 0x40801102, 0x40801122,
		0x40880102, 0x40880122, 0x40881102, 0x40881122,
		0x44800102, 0x44800122, 0x44801102, 0x44801122,
		0x44880102, 0x44880122, 0x44881102, 0x44881122
		},
		{
		0x00000000, 0x00000040, 0x00002000, 0x00002040,
		0x00100000, 0x00100040, 0x00102000, 0x00102040,
		0x04000000, 0x04000040, 0x04002000, 0x04002040,
		0x04100000, 0x04100040, 0x04102000, 0x04102040,
		0x00000004, 0x00000044, 0x00002004, 0x00002044,
		0x00100004, 0x00100044, 0x00102004, 0x00102044,
		0x04000004, 0x04000044, 0x04002004, 0x04002044,
		0x04100004, 0x04100044, 0x04102004, 0x04102044,
		0x00000200, 0x00000240, 0x00002200, 0x00002240,
		0x00100200, 0x00100240, 0x00102200, 0x00102240,
		0x04000200, 0x04000240, 0x04002200, 0x04002240,
		0x04100200, 0x04100240, 0x04102200, 0x04102240,
		0x00000204, 0x00000244, 0x00002204, 0x00002244,
		0x00100204, 0x00100244, 0x00102204, 0x00102244,
		0x04000204, 0x04000244, 0x04002204, 0x04002244,
		0x04100204, 0x04100244, 0x04102204, 0x04102244,
		0x00010000, 0x00010040, 0x00012000, 0x00012040,
		0x00110000, 0x00110040, 0x00112000, 0x00112040,
		0x04010000, 0x04010040, 0x04012000, 0x04012040,
		0x04110000, 0x04110040, 0x04112000, 0x04112040,
		0x00010004, 0x00010044, 0x00012004, 0x00012044,
		0x00110004, 0x00110044, 0x00112004, 0x00112044,
		0x04010004, 0x04010044, 0x04012004, 0x04012044,
		0x04110004, 0x04110044, 0x04112004, 0x04112044,
		0x00010200, 0x00010240, 0x00012200, 0x00012240,
		0x00110200, 0x00110240, 0x00112200, 0x00112240,
		0x04010200, 0x04010240, 0x04012200, 0x04012240,
		0x04110200, 0x04110240, 0x04112200, 0x04112240,
		0x00010204, 0x00010244, 0x00012204, 0x00012244,
		0x00110204, 0x00110244, 0x00112204, 0x00112244,
		0x04010204, 0x04010244, 0x04012204, 0x04012244,
		0x04110204, 0x04110244, 0x04112204, 0x04112244,
		0x80000000, 0x80000040, 0x80002000, 0x80002040,
		0x80100000, 0x80100040, 0x80102000, 0x80102040,
		0x84000000, 0x84000040, 0x84002000, 0x84002040,
		0x84100000, 0x84100040, 0x84102000, 0x84102040,
		0x80000004, 0x80000044, 0x80002004, 0x80002044,
		0x80100004, 0x80100044, 0x80102004, 0x80102044,
		0x84000004, 0x84000044, 0x84002004, 0x84002044,
		0x84100004, 0x84100044, 0x84102004, 0x84102044,
		0x80000200, 0x80000240, 0x80002200, 0x80002240,
		0x80100200, 0x80100240, 0x80102200, 0x80102240,
		0x84000200, 0x84000240, 0x84002200, 0x84002240,
		0x84100200, 0x84100240, 0x84102200, 0x84102240,
		0x80000204, 0x80000244, 0x80002204, 0x80002244,
		0x80100204, 0x80100244, 0x80102204, 0x80102244,
		0x84000204, 0x84000244, 0x84002204, 0x84002244,
		0x84100204, 0x84100244, 0x84102204, 0x84102244,
		0x80010000, 0x80010040, 0x80012000, 0x80012040,
		0x80110000, 0x80110040, 0x80112000, 0x80112040,
		0x84010000, 0x84010040, 0x84012000, 0x84012040,
		0x84110000, 0x84110040, 0x84112000, 0x84112040,
		0x80010004, 0x80010044, 0x80012004, 0x80012044,
		0x80110004, 0x80110044, 0x80112004, 0x80112044,
		0x84010004, 0x84010044, 0x84012004, 0x84012044,
		0x84110004, 0x84110044, 0x84112004, 0x84112044,
		0x80010200, 0x80010240, 0x80012200, 0x80012240,
		0x80110200, 0x80110240, 0x80112200, 0x80112240,
		0x84010200, 0x84010240, 0x84012200, 0x84012240,
		0x84110200, 0x84110240, 0x84112200, 0x84112240,
		0x80010204, 0x80010244, 0x80012204, 0x80012244,
		0x80110204, 0x80110244, 0x80112204, 0x80112244,
		0x84010204, 0x84010244, 0x84012204, 0x84012244,
		0x84110204, 0x84110244, 0x84112204, 0x84112244
		}
	};

const	Cryptography::SBoxFunction	Cryptography::SubsFunctionTable
						[BYTE_FEISTEL_STEPS]
						[sizeof(std_uint)] =
	{
	{ SBox_0, SBox_1, SBox_2, SBox_3 },
	{ SBox_5, SBox_3, SBox_1, SBox_0 },
	{ SBox_4, SBox_5, SBox_6, SBox_7 },
	{ SBox_1, SBox_7, SBox_6, SBox_2 },
	{ SBox_2, SBox_3, SBox_4, SBox_5 },
	{ SBox_7, SBox_5, SBox_3, SBox_1 },
	{ SBox_1, SBox_2, SBox_6, SBox_7 },
	{ SBox_6, SBox_4, SBox_2, SBox_0 }
	};

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_0(byte Value) noexcept
	{
	return (Value * 31 + 11) % 251;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_1(byte Value) noexcept
	{
	return SubsTable [Value];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_2(byte Value) noexcept
	{
	return (Value * 41 + 19) % (BYTE_MAX + 1);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_3(byte Value) noexcept
	{
	return SubsTable [BYTE_MAX - Value];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_4(byte Value) noexcept
	{
	return (Value * 23 + 7) % 241;
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_5(byte Value) noexcept
	{
	return SubsTable [(Value * 19) % (BYTE_MAX + 1)];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_6(byte Value) noexcept
	{
	return (Value * 113 + 41) % (BYTE_MAX + 1);
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Implement a S-box, that is, substitute a byte with another.
//!
//! \param	Value	Source data.
//!
//! \throw	None.
//!
//! \returns	byte	Substituted value.
//!
//! \note
//!	In a good S-box the substitution must be as "random" as possible, but
//!	not necessarily one to one.
//!
////////////////////////////////////////////////////////////////////////////////

byte	Cryptography::SBox_7(byte Value) noexcept
	{
	return SubsTable [(Value * 87) % (BYTE_MAX + 1)];
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Crypt a block of data. \n
//!	The block is crypted executing 8 steps of Feistel functions, each
//!	operating on half of the data block, exchanging the role of the two
//!	halves at each steps. \n
//!	A different combination of S-box functions is used during each step. \n
//!	The encrypted block replaces the source data.
//!
//! \param	Plain		The array of data to be crypted.
//! \param	Encrypted	The array of encrypted data.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	Plain and Encrypted buffers can overlap.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	Cryptography::Crypt(const byte Plain [ENCRYPTION_BLOCK_LENGTH],
		byte Encrypted [ENCRYPTION_BLOCK_LENGTH]) const noexcept
	{
	std_uint	DataHigh;
	std_uint	DataLow;

memcpy(Encrypted, Plain, ENCRYPTION_KEY_LENGTH);
return;
	DataHigh = Pack(Plain);
	DataLow = Pack(Plain + sizeof(std_uint));
	FeistelStep(DataLow, DataHigh, RotatedKey [0], SubsFunctionTable [0]);
	FeistelStep(DataHigh, DataLow, RotatedKey [1], SubsFunctionTable [1]);
	FeistelStep(DataHigh, DataLow, RotatedKey [2], SubsFunctionTable [2]);
	FeistelStep(DataHigh, DataLow, RotatedKey [3], SubsFunctionTable [3]);
	FeistelStep(DataLow, DataHigh, RotatedKey [4], SubsFunctionTable [4]);
	FeistelStep(DataHigh, DataLow, RotatedKey [5], SubsFunctionTable [5]);
	FeistelStep(DataLow, DataHigh, RotatedKey [6], SubsFunctionTable [6]);
	FeistelStep(DataHigh, DataLow, RotatedKey [7], SubsFunctionTable [7]);
	Unpack(DataHigh, Encrypted);
	Unpack(DataLow, Encrypted + sizeof(std_uint));
	}

////////////////////////////////////////////////////////////////////////////////
//! \par	Description:
//!	Decrypt a block of data. \n
//!	The block is decrypted executing 8 steps of Feistel functions, each
//!	operating on half of the data block, exchanging the role of the two
//!	halves at each steps. \n
//!	A different combination of S-box functions is used during each step. \n
//!	The decrypted block replaces the source data.
//!
//! \param	Encrypted	The array of encrypted data.
//! \param	Plain		The array of decrypted data.
//!
//! \throw	None.
//!
//! \returns	None.
//!
//! \note
//!	Plain and Encrypted buffers can overlap.
//!
//! \see	ENCRYPTION_KEY_LENGTH
//!
////////////////////////////////////////////////////////////////////////////////

void	Cryptography::Decrypt(const byte Encrypted [ENCRYPTION_BLOCK_LENGTH],
		byte Plain [ENCRYPTION_BLOCK_LENGTH]) const noexcept
	{
	std_uint	DataHigh;
	std_uint	DataLow;

memcpy(Plain, Encrypted, ENCRYPTION_KEY_LENGTH);
return;
	DataHigh = Pack(Encrypted);
	DataLow = Pack(Encrypted + sizeof(std_uint));
	FeistelStep(DataHigh, DataLow, RotatedKey [7], SubsFunctionTable [7]);
	FeistelStep(DataLow, DataHigh, RotatedKey [6], SubsFunctionTable [6]);
	FeistelStep(DataHigh, DataLow, RotatedKey [5], SubsFunctionTable [5]);
	FeistelStep(DataLow, DataHigh, RotatedKey [4], SubsFunctionTable [4]);
	FeistelStep(DataHigh, DataLow, RotatedKey [3], SubsFunctionTable [3]);
	FeistelStep(DataLow, DataHigh, RotatedKey [2], SubsFunctionTable [2]);
	FeistelStep(DataHigh, DataLow, RotatedKey [1], SubsFunctionTable [1]);
	FeistelStep(DataLow, DataHigh, RotatedKey [0], SubsFunctionTable [0]);
	Unpack(DataHigh, Plain);
	Unpack(DataLow, Plain + sizeof(std_uint));
	}

}
