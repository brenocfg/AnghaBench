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
struct NtileCtx {scalar_t__ nTotal; scalar_t__ nParam; int /*<<< orphan*/  iRow; } ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 void* sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ntileStepFunc(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **apArg
){
  struct NtileCtx *p;
  assert( nArg==2 ); UNUSED_PARAMETER(nArg);
  p = (struct NtileCtx*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p ){
    if( p->nTotal==0 ){
      p->nParam = sqlite3_value_int64(apArg[0]);
      p->nTotal = sqlite3_value_int64(apArg[1]);
      if( p->nParam<=0 ){
        sqlite3_result_error(
            pCtx, "argument of ntile must be a positive integer", -1
        );
      }
    }
    p->iRow++;
  }
}