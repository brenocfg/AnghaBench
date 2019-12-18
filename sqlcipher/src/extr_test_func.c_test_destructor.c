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
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  destructor ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 
 char* testContextMalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_destructor_count_var ; 

__attribute__((used)) static void test_destructor(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **argv
){
  char *zVal;
  int len;
  
  test_destructor_count_var++;
  assert( nArg==1 );
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
  len = sqlite3_value_bytes(argv[0]); 
  zVal = testContextMalloc(pCtx, len+3);
  if( !zVal ){
    return;
  }
  zVal[len+1] = 0;
  zVal[len+2] = 0;
  zVal++;
  memcpy(zVal, sqlite3_value_text(argv[0]), len);
  sqlite3_result_text(pCtx, zVal, -1, destructor);
}