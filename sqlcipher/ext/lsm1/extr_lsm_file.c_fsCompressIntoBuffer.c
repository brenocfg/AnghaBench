#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* xCompress ) (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  pCtx; } ;
typedef  TYPE_1__ lsm_compress ;
struct TYPE_9__ {scalar_t__ aOBuffer; int /*<<< orphan*/  nBuffer; int /*<<< orphan*/  nPagesize; TYPE_1__* pCompress; } ;
struct TYPE_8__ {int /*<<< orphan*/  nData; scalar_t__ aData; int /*<<< orphan*/  nCompress; } ;
typedef  TYPE_2__ Page ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fsAllocateBuffer (TYPE_3__*,int) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fsCompressIntoBuffer(FileSystem *pFS, Page *pPg){
  lsm_compress *p = pFS->pCompress;

  if( fsAllocateBuffer(pFS, 1) ) return LSM_NOMEM;
  assert( pPg->nData==pFS->nPagesize );

  pPg->nCompress = pFS->nBuffer;
  return p->xCompress(p->pCtx, 
      (char *)pFS->aOBuffer, &pPg->nCompress, 
      (const char *)pPg->aData, pPg->nData
  );
}