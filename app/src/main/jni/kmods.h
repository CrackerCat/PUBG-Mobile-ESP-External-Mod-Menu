#ifndef KMODS_H
#define KMODS_H

#include <jni.h>
#include <string>
#include <cstdlib>
#include <sys/mman.h>
#include <android/log.h>
#include <StructsCommon.h>

#include <iostream>
#include <fstream>
#include <fcntl.h>
#include <math.h>
#include <cstdio>
#include <cstddef>
//#include <cmath>
#include <ctime>
#include <vector>
#include <list>
#include <stack>

#include <dirent.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>

//#include <malloc.h>
//#include <assert.h>
#include "Memory.h"
#include "Process.h"
#include "Offsets.h"


static const char* game_version = "0.18.0";
static const char* process_name = "com.tencent.ig";
static const char* lib_name = "libUE4.so";

Response response;

//float matrix[50];


kaddr vworld; 
kaddr CM; 
kaddr JZDZ;
float pmx;
float pmy;



bool isESP = false;
//Player
bool isPlayerName = false;
bool isPlayerDist = false;
bool isPlayerHealth = false;
bool isTeamMateShow = false;
bool isPlayerBox = false;
bool isPlayerLine = false;
bool isPlayer360 = false;
bool isPlayerCount = false;
float playerTextSize = 15;
//Vehicle
bool isVehicleName = false;
bool isVehicleDist = false;
float vehicleTextSize = 15;
//LootBox
bool isLootBoxName = false;
bool isLootBoxDist = false;
float lootTextSize = 15;


bool isDasia = false; 
bool isBike =false; 
bool isTbike = false; 
bool isBrdm = false; 
bool isUaz = false; 
bool isBuggy = false; 
bool isMirado = false; 
bool isPlane = false; 

bool isM416 = false;
bool isAkm = false;
bool isScarl = false;
bool isFlare = false; 
bool isRip = false; 
bool isScopes = false; 
bool isAwm = false; 
bool isM24 = false; 
bool isKar = false;
bool isDrop = false; 
bool isAmmo = false; 
bool isPan = false;

void startDaemon();
int startClient();
bool isConnected();
void stopClient();
bool initServer();
bool stopServer();
Response getData(int screenWidth, int screenHeight);


char *getname(int id,kaddr Gnam)
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
			
}

bool isplayer(char *namee)
{
	if (strstr(namee,"BP_PlayerPawn") != NULL)
	{
	return true;	
	}
	return false;
}

bool isStartWith(string str, const char* check) {
	return (str.rfind(check, 0) == 0);
}

bool isEqual(char* s1, const char* s2) {
	return (strcmp(s1, s2) == 0);
}

bool isEqual(string s1, const char* check) {
	string s2(check);
	return (s1 == s2);
}

bool isEqual(string s1, string s2) {
	return (s1 == s2);
}

bool isContain(string str, const char* check) {
	size_t found = str.find(check);
	return (found != string::npos);
}





const char *isvh(char *name)
{
	
	if(isBike)
	{
	if (strstr(name,"VH_Motorcycle") != 0)
	{
		return "Bike";
	}
	}
	
	if(isTbike)
	{
	if (strstr(name,"VH_MotorcycleCart") != 0)
	{
		return "TBike";
	}
	}

	if(isBuggy)
	{
	if (strstr(name,"Buggy") != 0)
	{
		return "Buggy";
	}
	}
	

	if(isDasia)
	{
	if (strstr(name,"Dacia") != 0)
	{
		return "Dacia";
	}
	}

	if(isUaz)
	{
	if (strstr(name,"UAZ") != 0)
	{
		return "UAZ";
	}
	}
	
	if (strstr(name,"PG117") != 0)
	{
		return "PG117";
	}
	
	if (strstr(name,"AirDropPlane") != 0)
	{
		return "AirPlane";
	}
	
	
	if(isDrop)
{
	if (strstr(name,"BP_AirDropBox_C") != 0)
	{
		return "AirDrop";
	}
}

	if(isRip)
	{
	if (strstr(name,"PlayerDeadInventoryBox_C") != 0)
	{
		return "Loot";
	}
	}
	
	
	return "NO_Item";
}


const char *isq(char *name)
{
	
	if(isM416)
	{
	if (strstr(name,"Rifle_M416") != 0 && strstr(name,"Wrapper") != 0)
	{
		return "M416";
	}
	}

	if(isScarl)
	{
	if (strstr(name,"DP28") != 0 && strstr(name,"Wrapper") != 0)
	{
		return "DP28";
	}
	}

	if(isAwm)
	{
	if (strstr(name,"Sniper_AWM") != 0)
	{
		return "AWM";
	}
	}
	if(isKar)
	{
	if (strstr(name,"Sniper_Kar98k") != 0 && strstr(name,"Wrapper") != 0)
	{
		return "Kar98";
	}
	}
	if(isM24)
	{
	if (strstr(name,"Sniper_M24") != 0 && strstr(name,"Wrapper") != 0)
	{
		return "M24";
	}
	}

if(isFlare)
{
	if (strstr(name,"Pistol_Flaregun") != 0)
	{
		return "Flare";
	}
}



	return "NO_Item";
          
}

#endif
