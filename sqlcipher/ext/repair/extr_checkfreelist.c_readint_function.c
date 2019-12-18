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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ get4byte (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void readint_function(
  sqlite3_context *pCtx,
  int nArg,
  sqlite3_value **apArg
){
  const u8 *zBlob;
  int nBlob;
  int iOff = 0;
  u32 iRet = 0;

  if( nArg!=1 && nArg!=2 ){
    sqlite3_result_error(
        pCtx, "wrong number of arguments to function sqlite_readint32()", -1
    );
    return;
  }
  if( nArg==2 ){
    iOff = sqlite3_value_int(apArg[1]);
  }

  zBlob = sqlite3_value_blob(apArg[0]);
  nBlob = sqlite3_value_bytes(apArg[0]);

  if( nBlob>=(iOff+4) ){
    iRet = get4byte(&zBlob[iOff]);
  }

  sqlite3_result_int64(pCtx, (sqlite3_int64)iRet);
}