#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  value; int /*<<< orphan*/  id; int /*<<< orphan*/  schema; } ;
struct TYPE_4__ {size_t item_count; TYPE_3__* items; } ;
typedef  TYPE_1__ MetadataHandler ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  PropVariantClear (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void MetadataHandler_FreeItems(MetadataHandler *This)
{
    DWORD i;

    for (i=0; i<This->item_count; i++)
    {
        PropVariantClear(&This->items[i].schema);
        PropVariantClear(&This->items[i].id);
        PropVariantClear(&This->items[i].value);
    }

    HeapFree(GetProcessHeap(), 0, This->items);
}