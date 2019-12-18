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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 char* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testHexToBin (char const*,char*) ; 

__attribute__((used)) static void testHexToUtf8(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **argv
){
  int n;
  const char *zIn;
  char *zOut;
  assert( nArg==1 );
  n = sqlite3_value_bytes(argv[0]);
  zIn = (const char*)sqlite3_value_text(argv[0]);
  zOut = sqlite3_malloc( n/2 );
  if( zOut==0 ){
    sqlite3_result_error_nomem(pCtx);
  }else{
    testHexToBin(zIn, zOut);
    sqlite3_result_text(pCtx, zOut, n/2, sqlite3_free);
  }
}