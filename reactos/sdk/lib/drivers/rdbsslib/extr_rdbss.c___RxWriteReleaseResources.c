#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_8__ {int /*<<< orphan*/  ResourceThreadId; } ;
struct TYPE_9__ {TYPE_1__ LowIoContext; scalar_t__ FcbPagingIoResourceAcquired; scalar_t__ FcbResourceAcquired; } ;
typedef  TYPE_2__* PRX_CONTEXT ;
typedef  int /*<<< orphan*/  PCSTR ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PAGED_CODE () ; 
 int /*<<< orphan*/  RxCaptureFcb ; 
 int /*<<< orphan*/  RxReleaseFcb (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RxReleaseFcbForThread (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RxReleasePagingIoResource (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RxReleasePagingIoResourceForThread (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * capFcb ; 

VOID
__RxWriteReleaseResources(
    PRX_CONTEXT RxContext,
    BOOLEAN ResourceOwnerSet,
    ULONG LineNumber,
    PCSTR FileName,
    ULONG SerialNumber)
{
    RxCaptureFcb;

    PAGED_CODE();

    ASSERT(RxContext != NULL);
    ASSERT(capFcb != NULL);

    /* If FCB resource was acquired, release it */
    if (RxContext->FcbResourceAcquired)
    {
        /* Taking care of owner */
        if (ResourceOwnerSet)
        {
            RxReleaseFcbForThread(RxContext, capFcb, RxContext->LowIoContext.ResourceThreadId);
        }
        else
        {
            RxReleaseFcb(RxContext, capFcb);
        }

        RxContext->FcbResourceAcquired = FALSE;
    }

    /* If FCB paging resource was acquired, release it */
    if (RxContext->FcbPagingIoResourceAcquired)
    {
        /* Taking care of owner */
        if (ResourceOwnerSet)
        {
            RxReleasePagingIoResourceForThread(RxContext, capFcb, RxContext->LowIoContext.ResourceThreadId);
        }
        else
        {
            RxReleasePagingIoResource(RxContext, capFcb);
        }

        /* No need to release boolean here, RxReleasePagingIoResource() takes care of it */
    }
}