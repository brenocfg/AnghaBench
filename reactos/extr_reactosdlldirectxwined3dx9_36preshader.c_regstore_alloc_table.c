#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct d3dx_regstore {int /*<<< orphan*/ * tables; int /*<<< orphan*/ * table_sizes; } ;
struct TYPE_2__ {unsigned int component_size; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  D3D_OK ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 int /*<<< orphan*/  HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int get_offset_reg (unsigned int,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_info ; 

__attribute__((used)) static HRESULT regstore_alloc_table(struct d3dx_regstore *rs, unsigned int table)
{
    unsigned int size;

    size = get_offset_reg(table, rs->table_sizes[table]) * table_info[table].component_size;
    if (size)
    {
        rs->tables[table] = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
        if (!rs->tables[table])
            return E_OUTOFMEMORY;
    }
    return D3D_OK;
}