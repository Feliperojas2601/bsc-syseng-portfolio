compilar: makeHashTable.c p1-odProgram.C searchTime.c
	gcc makeHashTable.c -o makeHashTable
	gcc p1-odProgram.C -o p1-odProgram
	gcc searchTime.c -o searchTime