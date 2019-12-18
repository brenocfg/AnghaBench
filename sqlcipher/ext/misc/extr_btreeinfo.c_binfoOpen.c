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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_4__ {int /*<<< orphan*/ * pVtab; } ;
struct TYPE_5__ {TYPE_1__ base; } ;
typedef  TYPE_2__ BinfoCursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int binfoOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  BinfoCursor *pCsr;

  pCsr = (BinfoCursor *)sqlite3_malloc64(sizeof(BinfoCursor));
  if( pCsr==0 ){
    return SQLITE_NOMEM;
  }else{
    memset(pCsr, 0, sizeof(BinfoCursor));
    pCsr->base.pVtab = pVTab;
  }

  *ppCursor = (sqlite3_vtab_cursor *)pCsr;
  return SQLITE_OK;
}