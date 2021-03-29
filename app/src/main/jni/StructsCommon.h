#ifndef STRUCTSCOMM_H
#define STRUCTSCOMM_H

#include "kmods.h"
#include <cmath>

using namespace std;

#define maxplayerCount 30
#define maxvehicleCount 20
#define maxitemsCount 20

void GetUnicodeChar(uint16 code, char chars[5]) {
    if (code <= 0x7F) {
        chars[0] = (code & 0x7F); 
        chars[1] = '\0';
    } else if (code <= 0x7FF) {
        // one continuation byte
        chars[1] = 0x80 | (code & 0x3F); 
        code = (code >> 6);
        chars[0] = 0xC0 | (code & 0x1F); 
        chars[2] = '\0';
    } else if (code <= 0xFFFF) {
        // two continuation bytes
        //code = convert_endian(code);
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xE0 | (code & 0xF); chars[3] = '\0';
    } else if (code <= 0x10FFFF) {
        // three continuation bytes
        chars[3] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[2] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[1] = 0x80 | (code & 0x3F); code = (code >> 6);
        chars[0] = 0xF0 | (code & 0x7); chars[4] = '\0';
    } else {
        // unicode replacement character
        chars[2] = 0xEF; chars[1] = 0xBF; chars[0] = 0xBD;
        chars[3] = '\0';
    }
}

void GetAddressInfo_uni1(kaddr addr,char nmm[32])
{
int m; 
char bb[2] = "\0";
char nnn[32] = "";

for (m=0;m<14;m++)
{
uint16 code = Read<uint16>(addr+m*2);
if (code == 0) 
{
break;
}
char chars[5];

GetUnicodeChar(code, chars);
strcat(nnn,chars);
}
//strcat(nnn,bb);
sprintf(nmm,"%s",nnn);
strcpy(nnn,bb);
}

void getplayername(kaddr addr,char classname[32])
{
kaddr namepy = getPtr(addr+1512);
		if(namepy == 0)
		{
			classname = "AB";
		}
		else
		{
			GetAddressInfo_uni1(namepy,classname);
		}	
}

template<class T>
struct TArray {
	kaddr Data;
	int32 Count;

	inline kaddr operator[](int i)
	{
		return Data + (i * sizeof(T));
	};

	T get(int i, bool deref = false) {
		kaddr ptrData = Data + (i * sizeof(T));

		if (deref)
			ptrData = getPtr(ptrData);

		return Read<T>(ptrData);
	}

	void set(T value, int i, bool deref = false) {
		kaddr ptrData = Data + (i * sizeof(T));

		if (deref)
			ptrData = getPtr(ptrData);

		Write<T>(ptrData, value);
	}
};


struct FString {
	kaddr Data;
	int32 Count;

	const char* c_str() {
		char* str = new char[Count];
		for (int i = 0; i < Count; i++) {
			char data = Read<char>(Data + (2 * i));
			str[i] = isascii(data) ? data : '?';
		}
		return (const char*)str;
	}
};

struct Base {
	kaddr ptr;

	Base(kaddr address) {
		if (address) {
			ptr = address;
		}
	}
};

class Color {
public:
	float r;
	float g;
	float b;
	float a;

	Color() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
		this->a = 0;
	}

	Color(float r, float g, float b, float a) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	Color(float r, float g, float b) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}

	static Color White(){
		return Color(255,255,255);
	}

	static Color Green(){
		return Color(0,255,0);
	}
		
	static Color Red(){
		return Color(255,0,0);
	}
	
	static Color Ant(){
		return Color(255,128,0);
	}
		
	static Color Yellow(){
	    return Color(255,255,0);
	}
	
};


// Vector2 for client
class Vector2 {
public:
	float x;
	float y;

	Vector2() {
		this->x = 0;
		this->y = 0;
	}

	Vector2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	static Vector2 Zero() {
		return Vector2(0.0f, 0.0f);
	}

	bool operator!=(const Vector2 &src) const {
		return (src.x != x) || (src.y != y);
	}

	Vector2 &operator+=(const Vector2 &v) {
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2 &operator-=(const Vector2 &v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
};

//Vector2A for Sever
struct Vector2A {
	float X;
	float Y;

	Vector2A() {
		this->X = 0;
		this->Y = 0;
	}

	Vector2A(float x, float y) {
		this->X = x;
		this->Y = y;
	}
};


//Vector3 for Client
class Vector3 {
public:
	float x;
	float y;
	float z;

	Vector3() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}

	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	static Vector3 Zero() {
		return Vector3(0.0f, 0.0f, 0.0f);
	}
};


//Vector3A for Server
struct Vector3A {
	float X;
	float Y;
	float Z;

	Vector3A() {
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3A(float x, float y, float z) {
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

	Vector3A operator+(const Vector3A& v) const {
		return Vector3A(X + v.X, Y + v.Y, Z + v.Z);
	}

	Vector3A operator-(const Vector3A& v) const {
		return Vector3A(X - v.X, Y - v.Y, Z - v.Z);
	}

	static float Dot(Vector3A lhs, Vector3A rhs) {
		return (((lhs.X * rhs.X) + (lhs.Y * rhs.Y)) + (lhs.Z * rhs.Z));
	}

	static float Distance(Vector3A a, Vector3A b) {
		Vector3A vector = Vector3A(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
		return sqrt(((vector.X * vector.X) + (vector.Y * vector.Y)) + (vector.Z * vector.Z));
	}
};



class Rect {
public:
	float x;
	float y;
	float width;
	float height;

	Rect() {
		this->x = 0;
		this->y = 0;
		this->width = 0;
		this->height = 0;
	}

	Rect(float x, float y, float width, float height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
	}

	bool operator==(const Rect &src) const {
		return (src.x == this->x && src.y == this->y && src.height == this->height &&
				src.width == this->width);
	}

	bool operator!=(const Rect &src) const {
		return (src.x != this->x && src.y != this->y && src.height != this->height &&
				src.width != this->width);
	}
};


struct FMatrix {
	float M[4][4];
};

struct Quat {
	float X;
	float Y;
	float Z;
	float W;
};

struct FTransform {
	Quat Rotation;
	Vector3A Translation;
	float chunk;
	Vector3A Scale3D;
};

Vector3A MarixToVector(FMatrix matrix) {
	return Vector3A(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
}

FMatrix MatrixMulti(FMatrix m1, FMatrix m2) {
	FMatrix matrix = FMatrix();
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				matrix.M[i][j] += m1.M[i][k] * m2.M[k][j];
			}
		}
	}
	return matrix;
}

FMatrix TransformToMatrix(FTransform transform) {
	FMatrix matrix;

	matrix.M[3][0] = transform.Translation.X;
	matrix.M[3][1] = transform.Translation.Y;
	matrix.M[3][2] = transform.Translation.Z;

	float x2 = transform.Rotation.X + transform.Rotation.X;
	float y2 = transform.Rotation.Y + transform.Rotation.Y;
	float z2 = transform.Rotation.Z + transform.Rotation.Z;

	float xx2 = transform.Rotation.X * x2;
	float yy2 = transform.Rotation.Y * y2;
	float zz2 = transform.Rotation.Z * z2;

	matrix.M[0][0] = (1 - (yy2 + zz2)) * transform.Scale3D.X;
	matrix.M[1][1] = (1 - (xx2 + zz2)) * transform.Scale3D.Y;
	matrix.M[2][2] = (1 - (xx2 + yy2)) * transform.Scale3D.Z;

	float yz2 = transform.Rotation.Y * z2;
	float wx2 = transform.Rotation.W * x2;
	matrix.M[2][1] = (yz2 - wx2) * transform.Scale3D.Z;
	matrix.M[1][2] = (yz2 + wx2) * transform.Scale3D.Y;

	float xy2 = transform.Rotation.X * y2;
	float wz2 = transform.Rotation.W * z2;
	matrix.M[1][0] = (xy2 - wz2) * transform.Scale3D.Y;
	matrix.M[0][1] = (xy2 + wz2) * transform.Scale3D.X;

	float xz2 = transform.Rotation.X * z2;
	float wy2 = transform.Rotation.W * y2;
	matrix.M[2][0] = (xz2 + wy2) * transform.Scale3D.Z;
	matrix.M[0][2] = (xz2 - wy2) * transform.Scale3D.X;

	matrix.M[0][3] = 0;
	matrix.M[1][3] = 0;
	matrix.M[2][3] = 0;
	matrix.M[3][3] = 1;

	return matrix;
}

struct FRotator {
	float Pitch;
	float Yaw;
	float Roll;
};

FMatrix RotatorToMatrix(FRotator rotation) {
	float radPitch = rotation.Pitch * ((float)M_PI / 180.0f);
	float radYaw = rotation.Yaw * ((float)M_PI / 180.0f);
	float radRoll = rotation.Roll * ((float)M_PI / 180.0f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	FMatrix matrix;

	matrix.M[0][0] = (CP * CY);
	matrix.M[0][1] = (CP * SY);
	matrix.M[0][2] = (SP);
	matrix.M[0][3] = 0;

	matrix.M[1][0] = (SR * SP * CY - CR * SY);
	matrix.M[1][1] = (SR * SP * SY + CR * CY);
	matrix.M[1][2] = (-SR * CP);
	matrix.M[1][3] = 0;

	matrix.M[2][0] = (-(CR * SP * CY + SR * SY));
	matrix.M[2][1] = (CY * SR - CR * SP * SY);
	matrix.M[2][2] = (CR * CP);
	matrix.M[2][3] = 0;

	matrix.M[3][0] = 0;
	matrix.M[3][1] = 0;
	matrix.M[3][2] = 0;
	matrix.M[3][3] = 1;

	return matrix;
}

struct MinimalViewInfo {
	Vector3A Location;
	Vector3A LocationLocalSpace;
	FRotator Rotation;
	float FOV;
};

struct FCameraCacheEntry {
	float TimeStamp;
	char chunks[0xC];
	MinimalViewInfo POV;
};

Vector2A WorldToScreen(Vector3A worldLocation, MinimalViewInfo camViewInfo, int width, int height) {
	FMatrix tempMatrix = RotatorToMatrix(camViewInfo.Rotation);

	Vector3A vAxisX(tempMatrix.M[0][0], tempMatrix.M[0][1], tempMatrix.M[0][2]);
	Vector3A vAxisY(tempMatrix.M[1][0], tempMatrix.M[1][1], tempMatrix.M[1][2]);
	Vector3A vAxisZ(tempMatrix.M[2][0], tempMatrix.M[2][1], tempMatrix.M[2][2]);

	Vector3A vDelta = worldLocation - camViewInfo.Location;

vAxisZ.Z += 85.0f;
	
	Vector3A vTransformed(Vector3A::Dot(vDelta, vAxisY), Vector3A::Dot(vDelta, vAxisZ), Vector3A::Dot(vDelta, vAxisX));

	if (vTransformed.Z < 1.0f) {
		vTransformed.Z = 1.0f;
	}

	float fov = camViewInfo.FOV;
	float screenCenterX = (width / 2.0f);
	float screenCenterY = (height / 2.0f);

	return Vector2A(
		(screenCenterX + vTransformed.X * (screenCenterX / tanf(fov * ((float)M_PI / 360.0f))) / vTransformed.Z),
		(screenCenterY - vTransformed.Y * (screenCenterX / tanf(fov * ((float)M_PI / 360.0f))) / vTransformed.Z)
	);
}



Vector3A WorldToScreen1(Vector3A obj , float matrix[16] , float pmx, float pmy, bool isBox) 
{
	
		
	   float ViewW = (matrix[3] * obj.X) + (matrix[7] * obj.Y) + (matrix[11] * obj.Z) + matrix[15];
		
		
		
		if( ViewW < 0.01)
		{
		    ViewW = 1.0f;
		}
		
	float addz = isBox ? 85 : 0; 
	
	float num2 = ((matrix[0] * obj.X) + (matrix[4] * obj.Y) + (matrix[8] * obj.Z+ matrix[12]));
	float num3 = ((matrix[1] * obj.X) + (matrix[5] * obj.Y) + (matrix[9] * (obj.Z+addz) + matrix[13])); 
	
		num2 /= ViewW; 
		num3 /= ViewW; 
		
		float BoxX = (pmx * num2 + (pmx));
		float BoxY = (-(pmy * num3) + (pmy));
		
		
		float num4 = ((matrix[1] * obj.X) + (matrix[5] * obj.Y) +(matrix[9] * (obj.Z-100)+matrix[13]));
		
		num4 /= ViewW; 
		
		float BoxY1 = (-(pmy * num4) + (num4 + pmy));
		
		float BoxH = BoxY-BoxY1;
		
		
	return Vector3A(BoxX,BoxY,BoxH);
}

		




enum Mode {
	InitMode = 1,
	ESPMode = 2,
	HackMode = 3,
	StopMode = 4,
};

struct Request {
	int Mode;
	int ScreenWidth;
	int ScreenHeight;
};

struct PlayerData {
	string PlayerName;
	int TeamID;
	float Health;
	float Distance;
	Vector2 Location;
	Vector2 HeadLocation;
};

struct VehicleData {
	string Name;
	float Distance;
	Vector2 Location;
};

struct ItemData {
	string Name;
	float Distance;
	Vector2 Location;
};

struct Response {
	bool Success;
	int PlayerCount;
	int VehicleCount;
	int ItemsCount;
	PlayerData Players[maxplayerCount];
	VehicleData Vehicles[maxvehicleCount];
	ItemData Items[maxitemsCount];
};



#endif
