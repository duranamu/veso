#include "Utils.h"
void
	offerCurrentWorkingDirectoryWithCString(char* pwd)
{
	getcwd(pwd,120);
}
char*  
	readSourceCodeFromFile (const char *path ) {
    CFDataRef data = nil;
	CFStringRef str ;

    FILE* file = fopen (path, "r");

	if (file == nil) {
		fprintf(stderr, "Cannot open `%s' for reading.\n", path);
	} else {
        int result = fseek (file, 0, SEEK_END);
        result = ftell (file);
        rewind (file);

         char* buffer = (char*)calloc (1, result);

        if (buffer != nil) {
            int rc = (int)fread (buffer, result, 1, file);
            if (rc > 0 || !ferror (file)) {
             //   data = CFDataCreate (nil, (const UInt8*)buffer, result);
				fclose (file);
				return buffer;
            }
        } 
    }
	return nil;
}
void
	maybeUseful()
{
	CFStringRef str ;
	char* buffer = readSourceCodeFromFile("UIKit/UIView.h"); 
	str = CFStringCreateWithCString(nil,buffer,kCFStringEncodingASCII);
	CFRelease(str);
}