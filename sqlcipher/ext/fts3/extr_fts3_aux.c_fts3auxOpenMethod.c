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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  Fts3auxCursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 

__attribute__((used)) static int fts3auxOpenMethod(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCsr){
  Fts3auxCursor *pCsr;            /* Pointer to cursor object to return */

  UNUSED_PARAMETER(pVTab);

  pCsr = (Fts3auxCursor *)sqlite3_malloc(sizeof(Fts3auxCursor));
  if( !pCsr ) return SQLITE_NOMEM;
  memset(pCsr, 0, sizeof(Fts3auxCursor));

  *ppCsr = (sqlite3_vtab_cursor *)pCsr;
  return SQLITE_OK;
}