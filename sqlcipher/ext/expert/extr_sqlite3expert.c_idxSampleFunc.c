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
struct IdxSampleCtx {double nRow; int nRet; int target; int iTarget; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_randomness (int,void*) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idxSampleFunc(
  sqlite3_context *pCtx,
  int argc,
  sqlite3_value **argv
){
  struct IdxSampleCtx *p = (struct IdxSampleCtx*)sqlite3_user_data(pCtx);
  int bRet;

  (void)argv;
  assert( argc==0 );
  if( p->nRow==0.0 ){
    bRet = 1;
  }else{
    bRet = (p->nRet / p->nRow) <= p->target;
    if( bRet==0 ){
      unsigned short rnd;
      sqlite3_randomness(2, (void*)&rnd);
      bRet = ((int)rnd % 100) <= p->iTarget;
    }
  }

  sqlite3_result_int(pCtx, bRet);
  p->nRow += 1.0;
  p->nRet += (double)bRet;
}