#include<stdio.h>
#include<time.h>
#include<sys/stat.h>

int main(int argc,char* argv[]){
	if(argc==1){
		time_t T=time(NULL);
		struct tm tm=*localtime(&T);
		printf("System Date : %02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon+1,tm.tm_year+1900);
		printf("System Time : %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	}
	if(argc>1){
		if(argv[1][0]=='-'){
			char *p=(char*)(argv[1]+1);
			if(*p=='u'){
				time_t tmi;
				struct tm* utcTime;
				time(&tmi);
				utcTime=gmtime(&tmi);
				printf("UTC Date : %02d/%02d/%04d\n", utcTime->tm_mday, utcTime->tm_mon+1,utcTime->tm_year +1900);
				printf("UTC Time : %02d:%02d:%02d\n", (utcTime->tm_hour)%24, utcTime->tm_min, utcTime->tm_sec);
			}
			else if(*p=='r'){
				struct stat filestat;
				stat(argv[2],&filestat);
				printf("File Modify Time :: %s\n",ctime(&filestat.st_mtime));
			}
			else{
				printf("Invalid Command\n");
			}
		}
	}
return 0;
}
