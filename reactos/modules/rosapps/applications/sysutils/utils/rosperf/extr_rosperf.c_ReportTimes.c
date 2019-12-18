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
typedef  char* LPCWSTR ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 double RoundTo3Digits (double) ; 
 int /*<<< orphan*/  wprintf (char*,int,char*,...) ; 

__attribute__((used)) static void
ReportTimes(DWORD Time, int Reps, LPCWSTR Label, BOOL Average)
{
  double MSecsPerObj, ObjsPerSec;

  if (0 != Time)
    {
      MSecsPerObj = (double) Time / (double) Reps;
      ObjsPerSec = (double) Reps * 1000.0 / (double) Time;

      /* Round obj/sec to 3 significant digits.  Leave msec untouched, to
         allow averaging results from several repetitions. */
      ObjsPerSec =  RoundTo3Digits(ObjsPerSec);

      wprintf(L"%7d %s @ %8.4f msec (%8.1f/sec): %s\n",
              Reps, Average ? L"trep" : L"reps", MSecsPerObj, ObjsPerSec, Label);
    }
  else
    {
      wprintf(L"%6d %sreps @ 0.0 msec (unmeasurably fast): %s\n",
              Reps, Average ? L"t" : L"", Label);
    }

}