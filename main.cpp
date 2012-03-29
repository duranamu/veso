#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
 #endif
int main2()
{
	FILE* cppFile = fopen("NIKit//Kinect.h","r+");
	char cwd[120];
	getcwd(cwd,120);
	char  cppStr[120];
	fscanf(cppFile,"%s",cppStr);

	char lookupTable[5000];

	return 0;
}