#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* family_name; } ;
struct TYPE_6__ {scalar_t__ RefCount; int /*<<< orphan*/  UserLanguage; int /*<<< orphan*/  EnglishUS; int /*<<< orphan*/  Memory; TYPE_3__* Face; } ;
typedef  TYPE_1__* PSHARED_FACE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 int /*<<< orphan*/  ExFreePoolWithTag (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FT_Done_Face (TYPE_3__*) ; 
 int /*<<< orphan*/  IntLockFreeType () ; 
 int /*<<< orphan*/  IntUnLockFreeType () ; 
 int /*<<< orphan*/  RemoveCacheEntries (TYPE_3__*) ; 
 int /*<<< orphan*/  SharedFaceCache_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SharedMem_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_FONT ; 

__attribute__((used)) static void
SharedFace_Release(PSHARED_FACE Ptr)
{
    IntLockFreeType();
    ASSERT(Ptr->RefCount > 0);

    if (Ptr->RefCount <= 0)
        return;

    --Ptr->RefCount;
    if (Ptr->RefCount == 0)
    {
        DPRINT("Releasing SharedFace for %s\n", Ptr->Face->family_name ? Ptr->Face->family_name : "<NULL>");
        RemoveCacheEntries(Ptr->Face);
        FT_Done_Face(Ptr->Face);
        SharedMem_Release(Ptr->Memory);
        SharedFaceCache_Release(&Ptr->EnglishUS);
        SharedFaceCache_Release(&Ptr->UserLanguage);
        ExFreePoolWithTag(Ptr, TAG_FONT);
    }
    IntUnLockFreeType();
}