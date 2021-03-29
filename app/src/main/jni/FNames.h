#ifndef FNAMES_H
#define FNAMES_H

#include "kmods.h"

using namespace std;

string getUEString(kaddr address) {
	unsigned int MAX_SIZE = 100;

	string uestring(ReadStr(address, MAX_SIZE));
	//uestring.shrink_to_fit();

	return uestring;
}

/*char *getname(int id,kaddr Gnam)
{

if ( id > 0 && id < 2000000)
	{
		int ye=id/16384;
		int xu=id%16384;
		
		kaddr ddz = getPtr(Gnam+ye*4); 
		
		kaddr namedz = getPtr(ddz+xu*4);
		
	    char *classname = ReadStr(namedz+8,32);
	
		return classname; 				
	}
			
}*/


char *GetFNameFromID(uint32_t index) {
	kaddr TNameEntryArray = getPtr(getRealOffset(Offsets::GNames));

	kaddr FNameEntryArr = getPtr(TNameEntryArray + ((index / 0x4000) * Offsets::PointerSize));
	kaddr FNameEntry = getPtr(FNameEntryArr + ((index % 0x4000) * Offsets::PointerSize));

	return ReadStr(FNameEntry + Offsets::FNameEntryToNameString,32);
}

#endif
