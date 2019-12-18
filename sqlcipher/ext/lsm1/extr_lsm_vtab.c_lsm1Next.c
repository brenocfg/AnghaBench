#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {int atEof; scalar_t__ isDesc; scalar_t__ nKey2; scalar_t__ zData; scalar_t__ pKey2; int /*<<< orphan*/  pLsmCur; scalar_t__ bUnique; } ;
typedef  TYPE_1__ lsm1_cursor ;

/* Variables and functions */
 int LSM_OK ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsm_csr_key (int /*<<< orphan*/ ,void const**,int*) ; 
 int lsm_csr_next (int /*<<< orphan*/ ) ; 
 int lsm_csr_prev (int /*<<< orphan*/ ) ; 
 scalar_t__ lsm_csr_valid (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/  const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int lsm1Next(sqlite3_vtab_cursor *cur){
  lsm1_cursor *pCur = (lsm1_cursor*)cur;
  int rc = LSM_OK;
  if( pCur->bUnique ){
    pCur->atEof = 1;
  }else{
    if( pCur->isDesc ){
      rc = lsm_csr_prev(pCur->pLsmCur);
    }else{
      rc = lsm_csr_next(pCur->pLsmCur);
    }
    if( rc==LSM_OK && lsm_csr_valid(pCur->pLsmCur)==0 ){
      pCur->atEof = 1;
    }
    if( pCur->pKey2 && pCur->atEof==0 ){
      const u8 *pVal;
      u32 nVal;
      assert( pCur->isDesc==0 );
      rc = lsm_csr_key(pCur->pLsmCur, (const void**)&pVal, (int*)&nVal);
      if( rc==LSM_OK ){
        u32 len = pCur->nKey2;
        int c;
        if( len>nVal ) len = nVal;
        c = memcmp(pVal, pCur->pKey2, len);
        if( c==0 ) c = nVal - pCur->nKey2;
        if( c>0 ) pCur->atEof = 1;
      }
    }
    pCur->zData = 0;
  }
  return rc==LSM_OK ? SQLITE_OK : SQLITE_ERROR;
}