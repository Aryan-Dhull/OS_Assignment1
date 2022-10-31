#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<errno.h>

int main(int argc,char* argv[]){
	int o1=0;
	int o2=0;
	if(argc==2){
		if(argv[1][0]=='-'){
			char *p=(char*)(argv[1]+1);
			if(*p=='a') o1=1;
			else if(*p=='1') o2=1;
			else{printf("Invalid Command\n");}
		}

	}
	struct dirent *d;
	DIR *dh =opendir(".");
	if(!dh){
		if(errno=ENOENT){
			perror("Directory does not exist\n");
		}
		else{
			perror("Unable to read directory\n");
		}
		exit(EXIT_FAILURE);
	}
	char *str[100];
	char temp[100];
	int co=0;
	while((d=readdir(dh))!=NULL){
		str[co]=d->d_name;
		co++;
	}
	for(int i=0;i<co;i++){
		for(int j=i+1;j<co;j++){
			if(strcmp(str[i],str[j])>0){
				strcpy(temp,str[i]);
				strcpy(str[i],str[j]);
				strcpy(str[j],temp);
			}
		}
	}
	for(int i=0;i<co;i++){
		if(!o1 && str[i][0]=='.') continue;
		printf("%s ",str[i]);
		if(o2) printf("\n");
	}
	if(!o2) printf("\n");
return 0;
}
