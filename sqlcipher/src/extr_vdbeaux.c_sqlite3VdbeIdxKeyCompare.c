#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int i64 ;
struct TYPE_8__ {int /*<<< orphan*/ * pCursor; } ;
struct TYPE_9__ {scalar_t__ eCurType; TYPE_1__ uc; } ;
typedef  TYPE_2__ VdbeCursor ;
typedef  int /*<<< orphan*/  UnpackedRecord ;
struct TYPE_10__ {int /*<<< orphan*/  z; int /*<<< orphan*/  n; } ;
typedef  TYPE_3__ Mem ;
typedef  int /*<<< orphan*/  BtCursor ;

/* Variables and functions */
 scalar_t__ CURTYPE_BTREE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeCursorIsValid (int /*<<< orphan*/ *) ; 
 int sqlite3BtreePayloadSize (int /*<<< orphan*/ *) ; 
 int sqlite3VdbeMemFromBtree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemInit (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_3__*) ; 
 int sqlite3VdbeRecordCompareWithSkip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int sqlite3VdbeIdxKeyCompare(
  sqlite3 *db,                     /* Database connection */
  VdbeCursor *pC,                  /* The cursor to compare against */
  UnpackedRecord *pUnpacked,       /* Unpacked version of key */
  int *res                         /* Write the comparison result here */
){
  i64 nCellKey = 0;
  int rc;
  BtCursor *pCur;
  Mem m;

  assert( pC->eCurType==CURTYPE_BTREE );
  pCur = pC->uc.pCursor;
  assert( sqlite3BtreeCursorIsValid(pCur) );
  nCellKey = sqlite3BtreePayloadSize(pCur);
  /* nCellKey will always be between 0 and 0xffffffff because of the way
  ** that btreeParseCellPtr() and sqlite3GetVarint32() are implemented */
  if( nCellKey<=0 || nCellKey>0x7fffffff ){
    *res = 0;
    return SQLITE_CORRUPT_BKPT;
  }
  sqlite3VdbeMemInit(&m, db, 0);
  rc = sqlite3VdbeMemFromBtree(pCur, 0, (u32)nCellKey, &m);
  if( rc ){
    return rc;
  }
  *res = sqlite3VdbeRecordCompareWithSkip(m.n, m.z, pUnpacked, 0);
  sqlite3VdbeMemRelease(&m);
  return SQLITE_OK;
}