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
struct TYPE_2__ {size_t Constants; } ;
struct ID3DXConstantTableImpl {int /*<<< orphan*/ * ctab; int /*<<< orphan*/ * constants; TYPE_1__ desc; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_constant (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_constant_table(struct ID3DXConstantTableImpl *table)
{
    if (table->constants)
    {
        UINT i;

        for (i = 0; i < table->desc.Constants; ++i)
        {
            free_constant(&table->constants[i]);
        }
        HeapFree(GetProcessHeap(), 0, table->constants);
    }
    HeapFree(GetProcessHeap(), 0, table->ctab);
}