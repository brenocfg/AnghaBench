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
typedef  int /*<<< orphan*/  sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (char*,char const*,int) ; 
 scalar_t__ rbuIsVacuum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_user_data (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void rbuTargetNameFunc(
  sqlite3_context *pCtx,
  int argc,
  sqlite3_value **argv
){
  sqlite3rbu *p = sqlite3_user_data(pCtx);
  const char *zIn;
  assert( argc==1 || argc==2 );

  zIn = (const char*)sqlite3_value_text(argv[0]);
  if( zIn ){
    if( rbuIsVacuum(p) ){
      if( argc==1 || 0==sqlite3_value_int(argv[1]) ){
        sqlite3_result_text(pCtx, zIn, -1, SQLITE_STATIC);
      }
    }else{
      if( strlen(zIn)>4 && memcmp("data", zIn, 4)==0 ){
        int i;
        for(i=4; zIn[i]>='0' && zIn[i]<='9'; i++);
        if( zIn[i]=='_' && zIn[i+1] ){
          sqlite3_result_text(pCtx, &zIn[i+1], -1, SQLITE_STATIC);
        }
      }
    }
  }
}