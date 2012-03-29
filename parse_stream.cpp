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
void
	match_for_replace(CFMutableStringRef code,char* stream,CFStringRef stringToFind,CFStringRef replacementString)
{
	const char * erro = nil;
	int offset = -1;  
	int found_range[FOUND_COUNT_X3];
	if(pcre_exec(pcre_compile("[a-zA-Z0-9]*[(]", 0, &erro, &offset, nil), nil, stream, strlen(stream), 0, 0, found_range, FOUND_COUNT_X3)>0)
	{
	CFRange detailRange ;
	detailRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);
	CFStringFindAndReplace(code,stringToFind,replacementString,detailRange,0);
	CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
	}
}
unsigned int
	accessor(char* stream)
{
	const char * match_pattern = "self(->[a-zA-Z_])+";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
int match_count =0;
while(res >=0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,300,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);


CFStringFindAndReplace(code,CFSTR("->"),CFSTR("."),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("."))-CFStringGetLength(CFSTR("->"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
return match_count;
}
unsigned int
	getter(char* stream)
{
const char * match_pattern = "->get[a-zA-Z_]*[(][)]";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
int match_count =0;
while(res >=0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,300,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);

CFStringFindAndReplace(code,CFSTR("->"),CFSTR("."),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("."))-CFStringGetLength(CFSTR("->"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);

CFStringFindAndReplace(code,CFSTR("get"),CFSTR(""),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(""))-CFStringGetLength(CFSTR("get"));

CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
CFStringFindAndReplace(code,CFSTR("()"),CFSTR(""),searchRange,0);
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
return match_count;
}
unsigned int
	setter(char* stream)
{
const char * match_pattern = "->set[a-zA-Z_]*[(][a-zA-Z_0-9\.\ ]*(ccp[(][0-9]+,[0-9]+[)])*[)]";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
int match_count =0;
if(res >=0)
{


match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,300,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);

CFStringFindAndReplace(code,CFSTR("->"),CFSTR("."),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("."))-CFStringGetLength(CFSTR("->"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);


CFStringFindAndReplace(code,CFSTR("set"),CFSTR(""),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(""))-CFStringGetLength(CFSTR("set"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);

if(pcre_exec(pcre_compile("[a-zA-Z0-9]*[(]", 0, &erro_msg, &nOffset, nil), nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3)>0)
{
CFRange detailRange ;
detailRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);
CFStringFindAndReplace(code,CFSTR("("),CFSTR("="),detailRange,0);
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
}

CFStringFindAndReplace(code,CFSTR(")"),CFSTR(""),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(""))-CFStringGetLength(CFSTR(")"));


CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
return match_count;
}
unsigned int
    postering(char* stream)
{
const char * match_pattern = "[a-zA-Z_()]*::[a-zA-Z_]*[(][)]";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
int match_count =0;
while(res >=0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,200,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);
        
CFStringFindAndReplace(code,CFSTR("::"),CFSTR("->"),searchRange,0);
//searchRange.length += CFStringGetLength(CFSTR("->"))-CFStringGetLength(CFSTR("::"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
        
res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
 return match_count;
}
unsigned int
	messaging(char* stream)
{
const char * match_pattern = "[\[]*[a-zA-Z]+[\ ]*[a-zA-Z]*[\]]*->[a-zA-Z]+[(][)]";
   const char * iterate_match_pattern = "[\[]+[a-zA-Z]+([\ ]+[a-zA-Z]+[\]]+)*->[a-zA-Z]+[(][)]";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
    pcre* iterate_pcre_inst = pcre_compile(iterate_match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
    
int match_count =0;
while(res >=0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,300,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);

CFStringInsert(code,searchRange.location,CFSTR("["));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
searchRange.location += CFStringGetLength(CFSTR("["));

CFStringFindAndReplace(code,CFSTR("->"),CFSTR(" "),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(" "))-CFStringGetLength(CFSTR("->"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);

CFStringFindAndReplace(code,CFSTR("()"),CFSTR("]"),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("]"))-CFStringGetLength(CFSTR("()"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);


res = pcre_exec(iterate_pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
return match_count;
}
unsigned int
	iterator(char* stream)
{
const char * match_pattern = "nfor[(].*,.*,.*[)]";
pcre_inst = pcre_compile(match_pattern, 0, &erro_msg, &nOffset, nil);
int res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
int match_count =0;
if(res >=0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,200,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);


CFStringFindAndReplace(code,CFSTR("nfor"),CFSTR("for"),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("for"))-CFStringGetLength(CFSTR("nfor"));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);

CFStringFindAndReplace(code,CFSTR(","),CFSTR(" in "),searchRange,kCFCompareAnchored);
searchRange.length += CFStringGetLength(CFSTR(" in "))-CFStringGetLength(CFSTR(","));

CFStringGetCString(code,stream,200,kCFStringEncodingASCII);

const char * another_match_pattern = ",[a-zA-Z\ \.]+[)]";
pcre* another_pcre_inst = pcre_compile(another_match_pattern, 0, &erro_msg, &nOffset, nil);
res = pcre_exec(another_pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
if(res >= 0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,200,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);

CFStringFindAndReplace(code,CFSTR(","),CFSTR("in"),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR("in"))-CFStringGetLength(CFSTR(","));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
}

const char * third_match_pattern = "for[(a-zA-Z\ \*]+,";
pcre* third_pcre_inst = pcre_compile(third_match_pattern, 0, &erro_msg, &nOffset, nil);
res = pcre_exec(third_pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
if(res >= 0)
{
match_count++;
CFStringRef objCode;
objCode = CFStringCreateWithCString(nil,stream,kCFStringEncodingASCII);
CFMutableStringRef code;
code = CFStringCreateMutableCopy(nil,200,objCode);
CFRange searchRange ;
searchRange = CFRangeMake(found_pair[0],found_pair[1]-found_pair[0]);

CFStringFindAndReplace(code,CFSTR(","),CFSTR(" "),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(" "))-CFStringGetLength(CFSTR(","));
CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
}
}
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