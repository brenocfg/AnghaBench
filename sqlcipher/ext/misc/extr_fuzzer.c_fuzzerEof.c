#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
struct TYPE_2__ {scalar_t__ rLimit; } ;
typedef  TYPE_1__ fuzzer_cursor ;
typedef  scalar_t__ fuzzer_cost ;

/* Variables and functions */

__attribute__((used)) static int fuzzerEof(sqlite3_vtab_cursor *cur){
  fuzzer_cursor *pCur = (fuzzer_cursor*)cur;
  return pCur->rLimit<=(fuzzer_cost)0;
}