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
typedef  int /*<<< orphan*/  sqlite_int64 ;
struct TYPE_5__ {int nColumn; } ;
typedef  TYPE_1__ fulltext_vtab ;

/* Variables and functions */
 scalar_t__ DL_DEFAULT ; 
 scalar_t__ DL_DOCIDS ; 
 int SQLITE_ERROR ; 
 int SQLITE_OK ; 
 int buildTerms (TYPE_1__*,int /*<<< orphan*/ ,char const*,int) ; 
 int content_select (TYPE_1__*,int /*<<< orphan*/ ,char const***) ; 
 int /*<<< orphan*/  freeStringArray (int,char const**) ; 

__attribute__((used)) static int deleteTerms(fulltext_vtab *v, sqlite_int64 iRowid){
  const char **pValues;
  int i, rc;

  /* TODO(shess) Should we allow such tables at all? */
  if( DL_DEFAULT==DL_DOCIDS ) return SQLITE_ERROR;

  rc = content_select(v, iRowid, &pValues);
  if( rc!=SQLITE_OK ) return rc;

  for(i = 0 ; i < v->nColumn; ++i) {
    rc = buildTerms(v, iRowid, pValues[i], -1);
    if( rc!=SQLITE_OK ) break;
  }

  freeStringArray(v->nColumn, pValues);
  return SQLITE_OK;
}