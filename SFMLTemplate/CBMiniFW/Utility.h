/*
	CB Mini Utility
	By Dan Buckstein

	Functions that do helpful things.
*/

#ifndef __CBMINI_FW_UTILITY_H
#define __CBMINI_FW_UTILITY_H


namespace cbmini
{
namespace cbfw
{


class Utility
{
public: 

	// load a file and return the contents as a string
	// to delete the string just call 'free'
	// returns 0 if failure
	static char *LoadFile(const char *filePath);

	// allocate a string
	static char *AllocString(const unsigned int size);

	// free a string
	static void FreeString(char *str);

};


}
}


#endif	// __CBMINI_FW_UTILITY_H