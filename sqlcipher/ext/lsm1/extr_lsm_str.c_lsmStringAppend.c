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
struct TYPE_4__ {scalar_t__ n; scalar_t__ z; scalar_t__ nAlloc; } ;
typedef  TYPE_1__ LsmString ;

/* Variables and functions */
 int lsmStringExtend (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

int lsmStringAppend(LsmString *pStr, const char *z, int N){
  int rc;
  if( N<0 ) N = (int)strlen(z);
  rc = lsmStringExtend(pStr, N+1);
  if( pStr->nAlloc ){
    memcpy(pStr->z+pStr->n, z, N+1);
    pStr->n += N;
  }
  return rc;
}