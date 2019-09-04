#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  common; int /*<<< orphan*/  mgr_event; } ;
typedef  TYPE_1__ RpcServerProtseq_np ;
typedef  int /*<<< orphan*/  RpcServerProtseq ;

/* Variables and functions */
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RpcServerProtseq *rpcrt4_protseq_np_alloc(void)
{
    RpcServerProtseq_np *ps = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*ps));
    if (ps)
        ps->mgr_event = CreateEventW(NULL, FALSE, FALSE, NULL);
    return &ps->common;
}