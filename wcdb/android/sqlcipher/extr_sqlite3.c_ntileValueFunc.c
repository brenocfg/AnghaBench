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
struct NtileCtx {int nParam; int nTotal; int iRow; } ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void ntileValueFunc(sqlite3_context *pCtx){
  struct NtileCtx *p;
  p = (struct NtileCtx*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p && p->nParam>0 ){
    int nSize = (p->nTotal / p->nParam);
    if( nSize==0 ){
      sqlite3_result_int64(pCtx, p->iRow);
    }else{
      i64 nLarge = p->nTotal - p->nParam*nSize;
      i64 iSmall = nLarge*(nSize+1);
      i64 iRow = p->iRow-1;

      assert( (nLarge*(nSize+1) + (p->nParam-nLarge)*nSize)==p->nTotal );

      if( iRow<iSmall ){
        sqlite3_result_int64(pCtx, 1 + iRow/(nSize+1));
      }else{
        sqlite3_result_int64(pCtx, 1 + nLarge + (iRow-iSmall)/nSize);
      }
    }
  }
}