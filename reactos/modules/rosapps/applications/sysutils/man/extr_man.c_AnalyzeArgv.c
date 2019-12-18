#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int MAXLINE ; 
 scalar_t__ OpenF (char*) ; 
 int /*<<< orphan*/  Usage () ; 
 int _countof (char**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* strcat (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

int
AnalyzeArgv(char *argument)
{
    int element;
    char HelpFlag=0;
    char *keys[]={"--help","/h","/?","-h"};
    char *sections[]={".1",".2",".3",".4",".5",".6",".7",".8",".9"};
    char *filename=(char*)malloc(sizeof(char)*MAXLINE);

    strcpy(filename,argument); //save argument value

    for(element=0;element<_countof(keys);element++)
    {
     if(!strcmp(keys[element],argument))
     {
      Usage();
      HelpFlag=1;
     }
    }

   element = 0;

   if(!HelpFlag)
   {

   if(OpenF(filename))
   {
    while(element<_countof(sections)&&OpenF(strcat(filename,sections[element])))
    {
     strcpy(filename,argument);
     element++;
    }

    if(element>=_countof(sections)) printf("No manual for %s\n",argument);
   }

   }

    return element;
}