#include"Utils.h"
#include "parse_stream.h"
void parse_file_create(char* path)
{
	char filePath[200] = "";
	strcpy(filePath,path);
	FILE* cpp_file = fopen(filePath,"r");
	strcat(filePath,"m");
	FILE* objc_file = fopen(filePath,"w");
	char stream[500] ="";
	char branch_stream[500] ="";
	bool newToken = true;
	bool leadingWhitespace = false;

	while(fscanf(cpp_file,"%c",stream)!= EOF)
	{
		if( stream[0] ==' ')
		{
			newToken ? nil : strcat(branch_stream," ");

		}else if ( stream[0] =='\n' | stream[0] == '\t' | stream[0] == '\r')
		{
			newToken = false;
			leadingWhitespace = true;
		}
		else if( stream[0] == '#')
		{
			char aLine[200];
			fgets(aLine,200,cpp_file);
			strcat(branch_stream,"#");
			strcat(branch_stream,aLine);
			VSParserTakeTokenstoStreamFile(branch_stream,objc_file);
			strcpy(branch_stream,"");
			strcpy(stream,"");
			newToken = true;
		}
		else if( stream[0] == ';' 
		  | stream[0] == '='
		  | stream[0] == '|'
		  | stream[0] == '&'
		  )
		{
			VSParserTakeTokenstoStreamFile(branch_stream,objc_file);
			strcpy(branch_stream,"");
			newToken = true;
		}else if ( 
			stream[0] == '{'
		  | stream[0] == '}'
		  )
		{
			if(strlen(branch_stream)>0)
				VSParserTakeBlockstoStreamFile(branch_stream,objc_file);
			strcpy(branch_stream,"");
			newToken = true;
		}else{
			if(leadingWhitespace)
			{
				strcat(branch_stream," ");
				leadingWhitespace = false;
			}
			strcat(branch_stream,stream);
			newToken = false;
		}
    }
	fclose(cpp_file);
	fclose(objc_file);
}
int main()
{

	parse_file_create("C:/Library/Framework/Cocos/UIKit/UITableViewCell.cpp");
}