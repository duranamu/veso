#pragma once
#ifdef WIN32
#include<direct.h>
#define getcwd  _getcwd
#endif
#define nil NULL
#include<CoreFoundation/CoreFoundation.h>
#include<pcre.h>
void
	offerCurrentWorkingDirectoryWithCString(char* pwd);
char*  
	readSourceCodeFromFile (const char *path );
void
	maybeUseful();