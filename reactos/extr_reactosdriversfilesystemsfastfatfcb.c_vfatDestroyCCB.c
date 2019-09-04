#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_8__ {int /*<<< orphan*/  CcbLookasideList; } ;
struct TYPE_6__ {scalar_t__ Buffer; } ;
struct TYPE_7__ {TYPE_1__ SearchPattern; } ;
typedef  TYPE_2__* PVFATCCB ;

/* Variables and functions */
 int /*<<< orphan*/  ExFreePoolWithTag (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExFreeToNPagedLookasideList (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  TAG_SEARCH ; 
 TYPE_4__* VfatGlobalData ; 

VOID
vfatDestroyCCB(
    PVFATCCB pCcb)
{
    if (pCcb->SearchPattern.Buffer)
    {
        ExFreePoolWithTag(pCcb->SearchPattern.Buffer, TAG_SEARCH);
    }
    ExFreeToNPagedLookasideList(&VfatGlobalData->CcbLookasideList, pCcb);
}