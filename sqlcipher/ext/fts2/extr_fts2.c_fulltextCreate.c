#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  fts2Hash ;
struct TYPE_5__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  azContentColumn; int /*<<< orphan*/  nColumn; } ;
typedef  TYPE_1__ TableSpec ;
typedef  int /*<<< orphan*/  StringBuffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  appendList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearTableSpec (TYPE_1__*) ; 
 int constructVtab (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  initStringBuffer (int /*<<< orphan*/ *) ; 
 int parseSpec (TYPE_1__*,int,char const* const*,char**) ; 
 int sql_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* stringBufferData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stringBufferDestroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fulltextCreate(sqlite3 *db, void *pAux,
                          int argc, const char * const *argv,
                          sqlite3_vtab **ppVTab, char **pzErr){
  int rc;
  TableSpec spec;
  StringBuffer schema;
  TRACE(("FTS2 Create\n"));

  rc = parseSpec(&spec, argc, argv, pzErr);
  if( rc!=SQLITE_OK ) return rc;

  initStringBuffer(&schema);
  append(&schema, "CREATE TABLE %_content(");
  appendList(&schema, spec.nColumn, spec.azContentColumn);
  append(&schema, ")");
  rc = sql_exec(db, spec.zDb, spec.zName, stringBufferData(&schema));
  stringBufferDestroy(&schema);
  if( rc!=SQLITE_OK ) goto out;

  rc = sql_exec(db, spec.zDb, spec.zName,
                "create table %_segments(block blob);");
  if( rc!=SQLITE_OK ) goto out;

  rc = sql_exec(db, spec.zDb, spec.zName,
                "create table %_segdir("
                "  level integer,"
                "  idx integer,"
                "  start_block integer,"
                "  leaves_end_block integer,"
                "  end_block integer,"
                "  root blob,"
                "  primary key(level, idx)"
                ");");
  if( rc!=SQLITE_OK ) goto out;

  rc = constructVtab(db, (fts2Hash *)pAux, &spec, ppVTab, pzErr);

out:
  clearTableSpec(&spec);
  return rc;
}