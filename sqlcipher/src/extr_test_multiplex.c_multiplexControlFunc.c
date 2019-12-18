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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int MULTIPLEX_CTRL_ENABLE ; 
 int MULTIPLEX_CTRL_SET_CHUNK_SIZE ; 
 int MULTIPLEX_CTRL_SET_MAX_CHUNKS ; 
 int SQLITE_ERROR ; 
 int SQLITE_NOTFOUND ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 int sqlite3_file_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  sqlite3_result_error_code (int /*<<< orphan*/ *,int) ; 
 int sqlite3_value_int (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void multiplexControlFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int rc = SQLITE_OK;
  sqlite3 *db = sqlite3_context_db_handle(context);
  int op = 0;
  int iVal;

  if( !db || argc!=2 ){ 
    rc = SQLITE_ERROR; 
  }else{
    /* extract params */
    op = sqlite3_value_int(argv[0]);
    iVal = sqlite3_value_int(argv[1]);
    /* map function op to file_control op */
    switch( op ){
      case 1: 
        op = MULTIPLEX_CTRL_ENABLE; 
        break;
      case 2: 
        op = MULTIPLEX_CTRL_SET_CHUNK_SIZE; 
        break;
      case 3: 
        op = MULTIPLEX_CTRL_SET_MAX_CHUNKS; 
        break;
      default:
        rc = SQLITE_NOTFOUND;
        break;
    }
  }
  if( rc==SQLITE_OK ){
    rc = sqlite3_file_control(db, 0, op, &iVal);
  }
  sqlite3_result_error_code(context, rc);
}