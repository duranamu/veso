#include "parse_stream.h"
#define FOUND_COUNT_X3 30
const char * erro_msg = nil;
pcre * pcre_inst = nil;
int nOffset = -1;   
int found_pair[FOUND_COUNT_X3];
struct 
{
}__VSParser;
typedef const struct __VSParser * VSParserRef ;
UInt32 excutionModuleOntime(char* stream ,CFStringRef pattern,CFMutableArrayRef toFindStrings, CFMutableArrayRef replacementStrings)
{
	int match_count =0;
	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	while(CFStringMatchPatternforReplacement(code , pattern ,toFindStrings,replacementStrings) >= 0)
	{
		match_count++;
	}
	match_count?CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
}
unsigned int
	accessor(char* stream)
{
	int match_count =0;
	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	while(CFStringMatchPatternforReplacement(code,CFSTR("self(->[a-zA-Z_])+"),CFSTR("->"),CFSTR(".")) >= 0)
	{
		match_count++;
	}
	match_count?CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
}
unsigned int
	getter(char* stream)
{
	UInt32 match_count = 0;

	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	CFMutableArrayRef toFindStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("->"),CFSTR("get"),CFSTR("()"),nil);
	CFMutableArrayRef replacementStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("."),CFSTR(""),CFSTR(""),nil);
	while(CFStringMatchPatternforReplacement(code,CFSTR("->get[a-zA-Z_]*[(][)]"),toFindStrings,replacementStrings) >= 0)
	{
		match_count++;
	}
	match_count ? CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	
	CFRelease(code);

	return match_count;
}
unsigned int
	setter(char* stream)
{
	UInt32 match_count = 0;

	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	CFMutableArrayRef toFindStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("->set"),CFSTR("set"),nil);
	CFMutableArrayRef replacementStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("."),CFSTR(""),nil);
	while(CFStringMatchPatternforReplacement(code,CFSTR("->set[a-zA-Z_]*[(].*[)]"),
		toFindStrings,
		replacementStrings) >= 0)
	{
		CFStringMatchPatternforReplacement(code,CFSTR("[a-zA-Z0-9]*[(]"),CFSTR("("),CFSTR("="));
		CFStringMatchPatternforReplacement(code,CFSTR("[)]$"),CFSTR(")"),CFSTR(""));
		match_count++;
	}
	match_count ? CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
}
unsigned int
    postering(char* stream)
{
	UInt32 match_count = 0;

	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	CFMutableArrayRef toFindStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("::"),nil);
	CFMutableArrayRef replacementStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("->"),nil);
	while(CFStringMatchPatternforReplacement(code,CFSTR("[a-zA-Z_()]*::[a-zA-Z_]*[(][)]"),
		toFindStrings,
		replacementStrings) >= 0)
	{
		match_count++;
	}
	match_count?CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
 return match_count;
}
unsigned int
	messaging(char* stream)
{
	UInt32 match_count = 0;

	CFStringRef initiate_match_pattern = CFSTR("[\[]*[\ ]*[a-zA-Z]+[\ ]*[a-zA-Z]*[\]]*->[a-zA-Z]+[(][)]");
    CFStringRef iterate_match_pattern = CFSTR("[\[][\ ]*+[a-zA-Z]+([\ ]+[a-zA-Z]+[\]]+)*->[a-zA-Z]+[(][)]");
	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);
	CFMutableArrayRef toFindStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR("->"),CFSTR("()"),nil);
	CFMutableArrayRef replacementStrings = CFArrayCreateMutableWithObjects(nil,nil,
		CFSTR(" "),CFSTR("]"),nil);
	while(CFStringMatchPatternforReplacement(code ,
		match_count ? iterate_match_pattern : initiate_match_pattern ,
		toFindStrings,replacementStrings) >= 0)
	{
		match_count++;
		CFStringInsert(code,0,CFSTR("["));
	}
	match_count?CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
}
unsigned int
	iterator(char* stream)
{
	UInt32 match_count =0;
	CFMutableStringRef code = CFMutableStringCreateWithCString(nil,stream,300,kCFStringEncodingASCII);

	while(CFStringMatchPatternforReplacement(code,CFSTR("nfor[(].*,.*,.*[)]"),CFSTR("nfor"),CFSTR("for"))>= 0)
	{
		CFStringMatchPatternforReplacement(code,CFSTR(",[a-zA-Z\ \.]+[)]"),CFSTR(","),CFSTR("in"));
		CFStringMatchPatternforReplacement(code,CFSTR("for[(a-zA-Z\ \*]+,"),CFSTR(","),CFSTR(" "));
		match_count++;
	}
	match_count?CFStringGetCString(code,stream,200,kCFStringEncodingASCII):nil;
	CFRelease(code);
	return match_count;
}

void
VSParserTakeCStringtoStreamFile(char* stream , FILE* objc_file)
{
	unsigned int match_count = 0;
	match_count		 += getter(stream);
	match_count      += postering(stream);
	match_count      +=  messaging(stream); 
	match_count		 += accessor(stream);
	match_count		 += getter(stream);
	match_count		 +=  setter(stream);
	match_count      +=  iterator(stream);
	if(match_count)
		printf("%s",stream);
}