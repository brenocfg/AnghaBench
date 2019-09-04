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
typedef  enum cpu_addr { ____Placeholder_cpu_addr } cpu_addr ;
struct TYPE_6__ {int Mode; int /*<<< orphan*/  Offset; int /*<<< orphan*/  Segment; } ;
struct TYPE_5__ {int /*<<< orphan*/  Rbp; int /*<<< orphan*/  SegSs; int /*<<< orphan*/  Rsp; int /*<<< orphan*/  Rip; int /*<<< orphan*/  SegCs; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  TYPE_1__ CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_2__ ADDRESS64 ;

/* Variables and functions */
 int AddrModeFlat ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
#define  cpu_addr_frame 130 
#define  cpu_addr_pc 129 
#define  cpu_addr_stack 128 

__attribute__((used)) static BOOL x86_64_get_addr(HANDLE hThread, const CONTEXT* ctx,
                            enum cpu_addr ca, ADDRESS64* addr)
{
    addr->Mode = AddrModeFlat;
    switch (ca)
    {
#ifdef __x86_64__
    case cpu_addr_pc:    addr->Segment = ctx->SegCs; addr->Offset = ctx->Rip; return TRUE;
    case cpu_addr_stack: addr->Segment = ctx->SegSs; addr->Offset = ctx->Rsp; return TRUE;
    case cpu_addr_frame: addr->Segment = ctx->SegSs; addr->Offset = ctx->Rbp; return TRUE;
#endif
    default: addr->Mode = -1;
        return FALSE;
    }
}