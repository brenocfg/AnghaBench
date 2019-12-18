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
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 scalar_t__ sqlite3StrICmp (char const*,char*) ; 
 int /*<<< orphan*/  sqlite3_result_double (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_double (int /*<<< orphan*/ *) ; 
 size_t sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void testFunc(sqlite3_context *context, int argc, sqlite3_value **argv){
  while( argc>=2 ){
    const char *zArg0 = (char*)sqlite3_value_text(argv[0]);
    if( zArg0 ){
      if( 0==sqlite3StrICmp(zArg0, "int") ){
        sqlite3_result_int(context, sqlite3_value_int(argv[1]));
      }else if( sqlite3StrICmp(zArg0,"int64")==0 ){
        sqlite3_result_int64(context, sqlite3_value_int64(argv[1]));
      }else if( sqlite3StrICmp(zArg0,"string")==0 ){
        sqlite3_result_text(context, (char*)sqlite3_value_text(argv[1]), -1,
            SQLITE_TRANSIENT);
      }else if( sqlite3StrICmp(zArg0,"double")==0 ){
        sqlite3_result_double(context, sqlite3_value_double(argv[1]));
      }else if( sqlite3StrICmp(zArg0,"null")==0 ){
        sqlite3_result_null(context);
      }else if( sqlite3StrICmp(zArg0,"value")==0 ){
        sqlite3_result_value(context, argv[sqlite3_value_int(argv[1])]);
      }else{
        goto error_out;
      }
    }else{
      goto error_out;
    }
    argc -= 2;
    argv += 2;
  }
  return;

error_out:
  sqlite3_result_error(context,"first argument should be one of: "
      "int int64 string double null value", -1);
}