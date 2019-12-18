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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  fulltext_vtab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 scalar_t__ SQLITE_NULL ; 
 int /*<<< orphan*/  assert (int) ; 
 int index_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int index_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_int64 (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_value_type (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextUpdate(sqlite3_vtab *pVtab, int nArg, sqlite3_value **ppArg,
                   sqlite_int64 *pRowid){
  fulltext_vtab *v = (fulltext_vtab *) pVtab;

  if( nArg<2 ){
    return index_delete(v, sqlite3_value_int64(ppArg[0]));
  }

  if( sqlite3_value_type(ppArg[0]) != SQLITE_NULL ){
    return SQLITE_ERROR;   /* an update; not yet supported */
  }

  assert( nArg==3 );    /* ppArg[1] = rowid, ppArg[2] = content */
  return index_insert(v, ppArg[1],
                      (const char *)sqlite3_value_text(ppArg[2]), pRowid);
}