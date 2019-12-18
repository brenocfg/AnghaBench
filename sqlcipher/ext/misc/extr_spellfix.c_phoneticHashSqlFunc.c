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
 unsigned char* phoneticHash (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free ; 
 int /*<<< orphan*/  sqlite3_result_error_nomem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_bytes (int /*<<< orphan*/ *) ; 
 unsigned char* sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void phoneticHashSqlFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  const unsigned char *zIn;
  unsigned char *zOut;

  zIn = sqlite3_value_text(argv[0]);
  if( zIn==0 ) return;
  zOut = phoneticHash(zIn, sqlite3_value_bytes(argv[0]));
  if( zOut==0 ){
    sqlite3_result_error_nomem(context);
  }else{
    sqlite3_result_text(context, (char*)zOut, -1, sqlite3_free);
  }
}