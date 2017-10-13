/*
 WAP to search a given file in a given directory?
               Hint : ./a.out /home/folder/ file
*/
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("Usage :./a.out path filename\n");
		return;
	}
	char *path;
	printf("%s found in %s %d times\n",argv[2],argv[1],search(argv[1],argv[2]));
	return 0;
}

int search(char *path,char *name)
{
	static int count=0;
	char *fullpath;
	fullpath=malloc(500);
	DIR *dp;
	dp=opendir(path);
	if(dp==0)
	{
		perror("opendir");
		exit(0);
	}
	struct stat p;
	struct dirent *v;
	while(v=readdir(dp))
	{
		if(v->d_name[0]=='.')
			continue;
		strcpy(fullpath,path);
		strcat(fullpath,"/");
		strcat(fullpath,v->d_name);
		lstat(fullpath,&p);
		if(S_ISDIR(p.st_mode))
			search(fullpath,name);
		else if(S_ISREG(p.st_mode))
			if(strcmp(v->d_name,name)==0)
				count++; 
	}  
	free(fullpath); 
	return count;
}


