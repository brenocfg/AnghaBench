#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ eState; scalar_t__ dbSize; int errCode; scalar_t__ sectorSize; scalar_t__ tempFile; scalar_t__ pageSize; scalar_t__ nSavepoint; } ;
struct TYPE_8__ {int flags; scalar_t__ pgno; TYPE_2__* pPager; } ;
typedef  TYPE_1__ PgHdr ;
typedef  TYPE_2__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_WRITER_LOCKED ; 
 int PGHDR_MMAP ; 
 int PGHDR_WRITEABLE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_2__*) ; 
 int pagerWriteLargeSector (TYPE_1__*) ; 
 int pager_write (TYPE_1__*) ; 
 int subjournalPageIfRequired (TYPE_1__*) ; 

int sqlite3PagerWrite(PgHdr *pPg){
  Pager *pPager = pPg->pPager;
  assert( (pPg->flags & PGHDR_MMAP)==0 );
  assert( pPager->eState>=PAGER_WRITER_LOCKED );
  assert( assert_pager_state(pPager) );
  if( (pPg->flags & PGHDR_WRITEABLE)!=0 && pPager->dbSize>=pPg->pgno ){
    if( pPager->nSavepoint ) return subjournalPageIfRequired(pPg);
    return SQLITE_OK;
  }else if( pPager->errCode ){
    return pPager->errCode;
  }else if( pPager->sectorSize > (u32)pPager->pageSize ){
    assert( pPager->tempFile==0 );
    return pagerWriteLargeSector(pPg);
  }else{
    return pager_write(pPg);
  }
}