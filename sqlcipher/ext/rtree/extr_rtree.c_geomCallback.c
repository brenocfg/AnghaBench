#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_5__ {int iSize; int nParam; scalar_t__* apSqlParam; int /*<<< orphan*/ * aParam; int /*<<< orphan*/  cb; } ;
typedef  TYPE_1__ RtreeMatchArg ;
typedef  int /*<<< orphan*/  RtreeGeomCallback ;
typedef  int /*<<< orphan*/  RtreeDValue ;

/* Variables and functions */
 int /*<<< orphan*/  rtreeMatchArgFree (TYPE_1__*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_pointer (int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/  (*) (TYPE_1__*)) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_value_dup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void geomCallback(sqlite3_context *ctx, int nArg, sqlite3_value **aArg){
  RtreeGeomCallback *pGeomCtx = (RtreeGeomCallback *)sqlite3_user_data(ctx);
  RtreeMatchArg *pBlob;
  sqlite3_int64 nBlob;
  int memErr = 0;

  nBlob = sizeof(RtreeMatchArg) + (nArg-1)*sizeof(RtreeDValue)
           + nArg*sizeof(sqlite3_value*);
  pBlob = (RtreeMatchArg *)sqlite3_malloc64(nBlob);
  if( !pBlob ){
    sqlite3_result_error_nomem(ctx);
  }else{
    int i;
    pBlob->iSize = nBlob;
    pBlob->cb = pGeomCtx[0];
    pBlob->apSqlParam = (sqlite3_value**)&pBlob->aParam[nArg];
    pBlob->nParam = nArg;
    for(i=0; i<nArg; i++){
      pBlob->apSqlParam[i] = sqlite3_value_dup(aArg[i]);
      if( pBlob->apSqlParam[i]==0 ) memErr = 1;
#ifdef SQLITE_RTREE_INT_ONLY
      pBlob->aParam[i] = sqlite3_value_int64(aArg[i]);
#else
      pBlob->aParam[i] = sqlite3_value_double(aArg[i]);
#endif
    }
    if( memErr ){
      sqlite3_result_error_nomem(ctx);
      rtreeMatchArgFree(pBlob);
    }else{
      sqlite3_result_pointer(ctx, pBlob, "RtreeMatchArg", rtreeMatchArgFree);
    }
  }
}