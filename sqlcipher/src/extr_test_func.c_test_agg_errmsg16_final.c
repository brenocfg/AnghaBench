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
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  sqlite3_aggregate_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sqlite3_context_db_handle (int /*<<< orphan*/ *) ; 
 void* sqlite3_errmsg16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_result_text16 (int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_agg_errmsg16_final(sqlite3_context *ctx){
#ifndef SQLITE_OMIT_UTF16
  const void *z;
  sqlite3 * db = sqlite3_context_db_handle(ctx);
  sqlite3_aggregate_context(ctx, 2048);
  z = sqlite3_errmsg16(db);
  sqlite3_result_text16(ctx, z, -1, SQLITE_TRANSIENT);
#endif
}