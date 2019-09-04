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
typedef  scalar_t__ uint64_ ;
typedef  int /*<<< orphan*/  _TCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  _T (char*) ; 
 int /*<<< orphan*/  _tprintf (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ ** slice_names_plural ; 
 int /*<<< orphan*/ ** slice_names_singular ; 
 scalar_t__* ticks_per_slice ; 

void print_uptime
(
 uint64_ tickcount,
 uint64_ prevsliceval,
 _TCHAR * prevsliceunit,
 int curslice
)
{
 uint64_ tick_cur = tickcount / ticks_per_slice[curslice];
 uint64_ tick_residual = tickcount % ticks_per_slice[curslice];

 assert(tick_cur <= (~((uint64_)0)));

 if(tick_residual == 0)
 {
  /* the current slice is the last */

  if(prevsliceval == 0)
  {
   /* the current slice is the only */
   _tprintf
   (
    _T("%u %s"),
    (unsigned)tick_cur,
    (tick_cur == 1 ? slice_names_singular : slice_names_plural)[curslice]
   );
  }
  else
  {
   /* the current slice is the last, and there's a previous slice */
   assert(prevsliceunit);

   /* print the previous and the current slice, and terminate */
   _tprintf
   (
    _T("%u %s %s %u %s"),
    (unsigned)prevsliceval,
    prevsliceunit,
    _T("and"),
    (unsigned)tick_cur,
    (tick_cur == 1 ? slice_names_singular : slice_names_plural)[curslice]
   );
  }
 }
 else if(tick_cur != 0)
 {
  /* the current slice is not the last, and non-zero */

  if(prevsliceval != 0)
  {
   /* there's a previous slice: print it */
   assert(prevsliceunit);
   _tprintf(_T("%u %s, "), (unsigned)prevsliceval, prevsliceunit);
  }

  /* recursion on the next slice size, storing the current slice */
  print_uptime
  (
   tick_residual,
   tick_cur,
   (tick_cur == 1 ? slice_names_singular : slice_names_plural)[curslice],
   curslice + 1
  );
 }
 else
 {
  /*
   the current slice is not the last, and zero: recursion, remembering the
   previous non-zero slice
  */
  print_uptime(tick_residual, prevsliceval, prevsliceunit, curslice + 1);
 }
}