#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <signal.h>
#include <time.h>

#include <sys/stat.h>
#include <unistd.h>

void initLog(void);
char *getDate(void);

static char logFile[128];

int
main(void) {
	signal(SIGINT, SIG_IGN); // Disable SIGINT (Ctrl-C)
	int eof, c;	
	FILE *file;
	char data[2048], input[1024], editCMD[256];
	initLog();
	sprintf(editCMD,"$EDITOR %s", logFile);
	printf("Welcome to stlog\n"
	       "================\n"
	       "Ctrl+D (EOF) to exit\n\n"
	);
	while(eof!=EOF) {
		printf("Options: read/write/edit\n> ");
		eof=scanf(" %[^\n]1023s",input);
		if(!strcmp(input, "read")) {
			printf("\n");
			file=fopen(logFile, "r");
			c=fgetc(file);
			while(c!=EOF) {
				printf("%c", c);
				c=fgetc(file);
			}
			fclose(file);
			printf("\n");
		} else if(!strcmp(input, "write")) {
			file=fopen(logFile, "a");
			printf("\nEnter message: ");
			scanf(" %[^\n]1023s", input);
			sprintf(data,"\n%s - ", getDate());
			strcat(data, input);
			fprintf(file, "%s\n", data);
			fclose(file);
			printf("\n");
		} else if(!strcmp(input, "edit")) {
			system(editCMD);
			printf("\n");
		} else if(eof!=EOF) printf( "Invalid Input\n\n");
		strcpy(input, "");
	}
	printf("\n");
	return EXIT_SUCCESS;
}

/** @brief Locates/Generates logfile
 *
 *  Sets static "logfile" variable.
 *
 *  Generate logfile and/or directory if needed.
 *
 *  @param Void.
 *  @return Void.
 */
void
initLog(void) {
	FILE *file;
	struct stat st={0};
	sprintf(logFile, "%s/.config/stlog/", getenv("HOME"));
	if(stat(logFile, &st)==-1) mkdir(logFile, 0700);
	strcat(logFile, "log.txt");
	if((file=fopen(logFile, "r"))) fclose(file);
	else {
		file=fopen(logFile, "w+");
		fprintf(file, "stlog file\n----------\n\n");
		fclose(file);
	}
}

/** @brief Generate Date/Time
 *
 *  Generates date/time to be used in log entry header.
 *
 *  @param Void.
 *  @return Formatted date/time.
 */
char *
getDate(void) {
	char *weekdays[]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}, *date=malloc(64);
	int map[]={0,3,2,5,0,3,5,1,4,6,2,4};
	time_t t=time(NULL);
	struct tm tm=*localtime(&t);
	int m=tm.tm_mon+1,y=tm.tm_year+1900-(m<3);
	int wd=(y+y/4-y/100+y/400+map[m-1]+tm.tm_mday)%7;
	sprintf(date, "\033[4m""%i/%i/%i (%s) @ %i:%i""\033[0m", tm.tm_mon+1, tm.tm_mday, tm.tm_year+1900, weekdays[wd],tm.tm_hour,tm.tm_min);
	return date;
}