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

/* Variables and functions */
 int isnan (double) ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3IsNaN(double x){
  int rc;   /* The value return */
#if !SQLITE_HAVE_ISNAN && !HAVE_ISNAN
  /*
  ** Systems that support the isnan() library function should probably
  ** make use of it by compiling with -DSQLITE_HAVE_ISNAN.  But we have
  ** found that many systems do not have a working isnan() function so
  ** this implementation is provided as an alternative.
  **
  ** This NaN test sometimes fails if compiled on GCC with -ffast-math.
  ** On the other hand, the use of -ffast-math comes with the following
  ** warning:
  **
  **      This option [-ffast-math] should never be turned on by any
  **      -O option since it can result in incorrect output for programs
  **      which depend on an exact implementation of IEEE or ISO 
  **      rules/specifications for math functions.
  **
  ** Under MSVC, this NaN test may fail if compiled with a floating-
  ** point precision mode other than /fp:precise.  From the MSDN 
  ** documentation:
  **
  **      The compiler [with /fp:precise] will properly handle comparisons 
  **      involving NaN. For example, x != x evaluates to true if x is NaN 
  **      ...
  */
#ifdef __FAST_MATH__
# error SQLite will not work correctly with the -ffast-math option of GCC.
#endif
  volatile double y = x;
  volatile double z = y;
  rc = (y!=z);
#else  /* if HAVE_ISNAN */
  rc = isnan(x);
#endif /* HAVE_ISNAN */
  testcase( rc );
  return rc;
}