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
 int /*<<< orphan*/  sqlite3Fts5UnicodeFold (int,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5ExprFold(
  sqlite3_context *pCtx,          /* Function call context */
  int nArg,                       /* Number of args */
  sqlite3_value **apVal           /* Function arguments */
){
  if( nArg!=1 && nArg!=2 ){
    sqlite3_result_error(pCtx, 
        "wrong number of arguments to function fts5_fold", -1
    );
  }else{
    int iCode;
    int bRemoveDiacritics = 0;
    iCode = sqlite3_value_int(apVal[0]);
    if( nArg==2 ) bRemoveDiacritics = sqlite3_value_int(apVal[1]);
    sqlite3_result_int(pCtx, sqlite3Fts5UnicodeFold(iCode, bRemoveDiacritics));
  }
}