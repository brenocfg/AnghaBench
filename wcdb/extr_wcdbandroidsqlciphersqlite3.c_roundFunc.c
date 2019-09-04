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
typedef  scalar_t__ sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int LARGEST_INT64 ; 
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3AtoF (char*,double*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Strlen30 (char*) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int,double) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 double sqlite3_value_double (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void roundFunc(sqlite3_context *context, int argc, sqlite3_value **argv){
  int n = 0;
  double r;
  char *zBuf;
  assert( argc==1 || argc==2 );
  if( argc==2 ){
    if( SQLITE_NULL==sqlite3_value_type(argv[1]) ) return;
    n = sqlite3_value_int(argv[1]);
    if( n>30 ) n = 30;
    if( n<0 ) n = 0;
  }
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
  r = sqlite3_value_double(argv[0]);
  /* If Y==0 and X will fit in a 64-bit int,
  ** handle the rounding directly,
  ** otherwise use printf.
  */
  if( n==0 && r>=0 && r<LARGEST_INT64-1 ){
    r = (double)((sqlite_int64)(r+0.5));
  }else if( n==0 && r<0 && (-r)<LARGEST_INT64-1 ){
    r = -(double)((sqlite_int64)((-r)+0.5));
  }else{
    zBuf = sqlite3_mprintf("%.*f",n,r);
    if( zBuf==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }
    sqlite3AtoF(zBuf, &r, sqlite3Strlen30(zBuf), SQLITE_UTF8);
    sqlite3_free(zBuf);
  }
  sqlite3_result_double(context, r);
}