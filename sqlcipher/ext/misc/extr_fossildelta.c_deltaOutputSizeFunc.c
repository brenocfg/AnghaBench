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
 int delta_output_size (char const*,int) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deltaOutputSizeFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const char *aDelta;  int nDelta;       /* The input delta (D) */
  int nOut;                              /* Size of output */
  assert( argc==1 );
  if( sqlite3_value_type(argv[0])==SQLITE_NULL ) return;
  nDelta = sqlite3_value_bytes(argv[0]);
  aDelta = (const char*)sqlite3_value_blob(argv[0]);

  /* Figure out the size of the output */
  nOut = delta_output_size(aDelta, nDelta);
  if( nOut<0 ){
    sqlite3_result_error(context, "corrupt fossil delta", -1);
    return;
  }else{
    sqlite3_result_int(context, nOut);
  }
}