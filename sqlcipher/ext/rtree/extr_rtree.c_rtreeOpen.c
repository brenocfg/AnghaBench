#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_7__ {int /*<<< orphan*/  nCursor; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pVtab; } ;
struct TYPE_6__ {TYPE_1__ base; } ;
typedef  TYPE_2__ RtreeCursor ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int rtreeOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  int rc = SQLITE_NOMEM;
  Rtree *pRtree = (Rtree *)pVTab;
  RtreeCursor *pCsr;

  pCsr = (RtreeCursor *)sqlite3_malloc64(sizeof(RtreeCursor));
  if( pCsr ){
    memset(pCsr, 0, sizeof(RtreeCursor));
    pCsr->base.pVtab = pVTab;
    rc = SQLITE_OK;
    pRtree->nCursor++;
  }
  *ppCursor = (sqlite3_vtab_cursor *)pCsr;

  return rc;
}