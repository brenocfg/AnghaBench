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
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ memstat_vtab ;
struct TYPE_6__ {int /*<<< orphan*/  base; int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ memstat_cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* sqlite3_malloc (int) ; 

__attribute__((used)) static int memstatOpen(sqlite3_vtab *p, sqlite3_vtab_cursor **ppCursor){
  memstat_cursor *pCur;
  pCur = sqlite3_malloc( sizeof(*pCur) );
  if( pCur==0 ) return SQLITE_NOMEM;
  memset(pCur, 0, sizeof(*pCur));
  pCur->db = ((memstat_vtab*)p)->db;
  *ppCursor = &pCur->base;
  return SQLITE_OK;
}