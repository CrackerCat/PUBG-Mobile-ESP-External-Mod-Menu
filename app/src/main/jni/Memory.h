#ifndef MEMORY_H
#define MEMORY_H

#include <dirent.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Process.h"

using namespace std;

typedef unsigned int kaddr;

// Unsigned base types.
typedef unsigned char 		uint8;
typedef unsigned short int	uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;

// Signed base types.
typedef	signed char			int8;
typedef signed short int	int16;
typedef signed int	 		int32;
typedef signed long long	int64;

// Character types.
typedef char				ANSICHAR;
typedef wchar_t				WIDECHAR;
typedef uint8				CHAR8;
typedef uint16				CHAR16;
typedef uint32				CHAR32;
typedef WIDECHAR			TCHAR;

static kaddr libbase = 0;

pid_t find_pid(const char* process_name) {
	int id;
	pid_t pid = -1;
	DIR* dir;
	FILE* fp;
	char filename[32];
	char cmdline[256];

	struct dirent* entry;
	if (process_name == NULL) {
		return -1;
	}
	dir = opendir("/proc");
	if (dir == NULL) {
		return -1;
	}
	while ((entry = readdir(dir)) != NULL) {
		
		sscanf(entry->d_name,"%d",&id);
		
		//id = atoi(entry->d_name);
		
		if (id != 0) {
			sprintf(filename, "/proc/%d/cmdline", id);
			fp = fopen(filename, "r");
			if (fp) {
				fgets(cmdline, sizeof(cmdline), fp);
				fclose(fp);

				if (strcmp(process_name, cmdline) == 0) {
					/* process found */
					pid = id;
					break;
				}
			}
		}
	}

	closedir(dir);
	return pid;
}

struct MAPS

{
	
long int addr;
	
long int taddr;
	
char* value;
	
struct MAPS *next;

};

#define LEN sizeof(struct MAPS)

#define FRE sizeof(struct FREEZE)
typedef struct MAPS *PMAPS;


int getbsaddr(int iPID)
{

PMAPS pHead=NULL;
PMAPS pNew=NULL;
PMAPS pEnd=NULL;
pEnd=pNew=(PMAPS)malloc(LEN);
	


	FILE *fp;
	int i = 0, flag = 1;
	char lj[64], buff[256];
	sprintf(lj, "/proc/%d/maps", iPID);
	fp = fopen(lj, "r");
	if (fp == NULL)
	{
		puts("No Process started");
		
	}
	while (!feof(fp))
	{
		fgets(buff, sizeof(buff), fp);
		if (strstr(buff, "r-xp") != NULL && !feof(fp) && strstr(buff, "libUE4.so"))
		{
			sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr);
			
			flag = 1;
		}
		else
		{
			flag = 0;
		}
		
		if (flag==1)
{
i++;
if (i==1)
{
pNew->next=NULL;
pEnd=pNew;
pHead=pNew;
}
else
{
pNew->next=NULL;
pEnd->next=pNew;
pEnd=pNew;
}
pNew=(PMAPS)malloc(LEN);
}
}
free(pNew);
fclose(fp);



		
		
		return pHead->addr;
	}	
	
	
	
int ReadTM(kaddr addr)
{
int *data = (int*)malloc(4);
vm_readv(reinterpret_cast<void*>(addr), data, 4);

int paddr = *(int*)data;
return paddr;
free(data); 
}	
	

kaddr getRealOffset(kaddr offset) {
    if (libbase == 0) {
        //LOGW("Error: Can't Find Base Addr for Real Offset");
        return 0;
    }
    return (libbase + offset);
}

template <typename T>
T Read(kaddr address) {
    T data;
    vm_readv(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&data), sizeof(T));
    return data;
}

template <typename T>
void Write(kaddr address, T data) {
    vm_writev(reinterpret_cast<void*>(address), reinterpret_cast<void*>(&data), sizeof(T));
}

template <typename T>
T* ReadArr(kaddr address, unsigned int size) {
    T data[size];
    T* ptr = data;
    vm_readv(reinterpret_cast<void*>(address), reinterpret_cast<void*>(ptr), (sizeof(T) * size));
    return ptr;
}

char* ReadStr(kaddr address, unsigned int size) {
	char* data = new char[size];
	for(int i=0; i < size; i++){
		vm_readv(reinterpret_cast<void*>(address + (sizeof(char)*i)), reinterpret_cast<void*>(data + i), sizeof(char));
		if(data[i] == '\0'){
			break;
		}
	}
	return data;
	delete data; 
}

kaddr getPtr(kaddr address) {
    return Read<kaddr>(address);
}

#endif //MEMORY_H
