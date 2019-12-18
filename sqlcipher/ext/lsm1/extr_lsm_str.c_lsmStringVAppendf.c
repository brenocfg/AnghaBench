#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
struct TYPE_4__ {int nAlloc; int n; char* z; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int /*<<< orphan*/  lsmStringExtend (TYPE_1__*,int) ; 

void lsmStringVAppendf(
  LsmString *pStr, 
  const char *zFormat, 
  va_list ap1,
  va_list ap2
){
#if (!defined(__STDC_VERSION__) || (__STDC_VERSION__<199901L)) && \
    !defined(__APPLE__)
  extern int vsnprintf(char *str, size_t size, const char *format, va_list ap)
    /* Compatibility crutch for C89 compilation mode. sqlite3_vsnprintf()
       does not work identically and causes test failures if used here.
       For the time being we are assuming that the target has vsnprintf(),
       but that is not guaranteed to be the case for pure C89 platforms.
    */;
#endif
  int nWrite;
  int nAvail;

  nAvail = pStr->nAlloc - pStr->n;
  nWrite = vsnprintf(pStr->z + pStr->n, nAvail, zFormat, ap1);

  if( nWrite>=nAvail ){
    lsmStringExtend(pStr, nWrite+1);
    if( pStr->nAlloc==0 ) return;
    nWrite = vsnprintf(pStr->z + pStr->n, nWrite+1, zFormat, ap2);
  }

  pStr->n += nWrite;
  pStr->z[pStr->n] = 0;
}