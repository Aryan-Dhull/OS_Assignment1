#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>
#include<ctype.h>
#include<pthread.h>

void shell_run_pthread(char *command, char *args[10]){
	pthread_t thread_id;
	char *commandWithArgs=malloc(100);
	strcpy(commandWithArgs,command);
	for(int i=1;i<10;i++){
		if(args[i]!=NULL && (strcmp(args[i],"&t")!=0)){
			strcat(commandWithArgs, " ");
			strcat(commandWithArgs, args[i]);
		}
		else{
			break;
		}
	}
	pthread_create(&thread_id, NULL, (void *)system, commandWithArgs);
	pthread_join(thread_id, NULL);
}

void command_cd_func(char* args[],int s){
	if(s>2){
		printf("Invalid Input\n");
	}
	else{
		char cur_path[256];
		if(args[1][0]=='.'){
			getcwd(cur_path,sizeof(cur_path));
			strcat(cur_path,"/");
			strcat(cur_path,args[1]);
			chdir(cur_path);
			printf("Directory Changed To :: %s\n",getcwd(cur_path,sizeof(cur_path)));
		}
		else if(args[1][0]=='~'){
			args[1]++;
			char *cur_path=getenv("HOME");
			strcat(cur_path,args[1]);
			chdir(cur_path);
			printf("Directory Changed to :: %s\n",getcwd(cur_path,sizeof(cur_path)));
		}
		else{
			int i=chdir(args[1]);
			if(i==-1){
				printf("Invalid Path\n");
			}
			else{
				printf("Directory Changed To :: %s\n",getcwd(args[1],100));
			}
		}
	}
}

void command_echo_func(char* args[],int s){
	if(s<2){printf("\n");}
	else{
		if(args[1][0]=='-'){
			char* p=(char*)(args[1]+1);
			if(*p=='e'){
				for(int i=2;i<s;i++){
					if(args[i][0]=='\\'){
						if(args[i][1]=='c'){
							break;
							exit(0);
						}
						else{
							printf(args[i]);
							printf(" ");
						}
					}
					else{
						printf(args[i]);
						printf(" ");
					}
				}
			}
			else if(*p=='n'){
				for(int i=2;i<s;i++){
					for(int j=0;j<strlen(args[i]);j++){
						if(args[i][j]!='\n'){
							printf("%c",args[i][j]);
						}
					}
					if(i<s-1){
						printf(" ");
					}
				}
			}
		}
		else{
			for(int i=1;i<s;i++){
				printf(args[i]);
				printf(" ");
			}
		}
	}
}

void command_pwd_func(char* args[],int s){
	if(s==1){
		printf("%s\n",getenv("PWD"));
	}
	else if(s==2){
		if(strcmp(args[1],"-L")==0){
			printf("%s\n",getenv("PWD"));
		}
		else if(strcmp(args[1],"-P")==0){
			char str[100];
			printf("%s\n",getcwd(str,100));
		}
		else{
			printf("Invalid Command\n");
		}
	}
	else{
		printf("Invalid Command\n");
	}
}

void command_mkdir_func(char* args[],int s){
	pid_t pfid;
	pfid=fork();
	if(pfid==0){
		printf("Child Process, PID: %d\n",getpid());
		if(s==1){
			printf("Invalid Command");
			exit(0);
		}
		else if(s==2){
			execl("./mkdir",args[0],args[1],NULL);
			exit(0);
		}
		else if(s==3){
			execl("./mkdir",args[0],args[1],args[2],NULL);
			exit(0);
		}
		else{printf("Too many arguments");}
	}
	else if(pfid>0){		
		printf("Parent Process, PID: %d\n",getpid());
		int status;
		wait(&status);
		printf("Child is reaped\n");
	}	
	else{
		printf("Error in forking..\n");
		exit(EXIT_FAILURE);
	}
}


void command_ls_func(char* args[],int s){
	pid_t pfid;
	pfid=fork();
	if(pfid==0){
		printf("Child Process, PID: %d\n",getpid());
		if(s==1){
			execl("./ls",args[0],NULL);
			exit(0);
		}
		else if(s==2){
			execl("./ls",args[0],args[1],NULL);
			exit(0);
		}
		else{printf("Too many arguments");}
	}
	else if(pfid>0){
		printf("Parent Process, PID: %d\n",getpid());
		int status;
		wait(&status);
		printf("Child is reaped\n");
	}
	else{
		printf("Error in forking..\n");
		exit(EXIT_FAILURE);
	}
}


void command_rm_func(char* args[],int s){
	pid_t pfid;
	pfid=fork();	
	if(pfid==0){
		printf("Child Process, PID: %d\n",getpid());
		if(s==1){
			printf("Invalid Command\n");
			exit(0);
		}
		else if(s==2){
			execl("./rm",args[0],args[1],NULL);
			exit(0);
		}
		else{printf("Too many arguments");}
	}
	else if(pfid>0){
		printf("Parent Process, PID: %d\n",getpid());
		int status;
		wait(&status);
		printf("Child is reaped\n");
	}
	else{
		printf("Error in forking..\n");
		exit(EXIT_FAILURE);
	}
}

void command_date_func(char* args[],int s){
	pid_t pfid;
	pfid=fork();	
	if(pfid==0){
		printf("Child Process, PID: %d\n",getpid());
		if(s==1){
			execl("./Date",args[0],NULL);
			exit(0);
		}
		else if(s==2){
			execl("./Date",args[0],args[1],NULL);
			exit(0);
		}
		else{printf("Too many arguments");}
	}
	else if(pfid>0){
		printf("Parent Process, PID: %d\n",getpid());
		int status;
		wait(&status);	
		printf("Child is reaped\n");
	}
	else{
		printf("Error in forking..\n");
		exit(EXIT_FAILURE);	
	}
}

void command_cat_func(char* args[],int s){
	pid_t pfid;
	pfid=fork();
	if(pfid==0){
		printf("Child Process, PID: %d\n",getpid());
		if(s==1){
			printf("Invalid Command\n");
			exit(0);
		}
		else if(s==2){
			execl("./cat",args[0],args[1],NULL);
			exit(0);
		}
		else if(s==3){
			execl("./cat",args[0],args[1],args[2],NULL);
			exit(0);
		}
		else{printf("Too many arguments");}
	}
	else if(pfid>0){
		printf("Parent Process, PID: %d\n",getpid());
		int status;
		wait(&status);
		printf("Child is reaped\n");
	}
	else{	
		printf("Error in forking..\n");
		exit(EXIT_FAILURE);
	}
}


int main(){
	printf("*********************************************************");
	printf("\n\n");
	printf("\t\tMY SHELL\n\n");
	printf("*********************************************************\n");
	while(1){
		char* commands[100];
		char ts[100];	
		printf(" %s >",getcwd(ts,100));	
		char input[10000];
		int i=0;
		fgets(input,sizeof(input),stdin);
		if((strcmp(input,"\r")==0) || (strcmp(input,"\n")==0)){
			continue;
		}
		if(input[strlen(input)-1]=='\n'){
			input[strlen(input)-1]='\0';
		}
		char* tmp=strtok(input," ");
		int size=0;
		while(tmp!=NULL){
			commands[size++]=tmp;
			tmp=strtok(NULL," ");
		}
		if(strcmp(commands[0],"cd")==0){
			char ts[100];	
			printf("Current Directory is %s\n",getcwd(ts,100));
			command_cd_func(commands,size);
		}
		else if(strcmp(commands[0],"echo")==0){
			command_echo_func(commands,size);
		}
		else if(strcmp(commands[0],"pwd")==0){
			command_pwd_func(commands,size);
		}
		else if((strcmp(commands[0],"rm")==0)){
			if(strcmp(commands[size-1],"&t")==0){
				char* f=malloc(100);
				strcpy(f,"./rm");
				shell_run_pthread(f,commands);
			}
			else{
				command_rm_func(commands,size);
			}
		}
		else if((strcmp(commands[0],"cat")==0)){
			if(strcmp(commands[size-1],"&t")==0){
				char* f=malloc(100);
				strcpy(f,"./cat");
				shell_run_pthread(f,commands);
			}
			else{
				command_cat_func(commands,size);
			}
		}
		else if((strcmp(commands[0],"date")==0)){
			if(strcmp(commands[size-1],"&t")==0){
				char* f=malloc(100);
				strcpy(f,"./Date");
				shell_run_pthread(f,commands);
			}
			else{
				command_date_func(commands,size);
			}
		}
		else if((strcmp(commands[0],"mkdir")==0)){
			if(strcmp(commands[size-1],"&t")==0){
				char* f=malloc(100);
				strcpy(f,"./mkdir");
				shell_run_pthread(f,commands);
			}
			else{
				command_mkdir_func(commands,size);
			}
		}
		else if((strcmp(commands[0],"ls")==0)){
			if(strcmp(commands[size-1],"&t")==0){
				char* f=malloc(100);
				strcpy(f,"./ls");
				shell_run_pthread(f,commands);
			}
			else{
				command_ls_func(commands,size);
			}
		}	
		else if(strcmp(commands[0],"quit")==0){
			printf("Quitting..\n");
			exit(0);
		}
		else{
			printf("Invalid Input");
		}
	}
return 0;
}
