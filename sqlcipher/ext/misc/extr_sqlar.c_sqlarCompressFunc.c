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
typedef  int /*<<< orphan*/  uLongf ;
typedef  int /*<<< orphan*/  uLong ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 scalar_t__ SQLITE_BLOB ; 
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ compress (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compressBound (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlarCompressFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  assert( argc==1 );
  if( sqlite3_value_type(argv[0])==SQLITE_BLOB ){
    const Bytef *pData = sqlite3_value_blob(argv[0]);
    uLong nData = sqlite3_value_bytes(argv[0]);
    uLongf nOut = compressBound(nData);
    Bytef *pOut;

    pOut = (Bytef*)sqlite3_malloc(nOut);
    if( pOut==0 ){
      sqlite3_result_error_nomem(context);
      return;
    }else{
      if( Z_OK!=compress(pOut, &nOut, pData, nData) ){
        sqlite3_result_error(context, "error in compress()", -1);
      }else if( nOut<nData ){
        sqlite3_result_blob(context, pOut, nOut, SQLITE_TRANSIENT);
      }else{
        sqlite3_result_value(context, argv[0]);
      }
      sqlite3_free(pOut);
    }
  }else{
    sqlite3_result_value(context, argv[0]);
  }
}