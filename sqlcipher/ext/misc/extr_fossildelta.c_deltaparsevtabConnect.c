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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  deltaparsevtab_vtab ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * sqlite3_malloc64 (int) ; 

__attribute__((used)) static int deltaparsevtabConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  deltaparsevtab_vtab *pNew;
  int rc;

  rc = sqlite3_declare_vtab(db,
           "CREATE TABLE x(op,a1,a2,delta HIDDEN)"
       );
  /* For convenience, define symbolic names for the index to each column. */
#define DELTAPARSEVTAB_OP     0
#define DELTAPARSEVTAB_A1     1
#define DELTAPARSEVTAB_A2     2
#define DELTAPARSEVTAB_DELTA  3
  if( rc==SQLITE_OK ){
    pNew = sqlite3_malloc64( sizeof(*pNew) );
    *ppVtab = (sqlite3_vtab*)pNew;
    if( pNew==0 ) return SQLITE_NOMEM;
    memset(pNew, 0, sizeof(*pNew));
  }
  return rc;
}