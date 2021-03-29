#include "kmods.h"
#include <ESP.h>
#include "Hacks.h"
//#include "StructsPUBG.h"
//#include "FNames.h"

using namespace std;

ESP espOverlay;
 

extern "C"
JNIEXPORT void JNICALL
Java_com_Anonymous_Loader_DrawOn(JNIEnv *env, jclass type, jobject espView, jobject canvas) {
    espOverlay = ESP(env, espView, canvas);

//pmx = espOverlay.getWidth() / 2;
//pmy = espOverlay.getHeight() / 2;
    

if(isESP)
{
     looper(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
}  
    if (espOverlay.isValid()){
      DrawESP(espOverlay, espOverlay.getWidth(), espOverlay.getHeight());
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_Anonymous_Loader_Size(JNIEnv *env, jclass type, jint num, jfloat size) {
    switch (num){
        case 0:
            playerTextSize = size;
            break;
        case 1:
            vehicleTextSize = size;
            break;
        case 2:
            lootTextSize = size;
            break;
        default:
            break;
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_Anonymous_Loader_Switch(JNIEnv *env, jclass type, jint num, jboolean flag) {
    switch (num){
        case 0:
            isESP = flag;
            break;
        case 1:
            isPlayerName = flag;
            break;
        case 2:
            isPlayerHealth = flag;
            break;
        case 3:
            isPlayerDist = flag;
            break;
        case 4:
            isTeamMateShow = flag;
            break;
        case 5:
            isPlayerLine = flag;
            break;
        case 6:
            isPlayerBox = flag;
            break;
        case 7:
            isPlayer360 = flag;
            break;
        case 8:
            isVehicleName = flag;
            break;
        case 9:
            isVehicleDist = flag;
            break;
        case 10:
            isLootBoxName = flag;
            break;
        case 11:
            isLootBoxDist = flag;
            break;
		case 12:
			isPlayerCount = flag;
			break;
        default:
            break;
    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_Anonymous_Loader_Switch1(JNIEnv *env, jclass type, jint num, jboolean flag) {
    switch (num){
        case 0:
            isDasia = flag;
            break;
        case 1:
            isBike = flag;
            break;
        case 2:
            isTbike = flag;
            break;
        case 3:
            isBrdm = flag;
            break;
        case 4:
            isUaz = flag;
            break;
        case 5:
            isBuggy = flag;
            break;
        case 6:
            isMirado = flag;
            break;
        case 7:
            isPlane = flag;
            break;
            
            
        case 8:
            isM416 = flag;
            break;
        case 9:
            isAkm = flag;
            break;
        case 10:
            isScarl = flag;
            break;
        case 11:
            isFlare = flag;
            break;
        case 12:
            isRip = flag;
            break;
        case 13:
            isScopes = flag;
            break;
        case 14:
            isAwm = flag;
            break;
        case 15:
            isM24 = flag;
            break; 
        case 16:
            isKar = flag;
            break;
        case 17:
            isDrop = flag;
            break;
        case 18:
            isAmmo = flag;
            break;
        case 19:
            isPan = flag;
            break;
        default:
            break;
    }
}
	





extern "C"
JNIEXPORT void JNICALL Java_com_Anonymous_Loader_ExecJNI(JNIEnv* env, jclass type)

{
	//looper();
}









extern "C"
JNIEXPORT void JNICALL Java_com_Anonymous_Loader_Init(JNIEnv *env, jclass type)

{    


target_pid = find_pid(process_name);
		
		if (target_pid == -1) {
			
		}

int bsaddx;
bsaddx = getbsaddr(target_pid);
libbase = bsaddx + 4294967296;
     
vworld = getPtr(libbase + 0x6522900);

CM = getPtr(vworld + 32);

JZDZ = CM + 512;


}


extern "C"
JNIEXPORT void JNICALL
Java_com_Anonymous_Loader_stop(JNIEnv *env, jclass type) {
   // stopClient();
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    return JNI_VERSION_1_6;
}

JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {}



	


