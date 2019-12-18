#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_5__ {int /*<<< orphan*/  keyType; } ;
typedef  TYPE_2__ lsm1_vtab ;
struct TYPE_4__ {scalar_t__ pVtab; } ;
struct TYPE_6__ {int atEof; scalar_t__ pKey2; int isDesc; int bUnique; int /*<<< orphan*/  pLsmCur; int /*<<< orphan*/  nKey2; TYPE_1__ base; } ;
typedef  TYPE_3__ lsm1_cursor ;

/* Variables and functions */
 int LSM_OK ; 
 int LSM_SEEK_EQ ; 
 int LSM_SEEK_GE ; 
 int LSM_SEEK_LE ; 
 int /*<<< orphan*/  SQLITE_BLOB ; 
 int SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_INTEGER ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsm1KeyFromValue (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int*) ; 
 int /*<<< orphan*/  lsm1PutVarint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lsm_csr_first (int /*<<< orphan*/ ) ; 
 int lsm_csr_seek (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int,int) ; 
 scalar_t__ lsm_csr_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (scalar_t__) ; 
 void* sqlite3_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lsm1Filter(
  sqlite3_vtab_cursor *pVtabCursor, 
  int idxNum, const char *idxStr,
  int argc, sqlite3_value **argv
){
  lsm1_cursor *pCur = (lsm1_cursor *)pVtabCursor;
  lsm1_vtab *pTab = (lsm1_vtab*)(pCur->base.pVtab);
  int rc = LSM_OK;
  int seekType = -1;
  const u8 *pVal = 0;
  int nVal;
  u8 keyType = pTab->keyType;
  u8 aKey1[16];

  pCur->atEof = 1;
  sqlite3_free(pCur->pKey2);
  pCur->pKey2 = 0;
  if( idxNum<99 ){
    lsm1KeyFromValue(keyType, argv[0], aKey1, &pVal, &nVal);
  }
  switch( idxNum ){
    case 0: {   /* key==argv[0] */
      assert( argc==1 );
      seekType = LSM_SEEK_EQ;
      pCur->isDesc = 0;
      pCur->bUnique = 1;
      break;
    }
    case 1: {  /* key>=argv[0] AND key<=argv[1] */
      u8 aKey[12];
      seekType = LSM_SEEK_GE;
      pCur->isDesc = 0;
      pCur->bUnique = 0;
      if( keyType==SQLITE_INTEGER ){
        sqlite3_int64 v = sqlite3_value_int64(argv[1]);
        if( v<0 ) v = 0;
        pCur->nKey2 = lsm1PutVarint64(aKey, (sqlite3_uint64)v);
        pCur->pKey2 = sqlite3_malloc( pCur->nKey2 );
        if( pCur->pKey2==0 ) return SQLITE_NOMEM;
        memcpy(pCur->pKey2, aKey, pCur->nKey2);
      }else{
        pCur->nKey2 = sqlite3_value_bytes(argv[1]);
        pCur->pKey2 = sqlite3_malloc( pCur->nKey2 );
        if( pCur->pKey2==0 ) return SQLITE_NOMEM;
        if( keyType==SQLITE_BLOB ){
          memcpy(pCur->pKey2, sqlite3_value_blob(argv[1]), pCur->nKey2);
        }else{
          memcpy(pCur->pKey2, sqlite3_value_text(argv[1]), pCur->nKey2);
        }
      }
      break;
    }
    case 2: {  /* key>=argv[0] */
      seekType = LSM_SEEK_GE;
      pCur->isDesc = 0;
      pCur->bUnique = 0;
      break;
    }
    case 3: {  /* key<=argv[0] */
      seekType = LSM_SEEK_LE;
      pCur->isDesc = 1;
      pCur->bUnique = 0;
      break;
    }
    default: { /* full table scan */
      pCur->isDesc = 0;
      pCur->bUnique = 0;
      break;
    }
  }
  if( pVal ){
    rc = lsm_csr_seek(pCur->pLsmCur, pVal, nVal, seekType);
  }else{
    rc = lsm_csr_first(pCur->pLsmCur);
  }
  if( rc==LSM_OK && lsm_csr_valid(pCur->pLsmCur)!=0 ){
    pCur->atEof = 0;
  }
  return rc==LSM_OK ? SQLITE_OK : SQLITE_ERROR;
}