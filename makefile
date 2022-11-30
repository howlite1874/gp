question.a:./face2faceindex.cpp ./Data.cpp
	g++ face2faceindex.cpp Data.cpp -o questionA.o

question.b: ./faceindex2directededge.cpp ./Data.cpp
	g++ faceindex2directededge.cpp Data.cpp -o questionB.o

clean:
	rm ./*.o
