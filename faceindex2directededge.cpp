#include <iostream>
#include<vector>
#include<fstream>
#include<string>
#include<istream>
#include<queue>

#include "Data.cpp"

using namespace std;


//calculate genus according to  Euler's Formula
int calculateGenus(int a, int b,int c){
	int genus;
	genus=1-(a-b+c)/2;
	return genus;
}


bool judgeContinus(vector<halfedge> halfEdges,vector<vertex> vertsList){
	queue<vertex> vertexQueue;
	vector<int> visited;
	for(int i=0;i<vertsList.size();i++){
		visited[i]=0;
	}
	vertexQueue.push(vertsList[0]);
	visited[0]==1;
	while(!vertexQueue.empty()){
		vertex tmp=vertexQueue.back();
		vertexQueue.pop();
		int n=tmp.index;
		bool flag=false;
		for(int j=0;j<halfEdges.size();j++){
			if(halfEdges[j].bVertex==n&&visited[halfEdges[j].eVertex]==0){
				flag=true;
				visited[halfEdges[j].eVertex]==1;
				vertexQueue.push(vertsList[halfEdges[j].eVertex]);
			}
		}
		if(flag==false){
			int index=n;
			if(visited[index]==0){
				visited[index]=1;
			}
		}
	}
	for(int i=0;i<visited.size();i++){
		if(visited[i]==0){
			return false;
		}
	}
	return true;
}



//To each vertex,the first circle is along at first directed edge,after two more steps,the last edge will always go back to this vertex, 
//we should find whether this edge has otherhalf so we can begin a new circle
//if this is manifold, the times of we successfully find otherhalf should equals to the number of face -1
bool judgePinchPoint(int n, vector<face> faces, ofstream* outputFile,vector<halfedge> halfEdges,vector<int> FirstDirectedEdge,vector<int> otherHalf){
    vector<face> facesOfVertex;
	bool flag2=true;
    for(int i=0;i<n;i++){
		for(face oneface: faces){
            if(oneface.firstIndex==i ||oneface.secondIndex==i || oneface.thirdIndex==i ){
                facesOfVertex.push_back(oneface);
            }
        }
		int currentEdgeIndex=FirstDirectedEdge[i];
		int countface=0;
		int index;
		while(1){                       //loop until either it satisfies the condition of manifold or cannot find otherhalf
			index=currentEdgeIndex+2;
			bool flag=false;
			if(otherHalf[index]!=-1){
				index=otherHalf[index];
				countface++;
				}
			else break;
			if((countface+1)==facesOfVertex.size()){
				break;
			}
		}
		if((countface+1)!=facesOfVertex.size()){
			*outputFile<<"Fail Vertex "<<i<<endl;
			flag2=false;
		}
    }
	*outputFile<<"the second condition is satisfied."<<endl;
    return true;
}


//all edges share two faces and no more than two faces
bool EdgeShare2Faces(vector<int> &otherHalf,ofstream *outputFile){
    int m=otherHalf.size();
	bool flag=true;
	for(int i=0;i<m;i++){
		if(otherHalf[i]==-1){
			*outputFile<<"Fail HalfEdge"<<i<<endl;    //to judge if this edge has other halfedge
			flag=false;
			}
		for(int j=0;j<m;j++){
			if(otherHalf[i]==otherHalf[j]&&i!=j){               //to judge if this edge has more than one other half edges
			*outputFile<<"Fail HalfEdge "<<j<<endl;
			flag=false;
			}
		}
	}
	*outputFile<<"the first condition is satisfied."<<endl;
	return flag;
}


//loop through every face to get three halfedges each 
void face2halfEdges(vector<face> &facesList,vector<halfedge> *halfEdges) {
	for(int i=0;i<facesList.size();i++){
		int x=facesList[i].firstIndex;
		int y=facesList[i].secondIndex;
		int z=facesList[i].thirdIndex;
		halfedge e0(x,y);
		halfedge e1(y,z);
		halfedge e2(z,x);
		halfEdges->push_back(e0);  
        halfEdges->push_back(e1);
        halfEdges->push_back(e2);
	}
}

//loop through every vertex to find first halfedge that begin from this vertex
void findFirstDirectedEdge(vector<halfedge> &halfEdges,int n,vector<int> *FirstDirectedEdge){
	for(int i=0;i<n;i++){
		for(int j=0;j<halfEdges.size();j++){   
            if(halfEdges[j].bVertex==i){
                FirstDirectedEdge->push_back(j);
                break;
            }
		}
	}
}

//loop through every halfedge to find whether it has otherhalf,if not assgin -1 
void findotherhalf(int m,vector<halfedge> &halfEdges,vector<int> *otherHalf){
	for(int i=0;i<m;i++){
		int b=halfEdges[i].bVertex;
		int e=halfEdges[i].eVertex;
		bool flag=false;
		for(int j=0;j<m;j++){
			if(halfEdges[j].bVertex==e&&halfEdges[j].eVertex==b){
				otherHalf->push_back(j);
				flag=true;
				break;
			}
		}
		if(flag==false){
			otherHalf->push_back(-1);
		}
	}

}




int main(int argc, char** _argv) {

	//read && write 
		
	string inputFIleName = _argv[1];
	ifstream* inputFile = new ifstream(inputFIleName);
	if (!inputFile->is_open()) {
		cout << "ERROR OCCURS WHEN OPENING FILE";
		return 0;
	}

	size_t found = inputFIleName.find_last_of('.');
	string outputFileName = inputFIleName.substr(0, found);
	outputFileName = outputFileName + ".diredge";
	ofstream* outputFile = new ofstream(outputFileName);
	if (!outputFile->is_open()) {
		cout << "ERROR OCCURS WHEN OPENING FILE";
		return 0;
	}

	//read vertex or face info
	vector<vertex> vertsList;
	vector<face> facesList;
	string Buffer1;
	int count=0;
		while (*inputFile>>Buffer1) {
		if (Buffer1 == "Vertex") {
			int Buffer2;
			float Buffer3,Buffer4,Buffer5;
			*inputFile>>Buffer2>>Buffer3>>Buffer4>>Buffer5;
			vertex onevertex(Buffer2,Buffer3,Buffer4,Buffer5);
			vertsList.push_back(onevertex);
		}
		else if (Buffer1 == "Face") {
			int Buffer2,Buffer3,Buffer4,Buffer5;
			*inputFile>>Buffer2>>Buffer3>>Buffer4>>Buffer5;
			face oneface(Buffer3,Buffer4,Buffer5);
			facesList.push_back(oneface);
		}
	}

	//call specific method to get halfedge 、directedEdge and otherhalf 
	vector<halfedge> halfEdges;
	face2halfEdges(facesList, &halfEdges);
	vector<int> FirstDirectedEdge;
	int n=vertsList.size();
	findFirstDirectedEdge(halfEdges,n,&FirstDirectedEdge);
	int m=halfEdges.size();
	vector<int> otherHalf;
	findotherhalf(m,halfEdges,&otherHalf);


	
	*outputFile << "# University of Leeds 2022-2023" << endl;
	*outputFile << "# COMP 5812M Assignment 1" << endl;
	*outputFile << "# Chenxin Jiang" << endl;
	*outputFile << "# 201614769" << endl;
	*outputFile << "#" << endl;
    *outputFile << "# Object Name: " << outputFileName << endl;
	*outputFile << "#  Vertices= " << n << "   ";
	*outputFile << "#  Faces=" << facesList.size() << endl;
	*outputFile << "#" << endl;

	for (int i = 0; i < vertsList.size(); i++) {
		*outputFile << "Vertex " << i << " " << vertsList[i].x <<" " << vertsList[i].y <<" " << vertsList[i].z << endl;
	}
	for (int i = 0; i < FirstDirectedEdge.size(); i++) {
		*outputFile << "FirstDirectedEdge " << i << " " << FirstDirectedEdge[i]<<endl;
	}
	for (int i = 0; i < facesList.size(); i++) {
		*outputFile << "Face " << i << " " <<  facesList[i].firstIndex<< " " << facesList[i].secondIndex <<" "<< facesList[i].thirdIndex << endl;
	}
	for (int i = 0; i < otherHalf.size(); i++) {
		*outputFile << "OtherHalf " << i << " " << otherHalf[i] <<endl;
	}

	//manifold test :should satisfy two conditions
	*outputFile <<"------------------------------"<<endl;
	*outputFile << "Manifold Test:"<<endl;
	bool condition1=EdgeShare2Faces(otherHalf,outputFile);
	if(condition1){
		bool condition2=judgePinchPoint(n, facesList, outputFile,halfEdges,FirstDirectedEdge,otherHalf);
		if(condition2){
		*outputFile<<"It is Manifold"<<endl;
		int genus = calculateGenus(n, halfEdges.size()/2, facesList.size());
        *outputFile<<"The genus of this object is "<<genus<<endl;
		}
		else{
			*outputFile<<"It is not Manifold"<<endl;
		}
	}
	else{
		*outputFile<<"It is not Manifold"<<endl;
	}

	bool condition3=judgeContinus(halfEdges,vertsList);
	if(!condition3){
		*outputFile<<"not continus"<<endl;
	}
  

	inputFile->close();
	outputFile->close();

	return 0;
}


