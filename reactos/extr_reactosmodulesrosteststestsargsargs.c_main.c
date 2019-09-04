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
 int /*<<< orphan*/  AllocConsole () ; 
 char* GetCommandLineA () ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 void* InputHandle ; 
 void* OutputHandle ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  debug_printf (char*,...) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

int main(int argc, char* argv[])
{
   int i;

   AllocConsole();
   InputHandle = GetStdHandle(STD_INPUT_HANDLE);
   OutputHandle =  GetStdHandle(STD_OUTPUT_HANDLE);

   printf("GetCommandLineA() %s\n",GetCommandLineA());
   debug_printf("GetCommandLineA() %s\n",GetCommandLineA());
   debug_printf("argc %d\n", argc);
   for (i=0; i<argc; i++)
     {
        debug_printf("Argv[%d]: %x\n",i,argv[i]);
        debug_printf("Argv[%d]: '%s'\n",i,argv[i]);
     }
   return 0;
}