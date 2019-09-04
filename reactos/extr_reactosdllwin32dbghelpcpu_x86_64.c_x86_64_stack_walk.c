#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct cpu_stack_walk {int /*<<< orphan*/  is32; } ;
struct TYPE_9__ {scalar_t__ Mode; scalar_t__ Offset; } ;
struct TYPE_8__ {scalar_t__ Rsp; scalar_t__ Rip; scalar_t__ Rbp; } ;
struct TYPE_7__ {int /*<<< orphan*/  FuncTableEntry; TYPE_5__ AddrStack; TYPE_5__ AddrReturn; TYPE_5__ AddrFrame; TYPE_5__ AddrPC; void* Virtual; void* Far; int /*<<< orphan*/  Params; int /*<<< orphan*/  AddrBStore; } ;
typedef  TYPE_1__* LPSTACKFRAME64 ;
typedef  TYPE_2__ CONTEXT ;
typedef  void* BOOL ;

/* Variables and functions */
 scalar_t__ AddrModeFlat ; 
 void* FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 void* TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int curr_count ; 
 scalar_t__ curr_mode ; 
 int /*<<< orphan*/  fetch_next_frame (struct cpu_stack_walk*,TYPE_2__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stm_64bit ; 
 scalar_t__ stm_done ; 
 scalar_t__ stm_start ; 
 int /*<<< orphan*/  wine_dbgstr_addr (TYPE_5__*) ; 
 int /*<<< orphan*/  wine_dbgstr_longlong (int) ; 

__attribute__((used)) static BOOL x86_64_stack_walk(struct cpu_stack_walk* csw, LPSTACKFRAME64 frame, CONTEXT* context)
{
    unsigned    deltapc = curr_count <= 1 ? 0 : 1;

    /* sanity check */
    if (curr_mode >= stm_done) return FALSE;
    assert(!csw->is32);

    TRACE("Enter: PC=%s Frame=%s Return=%s Stack=%s Mode=%s Count=%s\n",
          wine_dbgstr_addr(&frame->AddrPC),
          wine_dbgstr_addr(&frame->AddrFrame),
          wine_dbgstr_addr(&frame->AddrReturn),
          wine_dbgstr_addr(&frame->AddrStack),
          curr_mode == stm_start ? "start" : "64bit",
          wine_dbgstr_longlong(curr_count));

    if (curr_mode == stm_start)
    {
        if ((frame->AddrPC.Mode == AddrModeFlat) &&
            (frame->AddrFrame.Mode != AddrModeFlat))
        {
            WARN("Bad AddrPC.Mode / AddrFrame.Mode combination\n");
            goto done_err;
        }

        /* Init done */
        curr_mode = stm_64bit;
        frame->AddrReturn.Mode = frame->AddrStack.Mode = AddrModeFlat;
        /* don't set up AddrStack on first call. Either the caller has set it up, or
         * we will get it in the next frame
         */
        memset(&frame->AddrBStore, 0, sizeof(frame->AddrBStore));
    }
    else
    {
        if (context->Rsp != frame->AddrStack.Offset) FIXME("inconsistent Stack Pointer\n");
        if (context->Rip != frame->AddrPC.Offset) FIXME("inconsistent Instruction Pointer\n");

        if (frame->AddrReturn.Offset == 0) goto done_err;
        if (!fetch_next_frame(csw, context, frame->AddrPC.Offset - deltapc, &frame->FuncTableEntry))
            goto done_err;
        deltapc = 1;
    }

    memset(&frame->Params, 0, sizeof(frame->Params));

    /* set frame information */
    frame->AddrStack.Offset = context->Rsp;
    frame->AddrFrame.Offset = context->Rbp;
    frame->AddrPC.Offset = context->Rip;
    if (1)
    {
        CONTEXT         newctx = *context;

        if (!fetch_next_frame(csw, &newctx, frame->AddrPC.Offset - deltapc, NULL))
            goto done_err;
        frame->AddrReturn.Mode = AddrModeFlat;
        frame->AddrReturn.Offset = newctx.Rip;
    }

    frame->Far = TRUE;
    frame->Virtual = TRUE;
    curr_count++;

    TRACE("Leave: PC=%s Frame=%s Return=%s Stack=%s Mode=%s Count=%s FuncTable=%p\n",
          wine_dbgstr_addr(&frame->AddrPC),
          wine_dbgstr_addr(&frame->AddrFrame),
          wine_dbgstr_addr(&frame->AddrReturn),
          wine_dbgstr_addr(&frame->AddrStack),
          curr_mode == stm_start ? "start" : "64bit",
          wine_dbgstr_longlong(curr_count),
          frame->FuncTableEntry);

    return TRUE;
done_err:
    curr_mode = stm_done;
    return FALSE;
}