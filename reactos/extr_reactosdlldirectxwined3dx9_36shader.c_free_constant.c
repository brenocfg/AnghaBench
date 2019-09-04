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
struct TYPE_2__ {int Elements; size_t StructMembers; } ;
struct ctab_constant {struct ctab_constant* constants; TYPE_1__ desc; } ;
typedef  size_t UINT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctab_constant*) ; 

__attribute__((used)) static void free_constant(struct ctab_constant *constant)
{
    if (constant->constants)
    {
        UINT i, count = constant->desc.Elements > 1 ? constant->desc.Elements : constant->desc.StructMembers;

        for (i = 0; i < count; ++i)
        {
            free_constant(&constant->constants[i]);
        }
        HeapFree(GetProcessHeap(), 0, constant->constants);
    }
}