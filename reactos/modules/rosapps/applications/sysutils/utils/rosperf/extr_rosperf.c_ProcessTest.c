#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {unsigned int Repeats; } ;
struct TYPE_12__ {unsigned int (* Init ) (void**,TYPE_2__*,unsigned int) ;int /*<<< orphan*/  Label; int /*<<< orphan*/  (* Cleanup ) (void*,TYPE_2__*) ;int /*<<< orphan*/  (* PassCleanup ) (void*,TYPE_2__*) ;int /*<<< orphan*/  (* Proc ) (void*,TYPE_2__*,unsigned int) ;} ;
typedef  TYPE_1__* PTEST ;
typedef  TYPE_2__* PPERF_INFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 unsigned int CalibrateTest (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ClearWindow (TYPE_2__*) ; 
 int /*<<< orphan*/  DisplayStatus (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  LabelWnd ; 
 int /*<<< orphan*/  ProcessMessages () ; 
 int /*<<< orphan*/  ReportTimes (scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 unsigned int stub1 (void**,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (void*,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (void*,TYPE_2__*) ; 

__attribute__((used)) static void
ProcessTest(PTEST Test, PPERF_INFO PerfInfo)
{
  unsigned Reps;
  unsigned Repeat;
  void *Context;
  DWORD StartTick;
  DWORD Time, TotalTime;

  DisplayStatus(LabelWnd, L"Calibrating", Test->Label, 0);
  Reps = CalibrateTest(Test, PerfInfo);
  if (0 == Reps)
    {
      return;
    }

  Reps = Test->Init(&Context, PerfInfo, Reps);
  if (0 == Reps)
    {
      return;
    }
  TotalTime = 0;
  for (Repeat = 0; Repeat < PerfInfo->Repeats; Repeat++)
    {
      DisplayStatus(LabelWnd, L"Testing", Test->Label, Repeat + 1);
      ClearWindow(PerfInfo);
      StartTick = GetTickCount();
      (*Test->Proc)(Context, PerfInfo, Reps);
      Time = GetTickCount() - StartTick;
      ProcessMessages();
      TotalTime += Time;
      ReportTimes(Time, Reps, Test->Label, FALSE);
      (*Test->PassCleanup)(Context, PerfInfo);
      ProcessMessages();
    }
  (*Test->Cleanup)(Context, PerfInfo);
  ReportTimes(TotalTime, Repeat * Reps, Test->Label, TRUE);
  ProcessMessages();
}