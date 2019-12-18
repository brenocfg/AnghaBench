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
typedef  int /*<<< orphan*/ * PUCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_READONLY ; 
 int SIZE ; 
 int /*<<< orphan*/ * VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * x ; 

int main()
{
   int i;
   PUCHAR BaseAddress;

   BaseAddress = VirtualAlloc(NULL,
			      SIZE,
			      MEM_COMMIT,
			      PAGE_READONLY);
   if (BaseAddress == NULL)
     {
	printf("Failed to allocate virtual memory");
	return(1);
     }
   printf("BaseAddress %p\n", BaseAddress);
   for (i = 0; i < (SIZE / 4096); i++)
     {
	printf("%.8x  ", i*4096);
	x[i] = BaseAddress[i*4096];
     }

   return(0);
}