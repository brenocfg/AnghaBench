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
struct TYPE_3__ {int mxPgno; scalar_t__ eState; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_OPEN ; 
 int /*<<< orphan*/  assert (int) ; 

int sqlite3PagerMaxPageCount(Pager *pPager, int mxPage){
  if( mxPage>0 ){
    pPager->mxPgno = mxPage;
  }
  assert( pPager->eState!=PAGER_OPEN );      /* Called only by OP_MaxPgcnt */
  /* assert( pPager->mxPgno>=pPager->dbSize ); */
  /* OP_MaxPgcnt ensures that the parameter passed to this function is not
  ** less than the total number of valid pages in the database. But this
  ** may be less than Pager.dbSize, and so the assert() above is not valid */
  return pPager->mxPgno;
}