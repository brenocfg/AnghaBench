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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  aArr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3Fts5UnicodeCatParse (char*,int /*<<< orphan*/ *) ; 
 size_t sqlite3Fts5UnicodeCategory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fts5ExprIsAlnum(
  sqlite3_context *pCtx,          /* Function call context */
  int nArg,                       /* Number of args */
  sqlite3_value **apVal           /* Function arguments */
){
  int iCode;
  u8 aArr[32];
  if( nArg!=1 ){
    sqlite3_result_error(pCtx, 
        "wrong number of arguments to function fts5_isalnum", -1
    );
    return;
  }
  memset(aArr, 0, sizeof(aArr));
  sqlite3Fts5UnicodeCatParse("L*", aArr);
  sqlite3Fts5UnicodeCatParse("N*", aArr);
  sqlite3Fts5UnicodeCatParse("Co", aArr);
  iCode = sqlite3_value_int(apVal[0]);
  sqlite3_result_int(pCtx, aArr[sqlite3Fts5UnicodeCategory((u32)iCode)]);
}