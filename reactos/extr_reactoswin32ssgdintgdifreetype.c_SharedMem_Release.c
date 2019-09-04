#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ RefCount; struct TYPE_7__* Buffer; scalar_t__ IsMapping; } ;
typedef  TYPE_1__* PSHARED_MEM ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT_FREETYPE_LOCK_HELD () ; 
 int /*<<< orphan*/  DPRINT (char*,TYPE_1__*,scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmUnmapViewInSystemSpace (TYPE_1__*) ; 
 int /*<<< orphan*/  TAG_FONT ; 

__attribute__((used)) static void SharedMem_Release(PSHARED_MEM Ptr)
{
    ASSERT_FREETYPE_LOCK_HELD();
    ASSERT(Ptr->RefCount > 0);

    if (Ptr->RefCount <= 0)
        return;

    --Ptr->RefCount;
    if (Ptr->RefCount == 0)
    {
        DPRINT("Releasing SharedMem for %p (%i, %p)\n", Ptr->Buffer, Ptr->IsMapping, Ptr);
        if (Ptr->IsMapping)
            MmUnmapViewInSystemSpace(Ptr->Buffer);
        else
            ExFreePoolWithTag(Ptr->Buffer, TAG_FONT);
        ExFreePoolWithTag(Ptr, TAG_FONT);
    }
}