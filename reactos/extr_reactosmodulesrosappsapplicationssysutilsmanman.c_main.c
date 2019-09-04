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
 int /*<<< orphan*/  AnalyzeArgv (char*) ; 
 int /*<<< orphan*/  CloseF () ; 
 int /*<<< orphan*/  NORMAL ; 
 scalar_t__ OpenFlag ; 
 int /*<<< orphan*/  SetCl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Usage () ; 

int
main(int argc, char *argv[])
{

  switch(argc)
    {
     case 1:  Usage(); break;
     case 2:  AnalyzeArgv(argv[1]);break;
     default: Usage();break;
    }

   if(OpenFlag)CloseF();
   SetCl(NORMAL);
   return 0;
}