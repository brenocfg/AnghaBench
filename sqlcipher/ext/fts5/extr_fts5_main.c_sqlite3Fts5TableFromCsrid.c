#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_4__ {scalar_t__ pVtab; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  Fts5Table ;
typedef  int /*<<< orphan*/  Fts5Global ;
typedef  TYPE_2__ Fts5Cursor ;

/* Variables and functions */
 TYPE_2__* fts5CursorFromCsrid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

Fts5Table *sqlite3Fts5TableFromCsrid(
  Fts5Global *pGlobal,            /* FTS5 global context for db handle */
  i64 iCsrId                      /* Id of cursor to find */
){
  Fts5Cursor *pCsr;
  pCsr = fts5CursorFromCsrid(pGlobal, iCsrId);
  if( pCsr ){
    return (Fts5Table*)pCsr->base.pVtab;
  }
  return 0;
}