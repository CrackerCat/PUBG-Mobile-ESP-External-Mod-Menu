#ifndef HACKS_H
#define HACKS_H

#include "kmods.h"
#include "StructsPUBG.h"
#include "FNames.h"


int limit;
int count;


bool isValidPlayer(PlayerData data){
    return (data.Location != Vector2::Zero() && data.HeadLocation != Vector2::Zero() && data.PlayerName.size() > 0);
}

bool isValidItem(VehicleData data){
    return (data.Location != Vector2::Zero() && data.Name.size() > 0);
}

bool isValidItem(ItemData data){
    return (data.Location != Vector2::Zero() && data.Name.size() > 0);
}

int isOutsideSafezone(Vector2 pos, Vector2 screen) {
    Vector2 mSafezoneTopLeft(screen.x * 0.04f, screen.y * 0.04f);
    Vector2 mSafezoneBottomRight(screen.x * 0.96f, screen.y * 0.96f);

    int result = 0;
    if (pos.y < mSafezoneTopLeft.y) {
        result |= 1;
    }
    if (pos.x > mSafezoneBottomRight.x) {
        result |= 2;
    }
    if (pos.y > mSafezoneBottomRight.y) {
        result |= 4;
    }
    if (pos.x < mSafezoneTopLeft.x) {
        result |= 8;
    }
    return result;
}

Vector2 pushToScreenBorder(Vector2 Pos, Vector2 screen, int borders, int offset) {
    int x = (int)Pos.x;
    int y = (int)Pos.y;
    if ((borders & 1) == 1) {
        y = 0 - offset;
    }
    if ((borders & 2) == 2) {
        x = (int)screen.x + offset;
    }
    if ((borders & 4) == 4) {
        y = (int)screen.y + offset;
    }
    if ((borders & 8) == 8) {
        x = 0 - offset;
    }
    return Vector2(x, y);
}

#define VehicleNames 15
static const char* vehicles[] = {
		"Buggy",
		"Dacia",
		"Tuk",
		"Rony",
		"Mirado",
		"UAZ",
		"MiniBus",
		"BRDM",
		"Scooter",
		"Motorcycle",
		"Snowmobile",
		"MotorcycleCart",
		"PG117",
		"AquaRail",
		"AirDropPlane"
};

const char *FindVehicleName(char *str) {
	for (int i = 0; i < VehicleNames; i++) {
		if (isContain(str, vehicles[i])) {
			return vehicles[i];
		}
	}
	return "Vehicle";
}

void DrawESP(ESP esp, int screenWidth, int screenHeight) {
   if(isESP){ 
   
 // char aa[32];
 // sprintf(aa,"%d",count);
esp.DrawCrosshair(Color(0, 0, 0, 255), Vector2(screenWidth / 2, screenHeight / 2), 42);
//esp.DrawText(Color::White(), acname.c_str(),Vector2(screenWidth / 2, screenHeight /2 ), lootTextSize);



/*for(int i=1 ; i<limit ; i++)
{

           float boxHeight = (screenWidth / boxdata[i].dis);
           float boxWidth = (screenHeight / boxdata[i].dis);
           Rect PlayerRect(boxdata[i].x-(boxWidth/2),boxdata[i].y,boxWidth,boxHeight);
esp.DrawBox(Color::Red(), 2, PlayerRect);

}*/
}
}

void looper(ESP esp1 , float pmx, float pmy)
{
if(isPlayerBox)
{
//espOverlay.DrawCrosshair(Color(255, 255, 0, 255), Vector2(espOverlay.getWidth() / 3, espOverlay.getHeight() / 2), 42);


float matrix[20] = { };
int tenemy=0;
int aa=0;
int localid=0;

	UWorld uworld(getPtr(getRealOffset(Offsets::GWorld)));
	if (uworld.ptr == 0) 
		{ 
		return; 
		}

	ULevel level = uworld.PersistentLevel;
	if (level.ptr == 0) 
		{ 
		return; 
		}

	for (int i = 0; i < level.getActorsCount(); i++) {
		AActor actor = level.getActor(i);
		if (actor.ptr == 0) 
			{ 
			continue; 
			}

		char *acname = actor.getName();
	    char Playername[32]={};

	
if (isContain(acname, "PlayerCameraManager")) {
	int g; 

    for (g = 0; g < 16; g++)
	{
		matrix[g] = Read<float>(JZDZ+g*4);
	}
	
}

		Vector3A location = actor.RootComponent.ComponentToWorld.Translation;
		Vector3A wlocation = WorldToScreen1(location, matrix, pmx/2, pmy/2,true);
	    
		float ViewW = (matrix[3] * location.X) + (matrix[7] * location.Y) + (matrix[11] * location.Z) + matrix[15];
		
		int distance = ViewW / 100;
		char dis[10]={};
		sprintf(dis,"%dm",distance);
		
   /* std::stringstream ss;
    ss << distance << "m";
    std::string s = ss.str();*/
 
if (isplayer(acname)) {
			STExtraCharacter player(actor.ptr);

aa++;
bool isAI = false;

if(aa == 1)
{
	localid=player.TeamID ;
}
if(player.isTeam != 0)
{
	continue;
}
if(player.TeamID==localid)
{
	continue;
}
if(player.isBot==0)
{
	isAI = true;
}

tenemy++;			
float hp = player.Health;


			
			Vector2 End(wlocation.X,wlocation.Y);
            float boxHeight = -wlocation.Z;
            float boxWidth = -wlocation.Z/2;
            Rect PlayerRect(End.x - (boxWidth / 2), End.y, boxWidth, boxHeight);

            
Vector2 screen(pmx, pmy);
Vector2 location(End.x,End.y);
float mScale = (pmy) / (float) 1080;	
			
			
			if(hp > 0)
			{
			esp1.DrawBox(Color::Red(), 2, PlayerRect);
					 
            if(isPlayerLine && End.y<pmy)
			{
			esp1.DrawLine(isAI ? Color::White() : Color::Ant(), 1, Vector2((pmx / 2), 90),End);           
		    }
	
			

			
			

		int borders = isOutsideSafezone(location, screen);
        if(isPlayer360 && borders != 0){
             Vector2 hintDotRenderPos = pushToScreenBorder(location, screen, borders, (int)((mScale * 100) / 3));
             Vector2 hintTextRenderPos = pushToScreenBorder(location, screen, borders, -(int)((mScale * 36)));
             esp1.DrawFilledCircle((Color(255,0,0,128)), hintDotRenderPos, (mScale * 100));
             esp1.DrawText(Color::White(),1.1f, dis, hintTextRenderPos, playerTextSize);
             }
             }
			

      if(isPlayerName)
	  {
	  
      getplayername(actor.ptr, Playername);
      esp1.DrawText((Color::White()), 1.1f, Playername, Vector2(PlayerRect.x + (PlayerRect.width / 2), PlayerRect.y - 12.0f), playerTextSize);
	  
	  }
					   
	  if(isPlayerHealth) {
                        esp1.DrawHorizontalHealthBar(
                                    Vector2(PlayerRect.x - (35 * mScale), PlayerRect.y - (isPlayerName ? 22.0f : 12.0f)),
                                    (80 * mScale),
                                    100, hp);
      }		   
					   
	  if(isPlayerDist) {
                      esp1.DrawText(Color::Yellow(),0.5f, dis,
                                         Vector2(PlayerRect.x + (PlayerRect.width / 2),
                                         PlayerRect.y + PlayerRect.height +
                                          12.5f), 12);
      }		   
					   
					   
		
	  
	  
//--------------------------------------------------//
    /*kaddr chest = 4;
	kaddr pelvis = 1;
	kaddr lsholder = 11;
	kaddr rsholder = 32;
	kaddr lElbow = 12;
	kaddr rElbow = 33;
	kaddr lWrist = 63;
	kaddr rWrist = 62;*/
	if(isTeamMateShow)
	{
			FTransform meshtrans = player.Mesh.ComponentToWorld;
			FMatrix c2wMatrix = TransformToMatrix(meshtrans);

			//Head
			FTransform headtrans = player.Mesh.getBone(6);
			FMatrix boneMatrix = TransformToMatrix(headtrans);

			Vector3A relLocation = MarixToVector(MatrixMulti(boneMatrix, c2wMatrix));
			relLocation.Z += 7;
			Vector3A wrelLocation = WorldToScreen1(relLocation, matrix, pmx/2, pmy/2,false);

            //Chest
            FTransform chesttrans = player.Mesh.getBone(5);
			FMatrix boneMatrix1 = TransformToMatrix(chesttrans);

			Vector3A relLocation1 = MarixToVector(MatrixMulti(boneMatrix1 , c2wMatrix));
			Vector3A wrelLocation1 = WorldToScreen1(relLocation1 , matrix, pmx/2, pmy/2,false);

            //Left Sholder
            FTransform lshtrans = player.Mesh.getBone(12);
			FMatrix boneMatrix2 = TransformToMatrix(lshtrans);

			Vector3A relLocation2 = MarixToVector(MatrixMulti(boneMatrix2 , c2wMatrix));
			Vector3A wrelLocation2 = WorldToScreen1(relLocation2 , matrix, pmx/2, pmy/2,false);

            //Right Shoulder
            FTransform rshtrans = player.Mesh.getBone(33);
			FMatrix boneMatrix3 = TransformToMatrix(rshtrans);

			Vector3A relLocation3 = MarixToVector(MatrixMulti(boneMatrix3 , c2wMatrix));
			Vector3A wrelLocation3 = WorldToScreen1(relLocation3 , matrix, pmx/2, pmy/2,false);

            //Left Elbow
            FTransform lelbtrans = player.Mesh.getBone(13);
			FMatrix boneMatrix4 = TransformToMatrix(lelbtrans);

			Vector3A relLocation4 = MarixToVector(MatrixMulti(boneMatrix4 , c2wMatrix));
			Vector3A wrelLocation4 = WorldToScreen1(relLocation4 , matrix, pmx/2, pmy/2,false);

            //Right Elbow
            FTransform relbtrans = player.Mesh.getBone(34);
			FMatrix boneMatrix5 = TransformToMatrix(relbtrans);

			Vector3A relLocation5 = MarixToVector(MatrixMulti(boneMatrix5 , c2wMatrix));
			Vector3A wrelLocation5 = WorldToScreen1(relLocation5 , matrix, pmx/2, pmy/2,false);

            //Left Wrist
            FTransform lwtrans = player.Mesh.getBone(64);
			FMatrix boneMatrix6 = TransformToMatrix(lwtrans);

			Vector3A relLocation6 = MarixToVector(MatrixMulti(boneMatrix6 , c2wMatrix));
			Vector3A wrelLocation6 = WorldToScreen1(relLocation6 , matrix, pmx/2, pmy/2,false);

            //Right Wrist
            FTransform rwtrans = player.Mesh.getBone(63);
			FMatrix boneMatrix7 = TransformToMatrix(rwtrans);

			Vector3A relLocation7 = MarixToVector(MatrixMulti(boneMatrix7 , c2wMatrix));
			Vector3A wrelLocation7 = WorldToScreen1(relLocation7 , matrix, pmx/2, pmy/2,false);

	/*kaddr chest = 1;
	//kaddr pelvis = 1;
	kaddr lsholder = 52;
	kaddr rsholder = 56;
	kaddr lElbow = 53;
	kaddr rElbow = 57;
	kaddr lWrist = 54;
	kaddr rWrist = 58;*/

            //Pelvis
            FTransform Lchesttrans = player.Mesh.getBone(2);
			FMatrix LboneMatrix1 = TransformToMatrix(Lchesttrans);

			Vector3A LrelLocation1 = MarixToVector(MatrixMulti(LboneMatrix1 , c2wMatrix));
			Vector3A LwrelLocation1 = WorldToScreen1(LrelLocation1 , matrix, pmx/2, pmy/2,false);

            //Left Sholder
            FTransform Llshtrans = player.Mesh.getBone(53);
			FMatrix LboneMatrix2 = TransformToMatrix(Llshtrans);

			Vector3A LrelLocation2 = MarixToVector(MatrixMulti(LboneMatrix2 , c2wMatrix));
			Vector3A LwrelLocation2 = WorldToScreen1(LrelLocation2 , matrix, pmx/2, pmy/2,false);

            //Right Shoulder
            FTransform Lrshtrans = player.Mesh.getBone(57);
			FMatrix LboneMatrix3 = TransformToMatrix(Lrshtrans);

			Vector3A LrelLocation3 = MarixToVector(MatrixMulti(LboneMatrix3 , c2wMatrix));
			Vector3A LwrelLocation3 = WorldToScreen1(LrelLocation3 , matrix, pmx/2, pmy/2,false);

            //Left Elbow
            FTransform Llelbtrans = player.Mesh.getBone(54);
			FMatrix LboneMatrix4 = TransformToMatrix(Llelbtrans);

			Vector3A LrelLocation4 = MarixToVector(MatrixMulti(LboneMatrix4 , c2wMatrix));
			Vector3A LwrelLocation4 = WorldToScreen1(LrelLocation4 , matrix, pmx/2, pmy/2,false);

            //Right Elbow
            FTransform Lrelbtrans = player.Mesh.getBone(58);
			FMatrix LboneMatrix5 = TransformToMatrix(Lrelbtrans);

			Vector3A LrelLocation5 = MarixToVector(MatrixMulti(LboneMatrix5 , c2wMatrix));
			Vector3A LwrelLocation5 = WorldToScreen1(LrelLocation5 , matrix, pmx/2, pmy/2,false);

            //Left Wrist
            FTransform Llwtrans = player.Mesh.getBone(55);
			FMatrix LboneMatrix6 = TransformToMatrix(Llwtrans);

			Vector3A LrelLocation6 = MarixToVector(MatrixMulti(LboneMatrix6 , c2wMatrix));
			Vector3A LwrelLocation6 = WorldToScreen1(LrelLocation6 , matrix, pmx/2, pmy/2,false);

            //Right Wrist
            FTransform Lrwtrans = player.Mesh.getBone(59);
			FMatrix LboneMatrix7 = TransformToMatrix(Lrwtrans);

			Vector3A LrelLocation7 = MarixToVector(MatrixMulti(LboneMatrix7 , c2wMatrix));
			Vector3A LwrelLocation7 = WorldToScreen1(LrelLocation7 , matrix, pmx/2, pmy/2,false);


Vector2 head(wrelLocation.X,wrelLocation.Y);

Vector2 chest(wrelLocation1.X,wrelLocation1.Y);
Vector2 lsh(wrelLocation2.X,wrelLocation2.Y);
Vector2 rsh(wrelLocation3.X,wrelLocation3.Y);
Vector2 lelb(wrelLocation4.X,wrelLocation4.Y);
Vector2 relb(wrelLocation5.X,wrelLocation5.Y);
Vector2 lwr(wrelLocation6.X,wrelLocation6.Y);
Vector2 rwr(wrelLocation7.X,wrelLocation7.Y);

Vector2 pelvis(LwrelLocation1.X,LwrelLocation1.Y);
Vector2 lth(LwrelLocation2.X,LwrelLocation2.Y);
Vector2 rth(LwrelLocation3.X,LwrelLocation3.Y);
Vector2 lkn(LwrelLocation4.X,LwrelLocation4.Y);
Vector2 rkn(LwrelLocation5.X,LwrelLocation5.Y);
Vector2 lank(LwrelLocation6.X,LwrelLocation6.Y);
Vector2 rank(LwrelLocation7.X,LwrelLocation7.Y);

esp1.DrawCircle(Color(255,255,255,255),1,head,-wrelLocation.Z/10);

esp1.DrawLine(Color::White(),1,chest,lsh);
esp1.DrawLine(Color::White(),1,chest,rsh);

esp1.DrawLine(Color::White(),1,lsh,lelb);
esp1.DrawLine(Color::White(),1,rsh,relb);

esp1.DrawLine(Color::White(),1,lelb,lwr);
esp1.DrawLine(Color::White(),1,relb,rwr);

esp1.DrawLine(Color::White(),1,chest,pelvis);

esp1.DrawLine(Color::White(),1,pelvis,lth);
esp1.DrawLine(Color::White(),1,pelvis,rth);

esp1.DrawLine(Color::White(),1,lth,lkn);
esp1.DrawLine(Color::White(),1,rth,rkn);

esp1.DrawLine(Color::White(),1,lkn,lank);
esp1.DrawLine(Color::White(),1,rkn,rank);




}
	  
}
if(isVehicleName)
{
//const char *Vehicle = isvh(acname);

if (isContain(acname, isvh(acname))) 
{
	float mScale = (pmy) / (float) 1080;	
	
	esp1.DrawText(Color::White(),0.8f, isvh(acname) , Vector2(
                                wlocation.X, wlocation.Y - (30 * mScale)), vehicleTextSize);
                    
                    
    esp1.DrawText(Color::Yellow(),0.8f, dis, Vector2(
                                wlocation.X, wlocation.Y - (10 * mScale)), 12);
                    

}
}    
//const char *Item = isq(acname);
if(isLootBoxName)
{
if(isContain(acname, isq(acname)))
{
	float mScale = (pmy) / (float) 1080;	
	
	esp1.DrawText(Color(0,255,0,255),0.8f, isq(acname) , Vector2(
                                wlocation.X, wlocation.Y - (30 * mScale)), lootTextSize);
                    
                    
    esp1.DrawText(Color::Yellow(),0.8f, dis, Vector2(
                                wlocation.X, wlocation.Y - (10 * mScale)), 12);
}
	
}   
	 
	   
	   
	 delete acname;
     //  delete Vehicle;

	   //s.clear();
	  // dis="\0";
	   
	  // delete[] Playername; 
      // delete dis;
}

char cn[10] = {};

	 sprintf(cn,"%d",tenemy);
	 if(isPlayerCount)
	 {
	 if(tenemy  == 0)
	 {
	 esp1.DrawText(Color(0,0,0,255),0.4f, "CLEAR", Vector2(
                                pmx/2, 80), 30);
     }
     else
     {
     esp1.DrawText(Color(0,0,0,255),0.4f, cn, Vector2(
                                pmx/2, 80) , 30);
	 }              
	 } 


}

}


#endif //HACKS_H
