#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ Seconds; } ;
struct TYPE_10__ {unsigned int (* Init ) (void**,TYPE_2__*,unsigned int) ;int /*<<< orphan*/  (* Cleanup ) (void*,TYPE_2__*) ;int /*<<< orphan*/  (* PassCleanup ) (void*,TYPE_2__*) ;int /*<<< orphan*/  (* Proc ) (void*,TYPE_2__*,unsigned int) ;} ;
typedef  TYPE_1__* PTEST ;
typedef  TYPE_2__* PPERF_INFO ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ClearWindow (TYPE_2__*) ; 
 scalar_t__ ENOUGH ; 
 double GOAL ; 
 scalar_t__ GetTickCount () ; 
 int /*<<< orphan*/  ProcessMessages () ; 
 scalar_t__ TICK ; 
 unsigned int stub1 (void**,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub2 (void*,TYPE_2__*,unsigned int) ; 
 int /*<<< orphan*/  stub3 (void*,TYPE_2__*) ; 
 int /*<<< orphan*/  stub4 (void*,TYPE_2__*) ; 

__attribute__((used)) static unsigned
CalibrateTest(PTEST Test, PPERF_INFO PerfInfo)
{
#define GOAL    2500   /* Try to get up to 2.5 seconds                 */
#define ENOUGH  2000   /* But settle for 2.0 seconds                   */
#define TICK      10   /* Assume clock not faster than .01 seconds     */

  unsigned Reps, DidReps;        /* Reps desired, reps performed                 */
  unsigned Exponent;
  void *Context;
  DWORD StartTick;
  DWORD Duration;

  /* Attempt to get an idea how long each rep lasts by getting enough
     reps to last more than ENOUGH.  Then scale that up to the number of
     seconds desired.

     If init call to test ever fails, return False and test will be skipped.
  */

  Reps = 1;
  for (;;)
    {
      ClearWindow(PerfInfo);
      DidReps = (*Test->Init)(&Context, PerfInfo, Reps);
      ProcessMessages();
      if (0 == DidReps)
        {
          return 0;
        }
      StartTick = GetTickCount();
      (*Test->Proc)(Context, PerfInfo, Reps);
      Duration = GetTickCount() - StartTick;
      (*Test->PassCleanup) (Context, PerfInfo);
      (*Test->Cleanup)(Context, PerfInfo);
      ProcessMessages();

      if (DidReps != Reps)
        {
          /* The test can't do the number of reps as we asked for.
             Give up */
          return DidReps;
        }
      /* Did we go long enough? */
      if (ENOUGH <= Duration)
        {
          break;
        }

      /* Don't let too short a clock make new reps wildly high */
      if (Duration <= TICK)
        {
          Reps *= 10;
        }
      else
        {
          /* Try to get up to GOAL seconds. */
          Reps = (int)(GOAL * (double) Reps / (double) Duration) + 1;
        }
    }

  Reps = (int) ((double) PerfInfo->Seconds * 1000.0 * (double) Reps / (double) Duration) + 1;

  /* Now round reps up to 1 digit accuracy, so we don't get stupid-looking
     numbers of repetitions. */
  Reps--;
  Exponent = 1;
  while (9 < Reps)
    {
      Reps /= 10;
      Exponent *= 10;
    }
  Reps = (Reps + 1) * Exponent;

  return Reps;
}