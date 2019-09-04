#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pVtab; } ;
typedef  TYPE_1__ sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_6__ {TYPE_1__ base; } ;
typedef  TYPE_2__ PragmaVtabCursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 

__attribute__((used)) static int pragmaVtabOpen(sqlite3_vtab *pVtab, sqlite3_vtab_cursor **ppCursor){
  PragmaVtabCursor *pCsr;
  pCsr = (PragmaVtabCursor*)sqlite3_malloc(sizeof(*pCsr));
  if( pCsr==0 ) return SQLITE_NOMEM;
  memset(pCsr, 0, sizeof(PragmaVtabCursor));
  pCsr->base.pVtab = pVtab;
  *ppCursor = &pCsr->base;
  return SQLITE_OK;
}