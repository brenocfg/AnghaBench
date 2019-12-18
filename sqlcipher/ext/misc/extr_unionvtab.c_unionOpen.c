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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ UnionCsr ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ unionMalloc (int*,int) ; 

__attribute__((used)) static int unionOpen(sqlite3_vtab *p, sqlite3_vtab_cursor **ppCursor){
  UnionCsr *pCsr;
  int rc = SQLITE_OK;
  (void)p;  /* Suppress harmless warning */
  pCsr = (UnionCsr*)unionMalloc(&rc, sizeof(UnionCsr));
  *ppCursor = &pCsr->base;
  return rc;
}