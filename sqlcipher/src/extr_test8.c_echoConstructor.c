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
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_5__ {char* zTableName; int isPattern; int /*<<< orphan*/  base; int /*<<< orphan*/  interp; void* zThis; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ echo_vtab ;
struct TYPE_6__ {int /*<<< orphan*/  interp; } ;
typedef  TYPE_2__ EchoModule ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  appendToEchoModule (int /*<<< orphan*/ ,char const* const) ; 
 int /*<<< orphan*/  dequoteString (char*) ; 
 int echoDeclareVtab (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  echoDestructor (int /*<<< orphan*/ *) ; 
 TYPE_1__* sqlite3MallocZero (int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 void* sqlite3_mprintf (char*,char const* const,...) ; 

__attribute__((used)) static int echoConstructor(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  int rc;
  int i;
  echo_vtab *pVtab;

  /* Allocate the sqlite3_vtab/echo_vtab structure itself */
  pVtab = sqlite3MallocZero( sizeof(*pVtab) );
  if( !pVtab ){
    return SQLITE_NOMEM;
  }
  pVtab->interp = ((EchoModule *)pAux)->interp;
  pVtab->db = db;

  /* Allocate echo_vtab.zThis */
  pVtab->zThis = sqlite3_mprintf("%s", argv[2]);
  if( !pVtab->zThis ){
    echoDestructor((sqlite3_vtab *)pVtab);
    return SQLITE_NOMEM;
  }

  /* Allocate echo_vtab.zTableName */
  if( argc>3 ){
    pVtab->zTableName = sqlite3_mprintf("%s", argv[3]);
    dequoteString(pVtab->zTableName);
    if( pVtab->zTableName && pVtab->zTableName[0]=='*' ){
      char *z = sqlite3_mprintf("%s%s", argv[2], &(pVtab->zTableName[1]));
      sqlite3_free(pVtab->zTableName);
      pVtab->zTableName = z;
      pVtab->isPattern = 1;
    }
    if( !pVtab->zTableName ){
      echoDestructor((sqlite3_vtab *)pVtab);
      return SQLITE_NOMEM;
    }
  }

  /* Log the arguments to this function to Tcl var ::echo_module */
  for(i=0; i<argc; i++){
    appendToEchoModule(pVtab->interp, argv[i]);
  }

  /* Invoke sqlite3_declare_vtab and set up other members of the echo_vtab
  ** structure. If an error occurs, delete the sqlite3_vtab structure and
  ** return an error code.
  */
  rc = echoDeclareVtab(pVtab, db);
  if( rc!=SQLITE_OK ){
    echoDestructor((sqlite3_vtab *)pVtab);
    return rc;
  }

  /* Success. Set *ppVtab and return */
  *ppVtab = &pVtab->base;
  return SQLITE_OK;
}