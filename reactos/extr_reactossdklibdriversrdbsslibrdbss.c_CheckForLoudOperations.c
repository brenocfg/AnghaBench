#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  UNICODE_NULL ;
struct TYPE_6__ {scalar_t__ Length; int /*<<< orphan*/  Buffer; } ;
struct TYPE_9__ {TYPE_1__ PrivateAlreadyPrefixedName; } ;
struct TYPE_7__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_8__ {TYPE_2__ LowIoContext; } ;
typedef  TYPE_3__* PRX_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  Add2Ptr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  LOWIO_CONTEXT_FLAG_LOUDOPS ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int RtlCompareMemory (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RxCaptureFcb ; 
 scalar_t__ RxLoudLowIoOpsEnabled ; 
 int /*<<< orphan*/  SetFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* capFcb ; 

VOID
CheckForLoudOperations(
    PRX_CONTEXT RxContext)
{
    RxCaptureFcb;

    PAGED_CODE();

#define ALLSCR_LENGTH (sizeof(L"all.scr") - sizeof(UNICODE_NULL))

    /* Are loud operations enabled? */
    if (RxLoudLowIoOpsEnabled)
    {
        /* If so, the operation will be loud only if filename ends with all.scr */
        if (RtlCompareMemory(Add2Ptr(capFcb->PrivateAlreadyPrefixedName.Buffer,
                             (capFcb->PrivateAlreadyPrefixedName.Length - ALLSCR_LENGTH)),
                             L"all.scr", ALLSCR_LENGTH) == ALLSCR_LENGTH)
        {
            SetFlag(RxContext->LowIoContext.Flags, LOWIO_CONTEXT_FLAG_LOUDOPS);
        }
    }
#undef ALLSCR_LENGTH
}