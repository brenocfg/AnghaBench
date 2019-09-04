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
typedef  int /*<<< orphan*/  ULONG_PTR ;
struct TYPE_2__ {unsigned int (* map_dwarf_register ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* fetch_context_reg ) (int /*<<< orphan*/ *,unsigned int,unsigned int*) ;} ;
typedef  int /*<<< orphan*/  CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* dbghelp_current_cpu ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stub3 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/ * stub4 (int /*<<< orphan*/ *,unsigned int,unsigned int*) ; 

__attribute__((used)) static void copy_context_reg(CONTEXT *dstcontext, ULONG_PTR dwregdst, CONTEXT* srccontext, ULONG_PTR dwregsrc)
{
    unsigned regdstno = dbghelp_current_cpu->map_dwarf_register(dwregdst, TRUE), szdst;
    unsigned regsrcno = dbghelp_current_cpu->map_dwarf_register(dwregsrc, TRUE), szsrc;
    ULONG_PTR* ptrdst = dbghelp_current_cpu->fetch_context_reg(dstcontext, regdstno, &szdst);
    ULONG_PTR* ptrsrc = dbghelp_current_cpu->fetch_context_reg(srccontext, regsrcno, &szsrc);

    if (szdst != szsrc)
    {
        FIXME("Cannot copy register %lu/%u => %lu/%u because of size mismatch (%u => %u)\n",
              dwregsrc, regsrcno, dwregdst, regdstno, szsrc, szdst);
        return;
    }
    memcpy(ptrdst, ptrsrc, szdst);
}