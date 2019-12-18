#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vtab_cursor ;
typedef  int /*<<< orphan*/  sqlite3_vtab ;
typedef  int sqlite3_int64 ;
struct TYPE_12__ {int nCol; } ;
struct TYPE_11__ {int* aColumnSize; scalar_t__ iCsrId; struct TYPE_11__* pNext; } ;
struct TYPE_8__ {TYPE_5__* pConfig; } ;
struct TYPE_10__ {TYPE_2__* pGlobal; TYPE_1__ p; } ;
struct TYPE_9__ {scalar_t__ iNextId; TYPE_4__* pCsr; } ;
typedef  TYPE_2__ Fts5Global ;
typedef  TYPE_3__ Fts5FullTable ;
typedef  TYPE_4__ Fts5Cursor ;
typedef  TYPE_5__ Fts5Config ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int fts5NewTransaction (TYPE_3__*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int fts5OpenMethod(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCsr){
  Fts5FullTable *pTab = (Fts5FullTable*)pVTab;
  Fts5Config *pConfig = pTab->p.pConfig;
  Fts5Cursor *pCsr = 0;           /* New cursor object */
  sqlite3_int64 nByte;            /* Bytes of space to allocate */
  int rc;                         /* Return code */

  rc = fts5NewTransaction(pTab);
  if( rc==SQLITE_OK ){
    nByte = sizeof(Fts5Cursor) + pConfig->nCol * sizeof(int);
    pCsr = (Fts5Cursor*)sqlite3_malloc64(nByte);
    if( pCsr ){
      Fts5Global *pGlobal = pTab->pGlobal;
      memset(pCsr, 0, (size_t)nByte);
      pCsr->aColumnSize = (int*)&pCsr[1];
      pCsr->pNext = pGlobal->pCsr;
      pGlobal->pCsr = pCsr;
      pCsr->iCsrId = ++pGlobal->iNextId;
    }else{
      rc = SQLITE_NOMEM;
    }
  }
  *ppCsr = (sqlite3_vtab_cursor*)pCsr;
  return rc;
}