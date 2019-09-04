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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int UCHAR ;
struct TYPE_2__ {int /*<<< orphan*/ * (* AllocateLsaHeap ) (int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/ * PSID ;

/* Variables and functions */
 TYPE_1__ DispatchTable ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RtlLengthRequiredSid (int) ; 
 int* RtlSubAuthorityCountSid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RtlSubAuthoritySid (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
PSID
AppendRidToSid(PSID SrcSid,
               ULONG Rid)
{
    PSID DstSid = NULL;
    UCHAR RidCount;

    RidCount = *RtlSubAuthorityCountSid(SrcSid);
    if (RidCount >= 8)
        return NULL;

    DstSid = DispatchTable.AllocateLsaHeap(RtlLengthRequiredSid(RidCount + 1));
    if (DstSid == NULL)
        return NULL;

    RtlCopyMemory(DstSid,
                  SrcSid,
                  RtlLengthRequiredSid(RidCount));

    *RtlSubAuthorityCountSid(DstSid) = RidCount + 1;
    *RtlSubAuthoritySid(DstSid, RidCount) = Rid;

    return DstSid;
}