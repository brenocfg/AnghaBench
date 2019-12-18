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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
struct TYPE_2__ {char* zBuf; int nUsed; } ;
typedef  TYPE_1__ JsonString ;

/* Variables and functions */
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  UNUSED_PARAM (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 scalar_t__ sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void jsonGroupInverse(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
){
  int i;
  int inStr = 0;
  char *z;
  JsonString *pStr;
  UNUSED_PARAM(argc);
  UNUSED_PARAM(argv);
  pStr = (JsonString*)sqlite3_aggregate_context(ctx, 0);
#ifdef NEVER
  /* pStr is always non-NULL since jsonArrayStep() or jsonObjectStep() will
  ** always have been called to initalize it */
  if( NEVER(!pStr) ) return;
#endif
  z = pStr->zBuf;
  for(i=1; z[i]!=',' || inStr; i++){
    assert( i<pStr->nUsed );
    if( z[i]=='"' ){
      inStr = !inStr;
    }else if( z[i]=='\\' ){
      i++;
    }
  }
  pStr->nUsed -= i;      
  memmove(&z[1], &z[i+1], (size_t)pStr->nUsed-1);
}