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
 scalar_t__ isDbSql (unsigned char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_value_blob (int /*<<< orphan*/ *) ; 
 int sqlite3_value_bytes (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void isDbSqlFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  int n = sqlite3_value_bytes(argv[0]);
  unsigned char *a = (unsigned char*)sqlite3_value_blob(argv[0]);
  sqlite3_result_int(context, a!=0 && n>0 && isDbSql(a,n));
}