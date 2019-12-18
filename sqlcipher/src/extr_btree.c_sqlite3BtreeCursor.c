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
struct KeyInfo {int dummy; } ;
typedef  int /*<<< orphan*/  Btree ;
typedef  int /*<<< orphan*/  BtCursor ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int btreeCursor (int /*<<< orphan*/ *,int,int,struct KeyInfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (int /*<<< orphan*/ *) ; 

int sqlite3BtreeCursor(
  Btree *p,                                   /* The btree */
  int iTable,                                 /* Root page of table to open */
  int wrFlag,                                 /* 1 to write. 0 read-only */
  struct KeyInfo *pKeyInfo,                   /* First arg to xCompare() */
  BtCursor *pCur                              /* Write new cursor here */
){
  int rc;
  if( iTable<1 ){
    rc = SQLITE_CORRUPT_BKPT;
  }else{
    sqlite3BtreeEnter(p);
    rc = btreeCursor(p, iTable, wrFlag, pKeyInfo, pCur);
    sqlite3BtreeLeave(p);
  }
  return rc;
}