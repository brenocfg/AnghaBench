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
typedef  int /*<<< orphan*/  ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  PAGE_EXECUTE ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 void* VirtualAlloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualProtect (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* data ; 
 int /*<<< orphan*/  execute (char*,int (*) (int)) ; 
 int /*<<< orphan*/  memcpy (void*,int (*) (int),int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int test (int) ; 

int main(void)
{
    unsigned char stack[100];
    void* heap;
    ULONG protection;

    printf("NoExecute\n");

    execute("Executing within the code segment", test);
    memcpy(data, test, 100);
    execute("Executing within the data segment", (int(*)(int))data);
    memcpy(stack, test, 100);
    execute("Executing on stack segment", (int(*)(int))stack);
    heap = VirtualAlloc(NULL, 100, MEM_COMMIT, PAGE_READWRITE);
    memcpy(heap, test, 100);
    execute("Executing on the heap with protection PAGE_READWRITE", (int(*)(int))heap);
    VirtualProtect(heap, 100, PAGE_EXECUTE, &protection);
    execute("Executing on the heap with protection PAGE_EXECUTE", (int(*)(int))heap);

    return 0;
}