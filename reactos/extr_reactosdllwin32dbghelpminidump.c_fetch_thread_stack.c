#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tib ;
struct dump_context {int /*<<< orphan*/  hProcess; } ;
typedef  scalar_t__ ULONG_PTR ;
struct TYPE_13__ {scalar_t__ word_size; scalar_t__ (* get_addr ) (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_4__*) ;} ;
struct TYPE_12__ {scalar_t__ Mode; scalar_t__ Offset; } ;
struct TYPE_9__ {scalar_t__ DataSize; } ;
struct TYPE_11__ {scalar_t__ StartOfMemoryRange; TYPE_1__ Memory; } ;
struct TYPE_10__ {scalar_t__ StackBase; scalar_t__ StackLimit; } ;
typedef  TYPE_2__ NT_TIB ;
typedef  TYPE_3__ MINIDUMP_MEMORY_DESCRIPTOR ;
typedef  int /*<<< orphan*/  CONTEXT ;
typedef  TYPE_4__ ADDRESS64 ;

/* Variables and functions */
 scalar_t__ AddrModeFlat ; 
 scalar_t__ ReadProcessMemory (int /*<<< orphan*/ ,void const*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_addr_stack ; 
 TYPE_7__* dbghelp_current_cpu ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void fetch_thread_stack(struct dump_context* dc, const void* teb_addr,
                               const CONTEXT* ctx, MINIDUMP_MEMORY_DESCRIPTOR* mmd)
{
    NT_TIB      tib;
    ADDRESS64   addr;

    if (ReadProcessMemory(dc->hProcess, teb_addr, &tib, sizeof(tib), NULL) &&
        dbghelp_current_cpu &&
        dbghelp_current_cpu->get_addr(NULL /* FIXME */, ctx, cpu_addr_stack, &addr) && addr.Mode == AddrModeFlat)
    {
        if (addr.Offset)
        {
            addr.Offset -= dbghelp_current_cpu->word_size;
            /* make sure stack pointer is within the established range of the stack.  It could have
               been clobbered by whatever caused the original exception. */
            if (addr.Offset < (ULONG_PTR)tib.StackLimit || addr.Offset > (ULONG_PTR)tib.StackBase)
                mmd->StartOfMemoryRange = (ULONG_PTR)tib.StackLimit;

            else
                mmd->StartOfMemoryRange = addr.Offset;
        }
        else
            mmd->StartOfMemoryRange = (ULONG_PTR)tib.StackLimit;
        mmd->Memory.DataSize = (ULONG_PTR)tib.StackBase - mmd->StartOfMemoryRange;
    }
}