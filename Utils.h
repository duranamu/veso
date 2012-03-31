#pragma once
#ifdef WIN32
#include<direct.h>
#define getcwd  _getcwd
#endif
#define nil NULL
#include<CoreFoundation/CoreFoundation.h>
#include<pcre.h>
#include<stdarg.h>
SInt32
	CFStringMatchPatternforReplacement(CFMutableStringRef theString,CFStringRef matchPattern,CFArrayRef stringToFindArray,CFArrayRef replacementStringArray);
SInt32
	CFStringMatchPatternforReplacement(CFMutableStringRef theString,CFStringRef matchPattern,CFStringRef stringToFind,CFStringRef replacementString);
SInt32
	CFStringMatchPatternforInsertBefore(CFMutableStringRef theString,CFStringRef matchPattern ,CFStringRef stringToInsert);
SInt32
	CFStringMatchPatternforDeletion(CFMutableStringRef theString,CFStringRef matchPattern );
SInt32
	CFStringMatchPatternforInsertAfter(CFMutableStringRef theString,CFStringRef matchPattern ,CFStringRef stringToInsert);


CFMutableStringRef
	CFMutableStringCreateWithCString(CFAllocatorRef allocator ,const char* cStr,CFIndex maxLength,CFStringEncoding encoding);
CFMutableArrayRef
	CFArrayCreateMutableWithObjects(CFAllocatorRef allocator ,const CFArrayCallBacks* callBack,CFTypeRef ref,...);