#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE
using namespace std;
#include <array>
#include <string>


/// <summary>
/// the class of vertex includes index and position of x y z
/// </summary>
class vertex {
public:
	vertex();
	vertex(int I,float X, float Y, float Z):index(I),x(X), y(Y), z(Z) {};
	float x, y, z;	
	int index;
};

/// <summary>
/// the class of face includes three vertex index 
/// </summary>
class face {
public:
	face();
	face(int x,int y,int z):firstIndex(x), secondIndex(y), thirdIndex(z) {}
	int firstIndex;
	int secondIndex;
	int thirdIndex;

};

/// <summary>
/// the class of halfedge includes begining vertex index and ending vertex index
/// </summary>
class halfedge {
public:
	halfedge();
	halfedge(int b, int e):bVertex(b),eVertex(e) {}
	int bVertex = -1;
	int eVertex = -1;
};


#endif