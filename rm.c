#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	if(argv[1][0]=='1'){
		char *p=(char*)(argv[1]+1);
		if(*p=='v'){
			for(int i=2;i<argc;i++){
				printf("Removing :: '%s'\n",argv[i]);
				remove(argv[i]);
			}
		}
		else if(*p=='i'){
			for(int i=2;i<argc;i++){
				char s[10];
				printf("Confirm Removing the file (y/n) ::");
				scanf("%s",s);
				if(strcmp(s,"y")==0){
					remove(argv[i]);
				}
			}
		}
		else{
			printf("No such option\n");
		}
	}
	else{
		for(int i=1;i<argc;i++){
			remove(argv[i]);
		}
	}
	if(argc==2){
		remove(argv[1]);
	}
return 0;
}
