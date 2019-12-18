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
struct TYPE_2__ {scalar_t__ iValue; scalar_t__ mxValue; } ;
typedef  TYPE_1__ wholenumber_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;

/* Variables and functions */

__attribute__((used)) static int wholenumberEof(sqlite3_vtab_cursor *cur){
  wholenumber_cursor *pCur = (wholenumber_cursor*)cur;
  return pCur->iValue>pCur->mxValue || pCur->iValue==0;
}