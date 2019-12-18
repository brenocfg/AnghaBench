#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
typedef  int /*<<< orphan*/  fts5_extension_function ;
typedef  int /*<<< orphan*/  fts5_api ;
struct TYPE_5__ {char* zFunc; void (* xDestroy ) (void*) ;struct TYPE_5__* pNext; int /*<<< orphan*/  xFunc; void* pUserData; TYPE_1__* pGlobal; } ;
struct TYPE_4__ {TYPE_2__* pAux; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ Fts5Global ;
typedef  TYPE_2__ Fts5Auxiliary ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sqlite3_malloc64 (scalar_t__) ; 
 int sqlite3_overload_function (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strlen (char const*) ; 

__attribute__((used)) static int fts5CreateAux(
  fts5_api *pApi,                 /* Global context (one per db handle) */
  const char *zName,              /* Name of new function */
  void *pUserData,                /* User data for aux. function */
  fts5_extension_function xFunc,  /* Aux. function implementation */
  void(*xDestroy)(void*)          /* Destructor for pUserData */
){
  Fts5Global *pGlobal = (Fts5Global*)pApi;
  int rc = sqlite3_overload_function(pGlobal->db, zName, -1);
  if( rc==SQLITE_OK ){
    Fts5Auxiliary *pAux;
    sqlite3_int64 nName;            /* Size of zName in bytes, including \0 */
    sqlite3_int64 nByte;            /* Bytes of space to allocate */

    nName = strlen(zName) + 1;
    nByte = sizeof(Fts5Auxiliary) + nName;
    pAux = (Fts5Auxiliary*)sqlite3_malloc64(nByte);
    if( pAux ){
      memset(pAux, 0, (size_t)nByte);
      pAux->zFunc = (char*)&pAux[1];
      memcpy(pAux->zFunc, zName, nName);
      pAux->pGlobal = pGlobal;
      pAux->pUserData = pUserData;
      pAux->xFunc = xFunc;
      pAux->xDestroy = xDestroy;
      pAux->pNext = pGlobal->pAux;
      pGlobal->pAux = pAux;
    }else{
      rc = SQLITE_NOMEM;
    }
  }

  return rc;
}