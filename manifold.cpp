#include<string>
#include<fstream>
#include<iostream>
#include<vector>
#include "Data.cpp"

using namespace std;







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

    vector<vertex> vertsList;
	vector<face> facesList;
    vector<halfedge> otherhalfedgesList;
	string Buffer1;
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
        else if(Buffer1 == "OtherHalf"){
            int Buffer2,Buffer3;
			*inputFile>>Buffer2>>Buffer3;
			halfedge onehalfEdge(Buffer2,Buffer3);
			otherhalfedgesList.push_back(onehalfEdge);
        }
	}



	*outputFile <<vertsList.size()<<" "<<facesList.size()<<" "<<otherhalfedgesList.size()<<endl;

	for (int i = 0; i < vertsList.size(); i++) {
		*outputFile << "Vertex " << i << " " << vertsList[i].x <<" " << vertsList[i].y <<" " << vertsList[i].z << endl;
	}

	for (int i = 0; i < facesList.size(); i++) {
		*outputFile << "Face " << i << " " <<  facesList[i].firstIndex<< " " << facesList[i].secondIndex <<" "<< facesList[i].thirdIndex << endl;
	}

	for (int i = 0; i < otherhalfedgesList.size(); i++) {
		*outputFile << "OtherHalf " << i << " " << otherhalfedgesList[i].bVertex<<" "<<otherhalfedgesList[i].eVertex <<endl;
	}

	inputFile->close();
	outputFile->close();
	return 0;
}
