#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
struct TYPE_3__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ fulltext_cursor ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sqlite3_malloc (int) ; 

__attribute__((used)) static int fulltextOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  fulltext_cursor *c;

  c = (fulltext_cursor *) sqlite3_malloc(sizeof(fulltext_cursor));
  if( c ){
    memset(c, 0, sizeof(fulltext_cursor));
    /* sqlite will initialize c->base */
    *ppCursor = &c->base;
    TRACE(("FTS2 Open %p: %p\n", pVTab, c));
    return SQLITE_OK;
  }else{
    return SQLITE_NOMEM;
  }
}