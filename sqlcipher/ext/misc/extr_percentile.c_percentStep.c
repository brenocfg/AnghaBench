#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_3__ {double rPct; int nUsed; int nAlloc; double* a; } ;
typedef  TYPE_1__ Percentile ;

/* Variables and functions */
 int SQLITE_FLOAT ; 
 int SQLITE_INTEGER ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ isInfinity (double) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sameValue (double,double) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_free (double*) ; 
 double* sqlite3_realloc64 (double*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_numeric_type (int /*<<< orphan*/ *) ; 
 int sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void percentStep(sqlite3_context *pCtx, int argc, sqlite3_value **argv){
  Percentile *p;
  double rPct;
  int eType;
  double y;
  assert( argc==2 );

  /* Requirement 3:  P must be a number between 0 and 100 */
  eType = sqlite3_value_numeric_type(argv[1]);
  rPct = sqlite3_value_double(argv[1]);
  if( (eType!=SQLITE_INTEGER && eType!=SQLITE_FLOAT)
   || rPct<0.0 || rPct>100.0 ){
    sqlite3_result_error(pCtx, "2nd argument to percentile() is not "
                         "a number between 0.0 and 100.0", -1);
    return;
  }

  /* Allocate the session context. */
  p = (Percentile*)sqlite3_aggregate_context(pCtx, sizeof(*p));
  if( p==0 ) return;

  /* Remember the P value.  Throw an error if the P value is different
  ** from any prior row, per Requirement (2). */
  if( p->rPct==0.0 ){
    p->rPct = rPct+1.0;
  }else if( !sameValue(p->rPct,rPct+1.0) ){
    sqlite3_result_error(pCtx, "2nd argument to percentile() is not the "
                               "same for all input rows", -1);
    return;
  }

  /* Ignore rows for which Y is NULL */
  eType = sqlite3_value_type(argv[0]);
  if( eType==SQLITE_NULL ) return;

  /* If not NULL, then Y must be numeric.  Otherwise throw an error.
  ** Requirement 4 */
  if( eType!=SQLITE_INTEGER && eType!=SQLITE_FLOAT ){
    sqlite3_result_error(pCtx, "1st argument to percentile() is not "
                               "numeric", -1);
    return;
  }

  /* Throw an error if the Y value is infinity or NaN */
  y = sqlite3_value_double(argv[0]);
  if( isInfinity(y) ){
    sqlite3_result_error(pCtx, "Inf input to percentile()", -1);
    return;
  }

  /* Allocate and store the Y */
  if( p->nUsed>=p->nAlloc ){
    unsigned n = p->nAlloc*2 + 250;
    double *a = sqlite3_realloc64(p->a, sizeof(double)*n);
    if( a==0 ){
      sqlite3_free(p->a);
      memset(p, 0, sizeof(*p));
      sqlite3_result_error_nomem(pCtx);
      return;
    }
    p->nAlloc = n;
    p->a = a;
  }
  p->a[p->nUsed++] = y;
}