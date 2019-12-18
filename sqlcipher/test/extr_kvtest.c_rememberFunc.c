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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 scalar_t__ SQLITE_INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rememberFunc(
  sqlite3_context *pCtx,
  int argc,
  sqlite3_value **argv
){
  sqlite3_int64 v;
  sqlite3_int64 ptr;
  assert( argc==2 );
  v = sqlite3_value_int64(argv[0]);
  ptr = sqlite3_value_int64(argv[1]);
  *(sqlite3_int64*)SQLITE_INT_TO_PTR(ptr) = v;
  sqlite3_result_int64(pCtx, v);
}