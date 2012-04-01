#include "Utils.h"
#define FOUND_COUNT_X3 30
char*
	CStringFromCFMutableString(CFMutableStringRef theString)
{
	char* cStr = (char*)malloc(sizeof(char)*CFStringGetLength(theString)+1);
	CFStringGetCString(theString,cStr,strlen(cStr),kCFStringEncodingASCII);
	return cStr;
}
char*
	CStringFromCFString(CFStringRef theString)
{
	char* cStr = (char*)malloc(sizeof(char)*CFStringGetLength(theString)+1);
	CFStringGetCString(theString,cStr,strlen(cStr),kCFStringEncodingASCII);
	return cStr;
}
void
	offerCurrentWorkingDirectoryWithCString(char* pwd)
{
	getcwd(pwd,120);
}
char*  
	readSourcetheStringFromFile (const char *path ) {
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
SInt32
	CFStringMatchPatternforReplacement(CFMutableStringRef theString,CFStringRef matchPattern,CFArrayRef stringToFindArray,CFArrayRef replacementStringArray)
{
	char* stream = CStringFromCFMutableString(theString);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	char* match_pattern = CStringFromCFString(matchPattern);
	CFStringGetCString(matchPattern,match_pattern,120,kCFStringEncodingASCII);
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFRange detailRange ;
		detailRange = CFRangeMake(found_range[0],found_range[1]-found_range[0]);

		UInt32 arrayCount = CFArrayGetCount(stringToFindArray);

		for(UInt32 i = 0; i< arrayCount ; i++)
		{
			CFStringRef stringToFind =  (CFStringRef)CFArrayGetValueAtIndex(stringToFindArray,i);
			CFStringRef replacementString = (CFStringRef)CFArrayGetValueAtIndex(replacementStringArray,i);

			CFStringFindAndReplace(theString,stringToFind,replacementString,detailRange,0);
			detailRange.length += CFStringGetLength(replacementString)-CFStringGetLength(stringToFind);
		}
	}
	free(stream);
	free(match_pattern);
	return matchCount;
}
SInt32
	CFStringMatchPatternforReplacement(CFMutableStringRef theString,CFStringRef matchPattern,CFStringRef stringToFind,CFStringRef replacementString)
{
	char* stream = CStringFromCFMutableString(theString);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	char* match_pattern = CStringFromCFString(matchPattern);
	CFStringGetCString(matchPattern,match_pattern,120,kCFStringEncodingASCII);
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFRange detailRange ;
		detailRange = CFRangeMake(found_range[0],found_range[1]-found_range[0]);
		CFStringFindAndReplace(theString,stringToFind,replacementString,detailRange,0);
		detailRange.length += CFStringGetLength(replacementString)-CFStringGetLength(stringToFind);
	}
	free(stream);
	return matchCount;
}
SInt32
	CFStringMatchPatternforPreInsert(CFMutableStringRef theString,CFStringRef matchPattern,CFStringRef stringToInsert)
{
	char* stream = CStringFromCFMutableString(theString);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	char* match_pattern = CStringFromCFString(matchPattern);
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFStringInsert(theString,found_range[0],stringToInsert);
		matchCount++;
	}
	free(stream);
	free(match_pattern);
	return matchCount;
}
SInt32
	CFStringMatchPatternforPostInsert(CFMutableStringRef theString,CFStringRef matchPattern,CFStringRef stringToInsert)
{
	char* stream = CStringFromCFMutableString(theString);
	char* match_pattern = CStringFromCFString(matchPattern);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFStringInsert(theString,found_range[1],stringToInsert);
		matchCount++;
	}
	free(stream);
	free(match_pattern);
	return matchCount;
}
SInt32
	CFStringMatchPatternforMultiPreInsert(CFMutableStringRef theString,CFStringRef matchPattern ,CFStringRef stringToInsert)
{
	char* stream = CStringFromCFMutableString(theString);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	char* match_pattern = CStringFromCFString(matchPattern);
	SInt32 matchCount =  0;
	UInt32 startOffsetForIteration = 0;
	while(pcre_exec(
			pcre_compile(match_pattern, 0, &erro, &offset, nil),
			nil, stream, strlen(stream), startOffsetForIteration, 0, found_range, FOUND_COUNT_X3
			)>= 0 
		 )
	{
		CFStringInsert(theString,found_range[0] + CFStringGetLength(stringToInsert)*(matchCount++),stringToInsert);
		startOffsetForIteration = found_range[1] ;
	}
	free(stream);
	free(match_pattern);
	return matchCount;
}
SInt32
	CFStringMatchPatternforDeletion(CFMutableStringRef theString,CFStringRef matchPattern )
{
	char* stream = CStringFromCFMutableString(theString);
	char* match_pattern = CStringFromCFString(matchPattern);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	CFStringGetCString(matchPattern,match_pattern,120,kCFStringEncodingASCII);
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFRange deleteRange;
		deleteRange = CFRangeMake(found_range[0] ,found_range[1]-found_range[0]);
		CFStringDelete(theString,deleteRange);
		matchCount++;
	}
	free(stream);
	free(match_pattern);
	return matchCount;
}
UniChar*
	CFStringMatchPatternforExtraction(CFMutableStringRef theString,CFStringRef matchPattern )
{
	CFMutableStringRef deletedString ;
	char* stream = CStringFromCFMutableString(theString);
	char* match_pattern = CStringFromCFString(matchPattern);
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	CFStringGetCString(matchPattern,match_pattern,120,kCFStringEncodingASCII);
	UniChar* deleteCStr ;
	SInt32 matchCount = (pcre_exec(pcre_compile(match_pattern, 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3));
	if(matchCount >=0)
	{
		CFRange deleteRange;
		deleteRange = CFRangeMake(found_range[0] ,found_range[1]-found_range[0]);
		deleteCStr = (UniChar*)malloc(sizeof(UniChar)*(deleteRange.length+1));
		CFStringGetCharacters(theString,deleteRange,deleteCStr);
		CFStringDelete(theString,deleteRange);
		matchCount++;
		free(deleteCStr);
	}
	free(stream);
	free(match_pattern);
	return deleteCStr;
}

CFMutableStringRef
	CFMutableStringCreateWithCString(CFAllocatorRef allocator ,const char* cStr,CFIndex maxLength,CFStringEncoding encoding)
{
	CFStringRef str = CFStringCreateWithCString(allocator,cStr,encoding);
	CFMutableStringRef mutableStr = CFStringCreateMutableCopy(allocator,maxLength,str);
	CFRelease(str);
	return mutableStr;
}
CFMutableArrayRef
	CFArrayCreateMutableWithObjects(CFAllocatorRef allocator ,const CFArrayCallBacks* callBack,CFTypeRef ref,...)
{
	CFMutableArrayRef array = CFArrayCreateMutable(allocator,80,callBack);

	if(ref)
		CFArrayAppendValue(array,ref);

	va_list argp;
	va_start(argp , ref);
	CFTypeRef* para;

	while(1)
	{
		para = va_arg(argp , CFTypeRef * );
		if( para != nil)
		{
			CFArrayAppendValue(array,para);
		}else{
			break;
		}
	}
	va_end (argp);
	return array;
}
