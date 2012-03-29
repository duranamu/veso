#include"Utils.h"
#include "parse_stream.h"
void parse_file_create(char* path)
{
	char filePath[200] = "";
	strcpy(filePath,path);
	FILE* cpp_file = fopen(filePath,"r");
	strcat(filePath,"m");
	FILE* objc_file = fopen(filePath,"w");
	char stream[2000] ="";
	char branch_stream[200] ="";
	bool needsConfluence = false;


	while(fscanf(cpp_file,"%c",stream)!= EOF)
	{
		if( stream[0] == '#')
		{
			char aLine[200];
			fgets(aLine,200,cpp_file);
			strcat(branch_stream,"#");
			strcat(branch_stream,aLine);
			VSParserTakeCStringtoStreamFile(branch_stream,objc_file);
			strcpy(branch_stream,"");
			strcpy(stream,"");
		}
		if( stream[0] == ';' 
		  | stream[0] == '{'
		  | stream[0] == '}'
		  )
		{
			VSParserTakeCStringtoStreamFile(branch_stream,objc_file);
			strcpy(branch_stream,"");
		}else{
			strcat(branch_stream,stream);
		}
    }

	fclose(cpp_file);
	fclose(objc_file);
}
int main()
{
	parse_file_create("C:/Library/Framework/Cocos/UIKit/UITableViewCell.cpp");
}