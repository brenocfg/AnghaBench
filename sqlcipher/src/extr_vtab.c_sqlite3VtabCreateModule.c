#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_module ;
struct TYPE_8__ {int /*<<< orphan*/  aModule; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_9__ {char* zName; void (* xDestroy ) (void*) ;scalar_t__ pEpoTab; void* pAux; int /*<<< orphan*/  const* pModule; } ;
typedef  TYPE_2__ Module ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  sqlite3DbFree (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ sqlite3HashInsert (int /*<<< orphan*/ *,char*,void*) ; 
 scalar_t__ sqlite3Malloc (int) ; 
 int /*<<< orphan*/  sqlite3OomFault (TYPE_1__*) ; 
 int sqlite3Strlen30 (char const*) ; 

Module *sqlite3VtabCreateModule(
  sqlite3 *db,                    /* Database in which module is registered */
  const char *zName,              /* Name assigned to this module */
  const sqlite3_module *pModule,  /* The definition of the module */
  void *pAux,                     /* Context pointer for xCreate/xConnect */
  void (*xDestroy)(void *)        /* Module destructor function */
){
  Module *pMod;
  int nName = sqlite3Strlen30(zName);
  pMod = (Module *)sqlite3Malloc(sizeof(Module) + nName + 1);
  if( pMod==0 ){
    sqlite3OomFault(db);
  }else{
    Module *pDel;
    char *zCopy = (char *)(&pMod[1]);
    memcpy(zCopy, zName, nName+1);
    pMod->zName = zCopy;
    pMod->pModule = pModule;
    pMod->pAux = pAux;
    pMod->xDestroy = xDestroy;
    pMod->pEpoTab = 0;
    pDel = (Module *)sqlite3HashInsert(&db->aModule,zCopy,(void*)pMod);
    assert( pDel==0 || pDel==pMod );
    if( pDel ){
      sqlite3OomFault(db);
      sqlite3DbFree(db, pDel);
      pMod = 0;
    }
  }
  return pMod;
}