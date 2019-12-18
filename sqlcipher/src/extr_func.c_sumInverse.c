#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  scalar_t__ i64 ;
struct TYPE_4__ {scalar_t__ cnt; scalar_t__ approx; int /*<<< orphan*/  rSum; int /*<<< orphan*/  iSum; } ;
typedef  TYPE_1__ SumCtx ;

/* Variables and functions */
 scalar_t__ ALWAYS (TYPE_1__*) ; 
 int SQLITE_INTEGER ; 
 int SQLITE_NULL ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_double (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 int sqlite3_value_numeric_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sumInverse(sqlite3_context *context, int argc, sqlite3_value**argv){
  SumCtx *p;
  int type;
  assert( argc==1 );
  UNUSED_PARAMETER(argc);
  p = sqlite3_aggregate_context(context, sizeof(*p));
  type = sqlite3_value_numeric_type(argv[0]);
  /* p is always non-NULL because sumStep() will have been called first
  ** to initialize it */
  if( ALWAYS(p) && type!=SQLITE_NULL ){
    assert( p->cnt>0 );
    p->cnt--;
    assert( type==SQLITE_INTEGER || p->approx );
    if( type==SQLITE_INTEGER && p->approx==0 ){
      i64 v = sqlite3_value_int64(argv[0]);
      p->rSum -= v;
      p->iSum -= v;
    }else{
      p->rSum -= sqlite3_value_double(argv[0]);
    }
  }
}