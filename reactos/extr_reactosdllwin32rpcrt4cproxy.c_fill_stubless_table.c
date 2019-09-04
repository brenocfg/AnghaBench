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
struct thunk {int dummy; } ;
typedef  void const* LPVOID ;
typedef  int /*<<< orphan*/  IUnknownVtbl ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
 int MAX_BLOCKS ; 
 int /*<<< orphan*/  TRUE ; 
 struct thunk* allocate_block (int) ; 
 struct thunk** method_blocks ; 

BOOL fill_stubless_table( IUnknownVtbl *vtbl, DWORD num )
{
    const void **entry = (const void **)(vtbl + 1);
    DWORD i, j;

    if (num - 3 > BLOCK_SIZE * MAX_BLOCKS)
    {
        FIXME( "%u methods not supported\n", num );
        return FALSE;
    }
    for (i = 0; i < (num - 3 + BLOCK_SIZE - 1) / BLOCK_SIZE; i++)
    {
        const struct thunk *block = method_blocks[i];
        if (!block && !(block = allocate_block( i ))) return FALSE;
        for (j = 0; j < BLOCK_SIZE && j < num - 3 - i * BLOCK_SIZE; j++, entry++)
            if (*entry == (LPVOID)-1) *entry = &block[j];
    }
    return TRUE;
}