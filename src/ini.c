#include "stdio.h"
#include "string.h"
#include "stdlib.h"

void unamed1(FILE *file,const char *str,const char cha,const char not)
{
	char *tmp=malloc(strlen(str)+1);
	while(1)
	{	char ch;
		do
		{
			ch=fgetc(file);
		} while (ch!=cha && feof(file)==0 && ch!=not);
		
		
		if(feof(file) || ch==not)
		{
			fseek(file,0,SEEK_END);
			fgetc(file);
			return;
		}
		fgets(tmp,strlen(str)+1,file);
		if(!strncmp(tmp,str,strlen(str)+1))
		{
			free(tmp);
			return;
		}
	}
}

void* getSettings(char *section,char *parametre)
{
	FILE *file=NULL;
	char *stmp;
	int  *itmp;

	if (stmp==NULL)
	{
		printf("chaine temporaire non alloue");
		return NULL;
	}
	
	if((file=fopen("bin\\settings.ini","r"))==NULL)
	{
		printf("Le fichier ini n'a pas pu etre ouvert");
		return NULL;
	}
	unamed1(file,section,'[','\0');
	if(feof(file)!=0)
		{
			printf("Section non trouver");
			return NULL;
		}
	unamed1(file,parametre,'\n','[');
	if(feof(file)!=0)
		{
			printf("parametre non trouver");
			return NULL;
		}
	fgetc(file);
	if(fgetc(file)=='"')
	{
		long position=ftell(file);
		int i=0;
		for(char ch=fgetc(file);ch!='"';i++,ch=fgetc(file));
		stmp=malloc(i+1);
		if(stmp==NULL)
		{
			printf("allocation echouer");
			return NULL;
		}
		fseek(file,position,SEEK_SET);
		fgets(stmp,i+1,file);
		fclose(file);
		return stmp;
	}
	else
	{
		fseek(file,-1,SEEK_CUR);
		itmp=malloc(sizeof(int));
		if(itmp==NULL)
		{
			printf("allocation echouer");
			return NULL;
		}
		fscanf(file,"%d",itmp);
		fclose(file);
		return itmp;
	}

}
/*
int main(int args,char **argv)
{
	int *i;
	char *str;
	if(args==3)
	{
		i=getSettings(argv[1],argv[2]);
		if(i)
			printf("[%s] : %s=%d",argv[1],argv[2],*i);
		free(i);
	}
	if(args==4)
	{
		str=getSettings(argv[1],argv[2]);
		if(str)
			printf("[%s] : %s=%s",argv[1],argv[2],str);
		free(str);
	}
	return 0;
}*/