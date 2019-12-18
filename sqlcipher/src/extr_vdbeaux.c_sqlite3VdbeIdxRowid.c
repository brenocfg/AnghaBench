#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int i64 ;
struct TYPE_7__ {int i; } ;
struct TYPE_8__ {int n; scalar_t__ szMalloc; TYPE_1__ u; int /*<<< orphan*/ * z; } ;
typedef  TYPE_2__ Mem ;
typedef  int /*<<< orphan*/  BtCursor ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_MAX_U32 ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  getVarint32 (int /*<<< orphan*/ *,int) ; 
 int sqlite3BtreeCursorIsValid (int /*<<< orphan*/ *) ; 
 int sqlite3BtreePayloadSize (int /*<<< orphan*/ *) ; 
 int* sqlite3SmallTypeSizes ; 
 int sqlite3VdbeMemFromBtree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeMemInit (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3VdbeMemRelease (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3VdbeSerialGet (int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  testcase (int) ; 
 scalar_t__ unlikely (int) ; 

int sqlite3VdbeIdxRowid(sqlite3 *db, BtCursor *pCur, i64 *rowid){
  i64 nCellKey = 0;
  int rc;
  u32 szHdr;        /* Size of the header */
  u32 typeRowid;    /* Serial type of the rowid */
  u32 lenRowid;     /* Size of the rowid */
  Mem m, v;

  /* Get the size of the index entry.  Only indices entries of less
  ** than 2GiB are support - anything large must be database corruption.
  ** Any corruption is detected in sqlite3BtreeParseCellPtr(), though, so
  ** this code can safely assume that nCellKey is 32-bits  
  */
  assert( sqlite3BtreeCursorIsValid(pCur) );
  nCellKey = sqlite3BtreePayloadSize(pCur);
  assert( (nCellKey & SQLITE_MAX_U32)==(u64)nCellKey );

  /* Read in the complete content of the index entry */
  sqlite3VdbeMemInit(&m, db, 0);
  rc = sqlite3VdbeMemFromBtree(pCur, 0, (u32)nCellKey, &m);
  if( rc ){
    return rc;
  }

  /* The index entry must begin with a header size */
  (void)getVarint32((u8*)m.z, szHdr);
  testcase( szHdr==3 );
  testcase( szHdr==m.n );
  testcase( szHdr>0x7fffffff );
  assert( m.n>=0 );
  if( unlikely(szHdr<3 || szHdr>(unsigned)m.n) ){
    goto idx_rowid_corruption;
  }

  /* The last field of the index should be an integer - the ROWID.
  ** Verify that the last entry really is an integer. */
  (void)getVarint32((u8*)&m.z[szHdr-1], typeRowid);
  testcase( typeRowid==1 );
  testcase( typeRowid==2 );
  testcase( typeRowid==3 );
  testcase( typeRowid==4 );
  testcase( typeRowid==5 );
  testcase( typeRowid==6 );
  testcase( typeRowid==8 );
  testcase( typeRowid==9 );
  if( unlikely(typeRowid<1 || typeRowid>9 || typeRowid==7) ){
    goto idx_rowid_corruption;
  }
  lenRowid = sqlite3SmallTypeSizes[typeRowid];
  testcase( (u32)m.n==szHdr+lenRowid );
  if( unlikely((u32)m.n<szHdr+lenRowid) ){
    goto idx_rowid_corruption;
  }

  /* Fetch the integer off the end of the index record */
  sqlite3VdbeSerialGet((u8*)&m.z[m.n-lenRowid], typeRowid, &v);
  *rowid = v.u.i;
  sqlite3VdbeMemRelease(&m);
  return SQLITE_OK;

  /* Jump here if database corruption is detected after m has been
  ** allocated.  Free the m object and return SQLITE_CORRUPT. */
idx_rowid_corruption:
  testcase( m.szMalloc!=0 );
  sqlite3VdbeMemRelease(&m);
  return SQLITE_CORRUPT_BKPT;
}