#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "check_def.h"

char target_path[256];

int get_path();
int check_reboot();
void set_reboot();


void main()
{
    int retry = 0;
    int first_restart;
    int ret = -1;
    int i;

/*
    first_restart = check_reboot();
    if(first_restart == 0) { // already configured. 
	exit(0);
    }
*/

    for(i=0;i<10;i++) {
	ret = get_path();
	if(ret < 0) {
	    sleep(3);
	} else break;
    }

    if(ret < 0) return; // usb memory is not installed.

    printf("mount point = %s\n", target_path);

    // check config file 
    parse_config(target_path);
    

    // system reboot
//    set_reboot();
}

/*
int check_reboot()
{
    int exist;

    exist = access(REBOOT_CHECK_FILE, F_OK);
    if(exist == 0)  // file is exist.. system is rebooting..
    {
	remove(REBOOT_CHECK_FILE);
    }

    return exist;
}

void set_reboot()
{
    int fd;

    fd = creat(REBOOT_CHECK_FILE, 0644);
    if(fd < 0) {
	printf("%s creation failed.\n", REBOOT_CHECK_FILE);
	return;
    }

    close(fd);

    //reboot system
    system("sync;sync;sync;sudo reboot");
}
*/


int get_path()
{
   FILE *fp;
   char str[256];
   char *mpoint = NULL;
   int ret = -1;

   fp = fopen(MOUNT_INFO, "r");
   if(fp == NULL ) {
        printf("%s open failed..\n", MOUNT_INFO);
        return -1;
   }

   while(fgets(str, 256, fp)) {
	if(strncmp(str,MOUNT_DEVICE, strlen(MOUNT_DEVICE)) == 0) 
	{
	    mpoint = strtok(str, " "); 
	    mpoint = strtok(NULL, " "); // mount point is located on second.
	    strcpy(target_path, mpoint);
	    ret = 0;
	    break;
	}
   }
   fclose(fp);
   return ret;
}

