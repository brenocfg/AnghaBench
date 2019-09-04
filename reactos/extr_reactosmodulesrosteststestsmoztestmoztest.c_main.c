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
 int SocketTest () ; 
 int VirtualTest () ; 
 int /*<<< orphan*/  _stricmp (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main(int argc, char **argv)
{
   if (argc != 2)
   {
      printf("Usage: %s test_name\n\n", argv[0]);
      printf("Valid test names:\n");
      printf("\tsocket\n");
      printf("\tvirtual\n");
      return 0;
   }

   if (!_stricmp(argv[1], "socket"))
      return SocketTest();
   if (!_stricmp(argv[1], "virtual"))
      return VirtualTest();

   printf("Test '%s' doesn't exist\n", argv[1]);

   return 0;
}