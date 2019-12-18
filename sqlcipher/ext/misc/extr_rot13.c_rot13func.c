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
typedef  int /*<<< orphan*/  zTemp ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned char rot13 (unsigned char const) ; 
 int /*<<< orphan*/  sqlite3_free (unsigned char*) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rot13func(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *zIn;
  int nIn;
  unsigned char *zOut;
  unsigned char *zToFree = 0;
  int i;
  unsigned char zTemp[100];
  assert( argc==1 );
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
  zIn = (const unsigned char*)sqlite3_value_text(argv[0]);
  nIn = sqlite3_value_bytes(argv[0]);
  if( nIn<sizeof(zTemp)-1 ){
    zOut = zTemp;
  }else{
    zOut = zToFree = (unsigned char*)sqlite3_malloc64( nIn+1 );
    if( zOut==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }
  }
  for(i=0; i<nIn; i++) zOut[i] = rot13(zIn[i]);
  zOut[i] = 0;
  sqlite3_result_text(context, (char*)zOut, i, SQLITE_TRANSIENT);
  sqlite3_free(zToFree);
}