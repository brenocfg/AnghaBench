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
typedef  TYPE_1__ fulltext_cursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static int fulltextOpen(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor){
  fulltext_cursor *c;

  c = (fulltext_cursor *) calloc(sizeof(fulltext_cursor), 1);
  /* sqlite will initialize c->base */
  *ppCursor = &c->base;

  return SQLITE_OK;
}