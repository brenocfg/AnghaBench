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
struct TYPE_4__ {int nRow; int iInst; } ;
typedef  TYPE_1__ vtablog_vtab ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* sqlite3_malloc (int) ; 
 char* sqlite3_mprintf (char*) ; 
 scalar_t__ vtablog_string_parameter (char**,char*,char const*,char**) ; 

__attribute__((used)) static int vtablogConnectCreate(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr,
  int isCreate
){
  static int nInst = 0;
  vtablog_vtab *pNew;
  int i;
  int rc;
  int iInst = ++nInst;
  char *zSchema = 0;
  char *zNRow = 0;

  printf("vtablog%s(tab=%d):\n", isCreate ? "Create" : "Connect", iInst);
  printf("  argc=%d\n", argc);
  for(i=0; i<argc; i++){
    printf("  argv[%d] = ", i);
    if( argv[i] ){
      printf("[%s]\n", argv[i]);
    }else{
      printf("NULL\n");
    }
  }

  for(i=3; i<argc; i++){
    const char *z = argv[i];
    if( vtablog_string_parameter(pzErr, "schema", z, &zSchema) ){
      return SQLITE_ERROR;
    }
    if( vtablog_string_parameter(pzErr, "rows", z, &zNRow) ){
      return SQLITE_ERROR;
    }
  }

  if( zSchema==0 ){
    *pzErr = sqlite3_mprintf("no schema defined");
    return SQLITE_ERROR;
  }
  rc = sqlite3_declare_vtab(db, zSchema);
  if( rc==SQLITE_OK ){
    pNew = sqlite3_malloc( sizeof(*pNew) );
    *ppVtab = (sqlite3_vtab*)pNew;
    if( pNew==0 ) return SQLITE_NOMEM;
    memset(pNew, 0, sizeof(*pNew));
    pNew->nRow = 10;
    if( zNRow ) pNew->nRow = atoi(zNRow);
    pNew->iInst = iInst;
  }
  return rc;
}