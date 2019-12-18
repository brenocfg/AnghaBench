#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_pcache_page ;
struct TYPE_5__ {int /*<<< orphan*/ * (* xFetch ) (scalar_t__,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_7__ {TYPE_1__ pcache2; } ;
struct TYPE_6__ {scalar_t__ pCache; int eCreate; scalar_t__ pDirty; scalar_t__ bPurgeable; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ PCache ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  pcacheTrace (char*) ; 
 TYPE_4__ sqlite3GlobalConfig ; 
 int /*<<< orphan*/ * stub1 (scalar_t__,int /*<<< orphan*/ ,int) ; 

sqlite3_pcache_page *sqlite3PcacheFetch(
  PCache *pCache,       /* Obtain the page from this cache */
  Pgno pgno,            /* Page number to obtain */
  int createFlag        /* If true, create page if it does not exist already */
){
  int eCreate;
  sqlite3_pcache_page *pRes;

  assert( pCache!=0 );
  assert( pCache->pCache!=0 );
  assert( createFlag==3 || createFlag==0 );
  assert( pCache->eCreate==((pCache->bPurgeable && pCache->pDirty) ? 1 : 2) );

  /* eCreate defines what to do if the page does not exist.
  **    0     Do not allocate a new page.  (createFlag==0)
  **    1     Allocate a new page if doing so is inexpensive.
  **          (createFlag==1 AND bPurgeable AND pDirty)
  **    2     Allocate a new page even it doing so is difficult.
  **          (createFlag==1 AND !(bPurgeable AND pDirty)
  */
  eCreate = createFlag & pCache->eCreate;
  assert( eCreate==0 || eCreate==1 || eCreate==2 );
  assert( createFlag==0 || pCache->eCreate==eCreate );
  assert( createFlag==0 || eCreate==1+(!pCache->bPurgeable||!pCache->pDirty) );
  pRes = sqlite3GlobalConfig.pcache2.xFetch(pCache->pCache, pgno, eCreate);
  pcacheTrace(("%p.FETCH %d%s (result: %p)\n",pCache,pgno,
               createFlag?" create":"",pRes));
  return pRes;
}