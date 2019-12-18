#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_9__ {int /*<<< orphan*/  zName; int /*<<< orphan*/  zDb; int /*<<< orphan*/  azContentColumn; int /*<<< orphan*/  nColumn; } ;
typedef  TYPE_1__ TableSpec ;
struct TYPE_10__ {char* s; } ;
typedef  TYPE_2__ StringBuffer ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  append (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  appendList (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clearTableSpec (TYPE_1__*) ; 
 int constructVtab (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ **,char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  initStringBuffer (TYPE_2__*) ; 
 int parseSpec (TYPE_1__*,int,char const* const*,char**) ; 
 int sql_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int fulltextCreate(sqlite3 *db, void *pAux,
                          int argc, const char * const *argv,
                          sqlite3_vtab **ppVTab, char **pzErr){
  int rc;
  TableSpec spec;
  StringBuffer schema;
  TRACE(("FTS1 Create\n"));

  rc = parseSpec(&spec, argc, argv, pzErr);
  if( rc!=SQLITE_OK ) return rc;

  initStringBuffer(&schema);
  append(&schema, "CREATE TABLE %_content(");
  appendList(&schema, spec.nColumn, spec.azContentColumn);
  append(&schema, ")");
  rc = sql_exec(db, spec.zDb, spec.zName, schema.s);
  free(schema.s);
  if( rc!=SQLITE_OK ) goto out;

  rc = sql_exec(db, spec.zDb, spec.zName,
    "create table %_term(term text, segment integer, doclist blob, "
                        "primary key(term, segment));");
  if( rc!=SQLITE_OK ) goto out;

  rc = constructVtab(db, &spec, ppVTab, pzErr);

out:
  clearTableSpec(&spec);
  return rc;
}