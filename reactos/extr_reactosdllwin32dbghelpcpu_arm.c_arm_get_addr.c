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
typedef  enum cpu_addr { ____Placeholder_cpu_addr } cpu_addr ;
struct TYPE_3__ {int Mode; scalar_t__ Segment; } ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  TYPE_1__ ADDRESS64 ;

/* Variables and functions */
 int AddrModeFlat ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static BOOL arm_get_addr(HANDLE hThread, const CONTEXT* ctx,
                         enum cpu_addr ca, ADDRESS64* addr)
{
    addr->Mode    = AddrModeFlat;
    addr->Segment = 0; /* don't need segment */
    switch (ca)
    {
#ifdef __arm__
    case cpu_addr_pc:    addr->Offset = ctx->Pc; return TRUE;
    case cpu_addr_stack: addr->Offset = ctx->Sp; return TRUE;
#ifdef __REACTOS__
    case cpu_addr_frame: addr->Offset = ctx->R11; return TRUE;
#else
    case cpu_addr_frame: addr->Offset = ctx->Fp; return TRUE;
#endif
#endif
    default: addr->Mode = -1;
        return FALSE;
    }
}