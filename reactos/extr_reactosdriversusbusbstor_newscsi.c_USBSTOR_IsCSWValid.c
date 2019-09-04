#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ULONG ;
struct TYPE_5__ {TYPE_1__* csw; } ;
struct TYPE_4__ {scalar_t__ Signature; scalar_t__ Tag; int Status; } ;
typedef  TYPE_2__* PIRP_CONTEXT ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ CSW_SIGNATURE ; 
 int /*<<< orphan*/  DPRINT1 (char*,int,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN
USBSTOR_IsCSWValid(
    PIRP_CONTEXT Context)
{
    //
    // sanity checks
    //
    if (Context->csw->Signature != CSW_SIGNATURE)
    {
        DPRINT1("[USBSTOR] Expected Signature %x but got %x\n", CSW_SIGNATURE, Context->csw->Signature);
        return FALSE;
    }

    if (Context->csw->Tag != (ULONG)Context->csw)
    {
        DPRINT1("[USBSTOR] Expected Tag %x but got %x\n", (ULONG)Context->csw, Context->csw->Tag);
        return FALSE;
    }

    if (Context->csw->Status != 0x00)
    {
        DPRINT1("[USBSTOR] Expected Status 0x00 but got %x\n", Context->csw->Status);
        return FALSE;
    }

    //
    // CSW is valid
    //
    return TRUE;

}