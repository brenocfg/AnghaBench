#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  spellfix1_vtab ;
struct TYPE_4__ {int /*<<< orphan*/  base; int /*<<< orphan*/ * pVTab; } ;
typedef  TYPE_1__ spellfix1_cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* sqlite3_malloc64 (int) ; 

__attribute__((used)) static int spellfix1Open(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  spellfix1_vtab *p = (spellfix1_vtab*)pVTab;
  spellfix1_cursor *pCur;
  pCur = sqlite3_malloc64( sizeof(*pCur) );
  if( pCur==0 ) return SQLITE_NOMEM;
  memset(pCur, 0, sizeof(*pCur));
  pCur->pVTab = p;
  *ppCursor = &pCur->base;
  return SQLITE_OK;
}