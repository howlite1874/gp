#include <iostream>
#include<vector>
#include<fstream>
#include <stdio.h>
#include<array>
#include<string>

#include"Data.cpp"
	
using namespace std;

int main(int argc, char** _argv) {

	string inputFIleName = _argv[1];
	ifstream* inputfile = new ifstream(inputFIleName);
	if (!inputfile->is_open()) {
		cout << "ERROR OCCURS WHEN OPENING FILE";
		return 0;
	}

	//remove the suffix to get the filename
	size_t found = inputFIleName.find_last_of('.');
	string Name = inputFIleName.substr(0, found);
	string outputFileName = Name + ".face";
	ofstream* outputFile = new ofstream(outputFileName);

	char facenumBuffer[10];
	inputfile->getline(facenumBuffer, 10);
	vector<vertex> repeatedVerts;
	vector<vertex> unrepeatedVerts;
	vector<array<int,3>> facesList;
	char vertexBuffer[100];
	int number=atoi(facenumBuffer);
	float buffer1,buffer2,buffer3;
	float x,y,z;
	
	//each line is a vertex of a face
	for (int i = 0; i < (number* 3); i++) {
		*inputfile>>buffer1>>buffer2>>buffer3;
		vertex onevertex1(i,buffer1,buffer2,buffer3);
		repeatedVerts.push_back(onevertex1);
	}
	
	//loop through each line,if this vertex has already been stored in the vector,then loop next vertex
	int count=0;
	for(int j=0;j<repeatedVerts.size();j++){
		bool flag=true;
			float x0,y0,z0;
			x0=repeatedVerts[j].x;
			y0=repeatedVerts[j].y;
			z0=repeatedVerts[j].z;
			for(int k=0;k<unrepeatedVerts.size();k++){
				float x1,y1,z1;
				x1=unrepeatedVerts[k].x;
				y1=unrepeatedVerts[k].y;
				z1=unrepeatedVerts[k].z;
				if(x0==x1&&y0==y1&&z0==z1){
					flag=false;
					break;
				}
			}
			if(flag==true){
				vertex onevertex2(count,x0,y0,z0);
				count++;
				unrepeatedVerts.push_back(onevertex2);
			}
		}

	//include the unrepeated vector we can find the index of each vertex,to every face,transfer detailed vertex into index of vertex
	array<int,3> oneface;
	for(int i=0;i<repeatedVerts.size();){
		for(int k=0;k<3;k++,i++){
		float x0=repeatedVerts[i].x;
		float y0=repeatedVerts[i].y;
		float z0=repeatedVerts[i].z;
			for(int j=0;j<unrepeatedVerts.size();j++){
			float x1=unrepeatedVerts[j].x;
			float y1=unrepeatedVerts[j].y;
			float z1=unrepeatedVerts[j].z;
				if(x0==x1&&y0==y1&&z0==z1){
				oneface[k]=j;
				break;
				}
			}
		}
		facesList.push_back(oneface);
	}

	*outputFile << "# University of Leeds 2022-2023" << endl;
	*outputFile << "# Chenxin Jiang" << endl;
	*outputFile << "# 201614769" << endl;
	*outputFile << "#" << endl;
	*outputFile << "# Object Name: " << Name << endl;
	*outputFile << "#  Vertices= " << unrepeatedVerts.size() << "   ";
	*outputFile << "#  Faces=" << number << endl;
	*outputFile << "#" << endl;
	

	for (int i = 0; i < unrepeatedVerts.size(); i++) {
		*outputFile << "Vertex " << i << " " << unrepeatedVerts[i].x<<" " << unrepeatedVerts[i].y<<" " << unrepeatedVerts[i].z<< endl;
	}
	for (int i = 0; i < facesList.size(); i++) {
		*outputFile << "Face " << i << " " << facesList[i][0]<<" "<<facesList[i][1]<<" "<<facesList[i][2]<<endl;
	}
	inputfile->close();
	outputFile->close();

	return 0;

}

