#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {scalar_t__ sizeCalled; scalar_t__ clearCalled; int /*<<< orphan*/  ref; TYPE_1__ IRecordInfo_iface; } ;
typedef  TYPE_2__ IRecordInfoImpl ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RecordInfoVtbl ; 
 int /*<<< orphan*/  START_REF_COUNT ; 

__attribute__((used)) static IRecordInfoImpl *IRecordInfoImpl_Construct(void)
{
  IRecordInfoImpl *rec;

  rec = HeapAlloc(GetProcessHeap(), 0, sizeof(IRecordInfoImpl));
  rec->IRecordInfo_iface.lpVtbl = &RecordInfoVtbl;
  rec->ref = START_REF_COUNT;
  rec->clearCalled = 0;
  rec->sizeCalled = 0;
  return rec;
}