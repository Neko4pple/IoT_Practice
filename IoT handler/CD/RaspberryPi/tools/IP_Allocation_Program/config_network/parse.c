#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "check_def.h"

#define DHCP	"dhcp"
#define INTERFACE	"interface"

void trim(char *str);
void rtrim(char *str);
void ltrim(char *str);
void parse_line(char *str, char *type, char *arg);
void update_interfaces(char *mnt, char *iface);
int dhcp_checked = -1;
int eth_checked = -1;

int parse_config(char *mpoint)
{
  int ret = -1;
  FILE *fp;
  char path[BUF_SIZ];
  char buf[BUF_SIZ];
  char type[BUF_SIZ];
  char arg[BUF_SIZ];
  char cmd[BUF_SIZ];

  strcpy(path,mpoint);
  strcat(path,"/hanback.cfg");

  fp = fopen(path,"r");
  if(fp == NULL) return ret; // config file is not exist.

  while(fgets(buf,BUF_SIZ,fp) != NULL)
  {
  	if((buf[0] == '#') || (buf[0] == '\r') || (buf[0] == '\0'))
  	{
  	    continue;
  	}

  	trim(buf);
  	if(strlen(buf) < 7) continue;
  	parse_line(buf, type, arg);
  	printf("type =%s, arg=%s\n", type, arg);

  	if(strcmp(type, DHCP) == 0)
  	{
  	  if((strcmp(arg, "yes") == 0) || (strcmp(arg, "YES")==0))
  	  {
  		  dhcp_checked = 1;
      }
      else  // static
      {
        dhcp_checked = -1;
  	  }
  	}
  	if(strcmp(type, INTERFACE) == 0)
  	{
  	  if((strcmp(arg, "eth0") == 0) || (strcmp(arg, "ETH0")==0))
  	  {
  		  eth_checked = 1;
      }
      else  // static
      {
        eth_checked = -1;
  	  }
  	}
  } // while
	update_interfaces(mpoint, arg);
}

void ltrim(char *str)
{
  char *p, *q;

  if(!(*str))
    return;

  p = q = str;

  while(*q && (*q == ' ')) { q++; }

  while(*q)
  {
    *p = *q;
    q++; p++;
  }
  
  *p = '\0';
}

void rtrim(char *str)
{
  char *p;
  if(!(*str))
    return;

  p = str + strlen(str) -1;

  while(*p && (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r'))
  {
    *p = '\0';
    p--;
  }
}

void trim(char *str)
{
  rtrim(str);
  ltrim(str);
}

void parse_line(char *src, char *type, char *arg)
{
  char del[] = "=";
  char *ptr = NULL;

  ptr = (char *)strtok(src, del);
  strncpy(type, ptr, strlen(ptr));
  type[strlen(ptr)] = '\0';
  printf("type = %s, len=%d\n", ptr, strlen(ptr));
  ptr = (char *)strtok(NULL, del);
  strncpy(arg, ptr, strlen(ptr));
  arg[strlen(ptr)] = '\0';
  printf("type = %s, len=%d\n", ptr, strlen(ptr));
}

void update_interfaces(char *mnt, char *iface)
{
  char cmd[BUF_SIZ];
  char FileName[20];

  if(dhcp_checked == 1)
  {
    if(eth_checked == 1)
      sprintf(FileName,"eth_dhcp");
    else
    {
      sprintf(FileName,"wlan_dhcp");
      system("sudo cp /media/usb/wpa_supplicant /etc/wpa_supplicant/wpa_supplicant.conf");
    }
  }
  else
  {
    if(eth_checked == 1)
      sprintf(FileName,"eth_static");
    else
    {
      sprintf(FileName,"wlan_static");
      system("sudo cp /media/usb/wpa_supplicant /etc/wpa_supplicant/wpa_supplicant.conf");
    }
  }

  sprintf(cmd, "sudo cp /media/usb/%s /etc/network/interfaces", FileName);
  system(cmd);

  sprintf(cmd, "sudo cp %s %s", NETWORK_DNS_STATIC, NETWORK_DNS_FILE);
  system(cmd);
  sleep(1);
  system("sudo /etc/init.d/networking restart");
  sprintf(cmd, "sudo ifconfig %s |grep inet | awk '{print $2}' | awk -F: '{print $2}' > /media/usb/ipaddr.txt",iface);
  system(cmd);
}
