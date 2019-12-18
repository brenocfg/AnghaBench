#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_3__ {int /*<<< orphan*/  base; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ FstreeVtab ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_declare_vtab (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 char* sqlite3_mprintf (char*) ; 

__attribute__((used)) static int fstreeConnect(
  sqlite3 *db,
  void *pAux,
  int argc, const char *const*argv,
  sqlite3_vtab **ppVtab,
  char **pzErr
){
  FstreeVtab *pTab;

  if( argc!=3 ){
    *pzErr = sqlite3_mprintf("wrong number of arguments");
    return SQLITE_ERROR;
  }

  pTab = (FstreeVtab *)sqlite3_malloc(sizeof(FstreeVtab));
  if( !pTab ) return SQLITE_NOMEM;
  memset(pTab, 0, sizeof(FstreeVtab));
  pTab->db = db;

  *ppVtab = &pTab->base;
  sqlite3_declare_vtab(db, "CREATE TABLE xyz(path, size, data);");

  return SQLITE_OK;
}