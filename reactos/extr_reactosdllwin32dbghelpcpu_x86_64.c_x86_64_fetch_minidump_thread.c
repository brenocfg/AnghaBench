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
struct dump_context {int dummy; } ;
typedef  int ULONG64 ;
struct TYPE_3__ {int Rip; scalar_t__ ContextFlags; } ;
typedef  TYPE_1__ CONTEXT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 unsigned int ThreadWriteInstructionWindow ; 
 int /*<<< orphan*/  minidump_add_memory_block (struct dump_context*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL x86_64_fetch_minidump_thread(struct dump_context* dc, unsigned index, unsigned flags, const CONTEXT* ctx)
{
    if (ctx->ContextFlags && (flags & ThreadWriteInstructionWindow))
    {
        /* FIXME: crop values across module boundaries, */
#ifdef __x86_64__
        ULONG64 base = ctx->Rip <= 0x80 ? 0 : ctx->Rip - 0x80;
        minidump_add_memory_block(dc, base, ctx->Rip + 0x80 - base, 0);
#endif
    }

    return TRUE;
}