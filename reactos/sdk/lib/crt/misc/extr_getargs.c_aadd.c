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
 int SIZE ; 
 int __argc ; 
 char** __argv ; 
 char** malloc (int) ; 
 char** realloc (char**,int) ; 

int aadd(char* name)
{
   char** _new;
   if ((__argc % SIZE) == 0)
   {
      if (__argv == NULL)
         _new = malloc(sizeof(char*) * (1 + SIZE));
      else
         _new = realloc(__argv, sizeof(char*) * (__argc + 1 + SIZE));
      if (_new == NULL)
         return -1;
      __argv = _new;
   }
   __argv[__argc++] = name;
   __argv[__argc] = NULL;
   return 0;
}