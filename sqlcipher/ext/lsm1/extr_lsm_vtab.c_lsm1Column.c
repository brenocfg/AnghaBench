#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  v ;
typedef  void u8 ;
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  scalar_t__ sqlite3_uint64 ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_7__ {scalar_t__ keyType; int nVal; } ;
typedef  TYPE_2__ lsm1_vtab ;
struct TYPE_8__ {void* zData; int* aiOfst; int* aiLen; int* aeType; int /*<<< orphan*/  pLsmCur; } ;
typedef  TYPE_3__ lsm1_cursor ;

/* Variables and functions */
 scalar_t__ LSM_OK ; 
#define  SQLITE_BLOB 131 
#define  SQLITE_FLOAT 130 
#define  SQLITE_INTEGER 129 
 int SQLITE_OK ; 
#define  SQLITE_TEXT 128 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ lsm1DecodeValues (TYPE_3__*) ; 
 int /*<<< orphan*/  lsm1GetSignedVarint64 (void const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsm1GetVarint64 (unsigned char const*,int,scalar_t__*) ; 
 scalar_t__ lsm_csr_key (int /*<<< orphan*/ ,void const**,int*) ; 
 scalar_t__ lsm_csr_value (int /*<<< orphan*/ ,void const**,int*) ; 
 int /*<<< orphan*/  memcpy (double*,void const*,int) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsm1Column(
  sqlite3_vtab_cursor *cur,   /* The cursor */
  sqlite3_context *ctx,       /* First argument to sqlite3_result_...() */
  int i                       /* Which column to return */
){
  lsm1_cursor *pCur = (lsm1_cursor*)cur;
  lsm1_vtab *pTab = (lsm1_vtab*)(cur->pVtab);
  if( i==0 ){
    /* The key column */
    const void *pVal;
    int nVal;
    if( lsm_csr_key(pCur->pLsmCur, &pVal, &nVal)==LSM_OK ){
      if( pTab->keyType==SQLITE_BLOB ){
        sqlite3_result_blob(ctx, pVal, nVal, SQLITE_TRANSIENT);
      }else if( pTab->keyType==SQLITE_TEXT ){
        sqlite3_result_text(ctx,(const char*)pVal, nVal, SQLITE_TRANSIENT);
      }else{
        const unsigned char *z = (const unsigned char*)pVal;
        sqlite3_uint64 v1;
        lsm1GetVarint64(z, nVal, &v1);
        sqlite3_result_int64(ctx, (sqlite3_int64)v1);
      }
    }
  }else if( i>pTab->nVal ){
    if( i==pTab->nVal+2 ){  /* lsm1_key */
      const void *pVal;
      int nVal;
      if( lsm_csr_key(pCur->pLsmCur, &pVal, &nVal)==LSM_OK ){
        sqlite3_result_blob(ctx, pVal, nVal, SQLITE_TRANSIENT);
      }
    }else if( i==pTab->nVal+3 ){  /* lsm1_value */
      const void *pVal;
      int nVal;
      if( lsm_csr_value(pCur->pLsmCur, &pVal, &nVal)==LSM_OK ){
        sqlite3_result_blob(ctx, pVal, nVal, SQLITE_TRANSIENT);
      }
    }
  }else if( lsm1DecodeValues(pCur) ){
    /* The i-th value column (where leftmost is 1) */
    const u8 *zData;
    u32 nData;
    i--;
    zData = pCur->zData + pCur->aiOfst[i];
    nData = pCur->aiLen[i];
    switch( pCur->aeType[i] ){
      case 0: {  /* in-line integer */
        sqlite3_result_int(ctx, pCur->aiOfst[i]);
        break;
      }
      case SQLITE_INTEGER: {
        sqlite3_int64 v;
        lsm1GetSignedVarint64(zData, nData, &v);
        sqlite3_result_int64(ctx, v);
        break;
      }
      case SQLITE_FLOAT: {
        double v;
        if( nData==sizeof(v) ){
          memcpy(&v, zData, sizeof(v));
          sqlite3_result_double(ctx, v);
        }
        break;
      }
      case SQLITE_TEXT: {
        sqlite3_result_text(ctx, (const char*)zData, nData, SQLITE_TRANSIENT);
        break;
      }
      case SQLITE_BLOB: {
        sqlite3_result_blob(ctx, zData, nData, SQLITE_TRANSIENT);
        break;
      }
      default: {
         /* A NULL.  Do nothing */
      }
    }
  }
  return SQLITE_OK;
}