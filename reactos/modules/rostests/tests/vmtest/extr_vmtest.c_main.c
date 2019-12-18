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
typedef  int /*<<< orphan*/ * PVOID ;
typedef  int /*<<< orphan*/ * PBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RESERVE ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 void* VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main()
{
   PBYTE Base;
   PVOID Ret;

   Base = VirtualAlloc(NULL,
		       1048576,
		       MEM_RESERVE,
		       PAGE_READWRITE);
   if (Base == NULL)
     {
	printf("VirtualAlloc failed 1\n");
     }

   Ret = VirtualAlloc(Base + 4096,
		      4096,
		      MEM_COMMIT,
		      PAGE_READWRITE);
   if (Ret == NULL)
     {
	printf("VirtualAlloc failed 2\n");
     }

   Ret = VirtualAlloc(Base + 12288,
		      4096,
		      MEM_COMMIT,
		      PAGE_READWRITE);
   if (Ret == NULL)
     {
	printf("VirtualAlloc failed 3\n");
     }

   Ret = VirtualAlloc(Base + 20480,
		      4096,
		      MEM_COMMIT,
		      PAGE_READWRITE);
   if (Ret == NULL)
     {
	printf("VirtualAlloc failed 4\n");
     }

   Ret = VirtualAlloc(Base + 4096,
		      28672,
		      MEM_RESERVE,
		      PAGE_READWRITE);
   if (Ret == NULL)
     {
	printf("VirtualAlloc failed 5\n");
     }
   return 0;
}