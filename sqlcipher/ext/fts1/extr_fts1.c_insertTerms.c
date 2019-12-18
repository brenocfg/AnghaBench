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
typedef  int /*<<< orphan*/  sqlite_int64 ;
typedef  int /*<<< orphan*/  sqlite3_value ;
struct TYPE_4__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;
typedef  int /*<<< orphan*/  fts1Hash ;

/* Variables and functions */
 int SQLITE_OK ; 
 int buildTerms (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int insertTerms(fulltext_vtab *v, fts1Hash *terms, sqlite_int64 iRowid,
                sqlite3_value **pValues){
  int i;
  for(i = 0; i < v->nColumn ; ++i){
    char *zText = (char*)sqlite3_value_text(pValues[i]);
    int rc = buildTerms(v, terms, iRowid, zText, i);
    if( rc!=SQLITE_OK ) return rc;
  }
  return SQLITE_OK;
}