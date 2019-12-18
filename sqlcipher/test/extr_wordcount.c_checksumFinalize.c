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

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_TRANSIENT ; 
 int /*<<< orphan*/  finalHash (unsigned int*,char*) ; 
 unsigned int* sqlite3_aggregate_context (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_text (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void checksumFinalize(sqlite3_context *context){
  unsigned int *a;
  char zResult[24];
  a = sqlite3_aggregate_context(context, 0);
  if( a ){
    finalHash(a, zResult);
    sqlite3_result_text(context, zResult, -1, SQLITE_TRANSIENT);
  }
}