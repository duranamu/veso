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
if(match_count)
printf("%s",stream);
}
void
	setter(char* stream)
{
const char * match_pattern = "->set[a-zA-Z_]*[(][a-zA-Z_]*[)]";
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


CFStringFindAndReplace(code,CFSTR("set"),CFSTR(""),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(""))-CFStringGetLength(CFSTR("get"));


CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
CFStringFindAndReplace(code,CFSTR("("),CFSTR("="),searchRange,0);


CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
CFStringFindAndReplace(code,CFSTR(")"),CFSTR(""),searchRange,0);
searchRange.length += CFStringGetLength(CFSTR(""))-CFStringGetLength(CFSTR(")"));


CFStringGetCString(code,stream,200,kCFStringEncodingASCII);
res = pcre_exec(pcre_inst, nil, stream, strlen(stream), 0, 0, found_pair, FOUND_COUNT_X3);
}
if(match_count)
printf("%s",stream);
}
void
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
 
}
void
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
if(match_count)
printf("%s",stream);
}
void
VSParserTakeCStringtoStreamFile(char* stream , FILE* objc_file)
{
	getter(stream);
	setter(stream);
    postering(stream);
	messaging(stream);
}