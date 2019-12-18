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
typedef  scalar_t__ uLongf ;
typedef  scalar_t__ uLong ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  Bytef ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_malloc (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3_result_blob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_int (int /*<<< orphan*/ *) ; 
 scalar_t__ uncompress (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/  const*,scalar_t__) ; 

__attribute__((used)) static void sqlarUncompressFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  uLong nData;
  uLongf sz;

  assert( argc==2 );
  sz = sqlite3_value_int(argv[1]);

  if( sz<=0 || sz==(nData = sqlite3_value_bytes(argv[0])) ){
    sqlite3_result_value(context, argv[0]);
  }else{
    const Bytef *pData= sqlite3_value_blob(argv[0]);
    Bytef *pOut = sqlite3_malloc(sz);
    if( Z_OK!=uncompress(pOut, &sz, pData, nData) ){
      sqlite3_result_error(context, "error in uncompress()", -1);
    }else{
      sqlite3_result_blob(context, pOut, sz, SQLITE_TRANSIENT);
    }
    sqlite3_free(pOut);
  }
}