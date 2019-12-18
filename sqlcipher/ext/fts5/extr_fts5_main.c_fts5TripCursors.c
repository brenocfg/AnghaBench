#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_8__ {int /*<<< orphan*/ * pVtab; } ;
struct TYPE_10__ {scalar_t__ ePlan; TYPE_2__ base; struct TYPE_10__* pNext; } ;
struct TYPE_9__ {TYPE_1__* pGlobal; } ;
struct TYPE_7__ {TYPE_4__* pCsr; } ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;

/* Variables and functions */
 int /*<<< orphan*/  CsrFlagSet (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTS5CSR_REQUIRE_RESEEK ; 
 scalar_t__ FTS5_PLAN_MATCH ; 

__attribute__((used)) static void fts5TripCursors(Fts5FullTable *pTab){
  Fts5Cursor *pCsr;
  for(pCsr=pTab->pGlobal->pCsr; pCsr; pCsr=pCsr->pNext){
    if( pCsr->ePlan==FTS5_PLAN_MATCH
     && pCsr->base.pVtab==(sqlite3_vtab*)pTab 
    ){
      CsrFlagSet(pCsr, FTS5CSR_REQUIRE_RESEEK);
    }
  }
}