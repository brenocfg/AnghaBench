#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache ;
struct TYPE_6__ {int /*<<< orphan*/  (* xDestroy ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* xCachesize ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/ * (* xCreate ) (int,scalar_t__,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_1__ pcache2; } ;
struct TYPE_7__ {scalar_t__ nRefSum; scalar_t__ pDirty; int szPage; int /*<<< orphan*/ * pCache; int /*<<< orphan*/  bPurgeable; scalar_t__ szExtra; } ;
typedef  int /*<<< orphan*/  PgHdr ;
typedef  TYPE_2__ PCache ;

/* Variables and functions */
 scalar_t__ ROUND8 (int) ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  numberOfCachePages (TYPE_2__*) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/ * stub1 (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 

int sqlite3PcacheSetPageSize(PCache *pCache, int szPage){
  assert( pCache->nRefSum==0 && pCache->pDirty==0 );
  if( pCache->szPage ){
    sqlite3_pcache *pNew;
    pNew = sqlite3GlobalConfig.pcache2.xCreate(
                szPage, pCache->szExtra + ROUND8(sizeof(PgHdr)),
                pCache->bPurgeable
    );
    if( pNew==0 ) return SQLITE_NOMEM_BKPT;
    sqlite3GlobalConfig.pcache2.xCachesize(pNew, numberOfCachePages(pCache));
    if( pCache->pCache ){
      sqlite3GlobalConfig.pcache2.xDestroy(pCache->pCache);
    }
    pCache->pCache = pNew;
    pCache->szPage = szPage;
    pcacheTrace(("%p.PAGESIZE %d\n",pCache,szPage));
  }
  return SQLITE_OK;
}