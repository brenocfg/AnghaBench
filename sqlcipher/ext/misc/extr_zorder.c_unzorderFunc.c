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
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_result_int64 (int /*<<< orphan*/ *,int) ; 
 int sqlite3_value_int64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unzorderFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  sqlite3_int64 z, n, i, x;
  int j, k;
  z = sqlite3_value_int64(argv[0]);
  n = sqlite3_value_int64(argv[1]);
  i = sqlite3_value_int64(argv[2]);
  x = 0;
  for(k=0, j=i; j<63; j+=n, k++){
    x |= ((z>>j)&1)<<k;
  }
  sqlite3_result_int64(context, x);
}