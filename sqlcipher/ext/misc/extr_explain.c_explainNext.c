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
struct TYPE_2__ {scalar_t__ rc; int /*<<< orphan*/  pExplain; } ;
typedef  TYPE_1__ explain_cursor ;

/* Variables and functions */
 scalar_t__ SQLITE_DONE ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int explainNext(sqlite3_vtab_cursor *cur){
  explain_cursor *pCur = (explain_cursor*)cur;
  pCur->rc = sqlite3_step(pCur->pExplain);
  if( pCur->rc!=SQLITE_DONE && pCur->rc!=SQLITE_ROW ) return pCur->rc;
  return SQLITE_OK;
}