  This project is the first Assignment of 5812.
  This project provide a makefile to compile two files.
  (I combine the third and fourth answer in thesecond file)

  To compile on  machines, you will need to do the following:

1）command"make question.a" will generate a file named questionA.o
2）command"questionA.o xxx.tri" will generate .face file
3）command"questionA.o xxx.tri" will generate .diredge file

---------------------------------------------------------------------------------
			Complexity Analysis:
1）face2faceindex.cpp    
    The complexity of Main is O(n^2).
	
2) faceindex2directededge.cpp
    The complexity of Main is O(n),the complexity of calculateGenus is O(1),
the complexity of judgePinchPoint is O(1),the complexity of EdgeShare2Facesis O(n^2),the complexity of face2halfEdges is O(n),the complexity of findFirstDirectedEdge is O(n^2),the complexity of findotherhalf is O(n^2).
