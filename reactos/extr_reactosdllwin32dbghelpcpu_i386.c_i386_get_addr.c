#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  enum cpu_addr { ____Placeholder_cpu_addr } cpu_addr ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  ADDRESS64 ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static BOOL i386_get_addr(HANDLE hThread, const CONTEXT* ctx,
                          enum cpu_addr ca, ADDRESS64* addr)
{
#ifdef __i386__
    switch (ca)
    {
    case cpu_addr_pc:    return i386_build_addr(hThread, ctx, addr, ctx->SegCs, ctx->Eip);
    case cpu_addr_stack: return i386_build_addr(hThread, ctx, addr, ctx->SegSs, ctx->Esp);
    case cpu_addr_frame: return i386_build_addr(hThread, ctx, addr, ctx->SegSs, ctx->Ebp);
    }
#endif
    return FALSE;
}