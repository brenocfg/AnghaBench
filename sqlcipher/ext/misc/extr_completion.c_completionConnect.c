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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ completion_vtab ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 

__attribute__((used)) static int completionConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  completion_vtab *pNew;
  int rc;

  (void)(pAux);    /* Unused parameter */
  (void)(argc);    /* Unused parameter */
  (void)(argv);    /* Unused parameter */
  (void)(pzErr);   /* Unused parameter */

/* Column numbers */
#define COMPLETION_COLUMN_CANDIDATE 0  /* Suggested completion of the input */
#define COMPLETION_COLUMN_PREFIX    1  /* Prefix of the word to be completed */
#define COMPLETION_COLUMN_WHOLELINE 2  /* Entire line seen so far */
#define COMPLETION_COLUMN_PHASE     3  /* ePhase - used for debugging only */

  rc = sqlite3_declare_vtab(db,
      "CREATE TABLE x("
      "  candidate TEXT,"
      "  prefix TEXT HIDDEN,"
      "  wholeline TEXT HIDDEN,"
      "  phase INT HIDDEN"        /* Used for debugging only */
      ")");
  if( rc==SQLITE_OK ){
    pNew = sqlite3_malloc( sizeof(*pNew) );
    *ppVtab = (sqlite3_vtab*)pNew;
    if( pNew==0 ) return SQLITE_NOMEM;
    memset(pNew, 0, sizeof(*pNew));
    pNew->db = db;
  }
  return rc;
}