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
 int /*<<< orphan*/  sqlite3_free ; 
 scalar_t__ sqlite3_get_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* sqlite3_malloc (int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_set_auxdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void counterFunc(
  sqlite3_context *pCtx,   /* Function context */
  int nArg,                /* Number of function arguments */
  sqlite3_value **argv     /* Values for all function arguments */
){
  int *pCounter = (int*)sqlite3_get_auxdata(pCtx, 0);
  if( pCounter==0 ){
    pCounter = sqlite3_malloc( sizeof(*pCounter) );
    if( pCounter==0 ){
      sqlite3_result_error_nomem(pCtx);
      return;
    }
    *pCounter = sqlite3_value_int(argv[0]);
    sqlite3_set_auxdata(pCtx, 0, pCounter, sqlite3_free);
  }else{
    ++*pCounter;
  }
  sqlite3_result_int(pCtx, *pCounter);
}