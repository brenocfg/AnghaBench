#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* family_name; } ;
struct TYPE_6__ {int RefCount; int /*<<< orphan*/  UserLanguage; int /*<<< orphan*/  EnglishUS; int /*<<< orphan*/  Memory; TYPE_2__* Face; } ;
typedef  int /*<<< orphan*/  SHARED_FACE ;
typedef  int /*<<< orphan*/  PSHARED_MEM ;
typedef  TYPE_1__* PSHARED_FACE ;
typedef  TYPE_2__* FT_Face ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,char*) ; 
 TYPE_1__* ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PagedPool ; 
 int /*<<< orphan*/  SharedFaceCache_Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SharedMem_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG_FONT ; 

__attribute__((used)) static PSHARED_FACE
SharedFace_Create(FT_Face Face, PSHARED_MEM Memory)
{
    PSHARED_FACE Ptr;
    Ptr = ExAllocatePoolWithTag(PagedPool, sizeof(SHARED_FACE), TAG_FONT);
    if (Ptr)
    {
        Ptr->Face = Face;
        Ptr->RefCount = 1;
        Ptr->Memory = Memory;
        SharedFaceCache_Init(&Ptr->EnglishUS);
        SharedFaceCache_Init(&Ptr->UserLanguage);

        SharedMem_AddRef(Memory);
        DPRINT("Creating SharedFace for %s\n", Face->family_name ? Face->family_name : "<NULL>");
    }
    return Ptr;
}