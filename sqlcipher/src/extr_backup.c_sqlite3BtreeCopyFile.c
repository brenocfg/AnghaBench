#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {scalar_t__ pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_20__ {int iNext; int rc; TYPE_4__* pDest; TYPE_4__* pSrc; int /*<<< orphan*/  pSrcDb; } ;
typedef  TYPE_3__ sqlite3_backup ;
typedef  int i64 ;
typedef  int /*<<< orphan*/  b ;
struct TYPE_21__ {TYPE_1__* pBt; int /*<<< orphan*/  db; } ;
struct TYPE_18__ {int /*<<< orphan*/  btsFlags; } ;
typedef  TYPE_4__ Btree ;

/* Variables and functions */
 int /*<<< orphan*/  BTS_PAGESIZE_FIXED ; 
 int /*<<< orphan*/  SQLITE_FCNTL_OVERWRITE ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_4__*) ; 
 int sqlite3BtreeGetPageSize (TYPE_4__*) ; 
 scalar_t__ sqlite3BtreeIsInTrans (TYPE_4__*) ; 
 scalar_t__ sqlite3BtreeLastPage (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_4__*) ; 
 int /*<<< orphan*/  sqlite3BtreePager (TYPE_4__*) ; 
 int sqlite3OsFileControl (TYPE_2__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3PagerAlignReserve (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerClearCache (int /*<<< orphan*/ ) ; 
 TYPE_2__* sqlite3PagerFile (int /*<<< orphan*/ ) ; 
 int sqlite3_backup_finish (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3_backup_step (TYPE_3__*,int) ; 

int sqlite3BtreeCopyFile(Btree *pTo, Btree *pFrom){
  int rc;
  sqlite3_file *pFd;              /* File descriptor for database pTo */
  sqlite3_backup b;
  sqlite3BtreeEnter(pTo);
  sqlite3BtreeEnter(pFrom);

  assert( sqlite3BtreeIsInTrans(pTo) );
  pFd = sqlite3PagerFile(sqlite3BtreePager(pTo));
  if( pFd->pMethods ){
    i64 nByte = sqlite3BtreeGetPageSize(pFrom)*(i64)sqlite3BtreeLastPage(pFrom);
    rc = sqlite3OsFileControl(pFd, SQLITE_FCNTL_OVERWRITE, &nByte);
    if( rc==SQLITE_NOTFOUND ) rc = SQLITE_OK;
    if( rc ) goto copy_finished;
  }

  /* Set up an sqlite3_backup object. sqlite3_backup.pDestDb must be set
  ** to 0. This is used by the implementations of sqlite3_backup_step()
  ** and sqlite3_backup_finish() to detect that they are being called
  ** from this function, not directly by the user.
  */
  memset(&b, 0, sizeof(b));
  b.pSrcDb = pFrom->db;
  b.pSrc = pFrom;
  b.pDest = pTo;
  b.iNext = 1;

#ifdef SQLITE_HAS_CODEC
  sqlite3PagerAlignReserve(sqlite3BtreePager(pTo), sqlite3BtreePager(pFrom));
#endif

  /* 0x7FFFFFFF is the hard limit for the number of pages in a database
  ** file. By passing this as the number of pages to copy to
  ** sqlite3_backup_step(), we can guarantee that the copy finishes 
  ** within a single call (unless an error occurs). The assert() statement
  ** checks this assumption - (p->rc) should be set to either SQLITE_DONE 
  ** or an error code.  */
  sqlite3_backup_step(&b, 0x7FFFFFFF);
  assert( b.rc!=SQLITE_OK );

  rc = sqlite3_backup_finish(&b);
  if( rc==SQLITE_OK ){
    pTo->pBt->btsFlags &= ~BTS_PAGESIZE_FIXED;
  }else{
    sqlite3PagerClearCache(sqlite3BtreePager(b.pDest));
  }

  assert( sqlite3BtreeIsInTrans(pTo)==0 );
copy_finished:
  sqlite3BtreeLeave(pFrom);
  sqlite3BtreeLeave(pTo);
  return rc;
}