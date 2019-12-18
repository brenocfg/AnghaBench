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
 int /*<<< orphan*/  sqlite3_result_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_isolation(
  sqlite3_context *pCtx, 
  int nArg,
  sqlite3_value **argv
){
#ifndef SQLITE_OMIT_UTF16
  sqlite3_value_text16(argv[0]);
  sqlite3_value_text(argv[0]);
  sqlite3_value_text16(argv[0]);
  sqlite3_value_text(argv[0]);
#endif
  sqlite3_result_value(pCtx, argv[1]);
}