#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_3__ {int* p; size_t n; } ;
typedef  TYPE_1__ Fts5Buffer ;

/* Variables and functions */
 scalar_t__ sqlite3Fts5PutVarint (int*,int) ; 

void sqlite3Fts5PoslistSafeAppend(
  Fts5Buffer *pBuf, 
  i64 *piPrev, 
  i64 iPos
){
  static const i64 colmask = ((i64)(0x7FFFFFFF)) << 32;
  if( (iPos & colmask) != (*piPrev & colmask) ){
    pBuf->p[pBuf->n++] = 1;
    pBuf->n += sqlite3Fts5PutVarint(&pBuf->p[pBuf->n], (iPos>>32));
    *piPrev = (iPos & colmask);
  }
  pBuf->n += sqlite3Fts5PutVarint(&pBuf->p[pBuf->n], (iPos-*piPrev)+2);
  *piPrev = iPos;
}