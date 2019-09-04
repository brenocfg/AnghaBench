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
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 void* HeapReAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static void *grow_array( void *array, unsigned int *count, size_t elem )
{
    void *new_array;
    unsigned int new_count = *count + *count / 2;
    if (new_count < 32) new_count = 32;

    if (array)
	new_array = HeapReAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, array, new_count * elem );
    else
	new_array = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, new_count * elem );

    if (new_array)
        *count = new_count;
    else
        HeapFree( GetProcessHeap(), 0, array );
    return new_array;
}