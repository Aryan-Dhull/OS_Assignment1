#include<stdio.h>
#include<stdlib.h>
int main(int argc,char*argv[]){
	if(argc==2){
		FILE *fptr;	
		char c;
		fptr=fopen(argv[1],"r");
		if(fptr==NULL){
			printf("File not found \n");
			exit(0);
		}
		c=fgetc(fptr);
		while(c!=EOF){
			printf("%c",c);
			c=fgetc(fptr);
		}
		fclose(fptr);
	}
	else if(argc>2){
		if(argv[1]==">"){
			FILE *fptr;
			fptr=fopen(argv[2],"w");
			if(fptr==NULL){
				printf("Unable to create file.\n");
				exit(EXIT_FAILURE);
			}
		}
		else if(argv[1][0]=='-'){
			char *p=(char*)(argv[1]+1);
			if(*p=='n'){
				for(int i=2;i<argc;i++){
					FILE *fptr;	
					char c;
					fptr=fopen(argv[i],"r");
					if(fptr==NULL){
						printf("File not found \n");
						exit(0);
					}
					int count=1;
					c=fgetc(fptr);
					while(c!=EOF){
						if(c=='\n'){
							printf("\n");
							printf("\t%d) ",count++);
							c=fgetc(fptr);
						}
						else{
							printf("%c",c);
							c=fgetc(fptr);
						}
					}
					fclose(fptr);
				}
			}
			else{
				printf("Invalid Command\n");
			}
		}
		else{
			for(int i=1;i<argc;i++){
				FILE *fptr;	
				char c;
				fptr=fopen(argv[i],"r");
				if(fptr==NULL){
					printf("File not found \n");
					exit(0);
				}
				c=fgetc(fptr);
				while(c!=EOF){
					printf("%c",c);
					c=fgetc(fptr);
				}
				fclose(fptr);
			}
		}
	}
	return 0;
}
