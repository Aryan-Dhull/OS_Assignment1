#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc,char *argv[]){
	if(argv[1][0]=='-'){
		char *p=(char*)(argv[1]+1);
		if(*p=='v'){
			for(int i=2;i<argc;i++){
				int ret=0;
				ret=mkdir(argv[i],0755);
				if(ret==0)
					printf("mkdir : created directory '%s'\n",argv[i]);
				else
					printf("Unable to create directory %s\n:",argv[i]);
			}
		}
		else if(*p=='p'){
			for(int i=2;i<argc;i++){
				int ret=0;
				ret=mkdir(argv[i],0755);
			}
		}
		else{
			printf("No such option available\n");
		}
	}
	else{
		for(int i=1;i<argc;i++){
			int ret=0;
			ret=mkdir(argv[i],0755);
			if(ret==0){printf("Directory Ceated successfully\n");}
			else{printf("Unable to create directory %s\n",argv[i]);}
		}
	}
return 0;
}
