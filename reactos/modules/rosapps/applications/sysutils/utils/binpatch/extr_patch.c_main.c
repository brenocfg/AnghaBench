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
 int applyPatch () ; 
 int createPatch () ; 
 int m_argc ; 
 char** m_argv ; 
 int /*<<< orphan*/  printUsage () ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(
   int argc,
   char *argv[])
{
   m_argc = argc;
   m_argv = argv;

   if (argc >= 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0))
   {
      printUsage();
      return 0;
   }
   else if (argc >= 2 && argv[1][0] == '-')
   {
      if (strcmp(argv[1], "-c") == 0)
      {
         return createPatch();
      }
      else if (strcmp(argv[1], "-d") == 0)
      {
         return applyPatch();
      }
      else
      {
         printf("Unknown option: %s\n"
                "Use -h for help.\n",
                argv[1]);
         return -1;
      }
   }

   return applyPatch();
}