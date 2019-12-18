#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int nPagesize; scalar_t__ pCompress; } ;
struct TYPE_21__ {scalar_t__ iPg; int nCompress; int flags; int /*<<< orphan*/ * aData; TYPE_3__* pFS; } ;
struct TYPE_20__ {scalar_t__ iFirst; scalar_t__ iLastPg; int /*<<< orphan*/ * pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  Redirect ;
typedef  TYPE_2__ Page ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int PAGE_HASPREV ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_3__*,int) ; 
 int fsGetPageBefore (TYPE_3__*,TYPE_1__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ fsIsFirst (TYPE_3__*,scalar_t__) ; 
 scalar_t__ fsIsLast (TYPE_3__*,scalar_t__) ; 
 scalar_t__ fsLastPageOnBlock (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int fsNextPageOffset (TYPE_3__*,TYPE_1__*,scalar_t__,int,scalar_t__*) ; 
 int fsPageGet (TYPE_3__*,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,TYPE_2__**,int*) ; 
 int fsRedirectBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fsSegmentRedirects (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  lsmGetU32 (int /*<<< orphan*/ *) ; 

int lsmFsDbPageNext(Segment *pRun, Page *pPg, int eDir, Page **ppNext){
  int rc = LSM_OK;
  FileSystem *pFS = pPg->pFS;
  LsmPgno iPg = pPg->iPg;

  assert( 0==fsSegmentRedirects(pFS, pRun) );
  if( pFS->pCompress ){
    int nSpace = pPg->nCompress + 2*3;

    do {
      if( eDir>0 ){
        rc = fsNextPageOffset(pFS, pRun, iPg, nSpace, &iPg);
      }else{
        if( iPg==pRun->iFirst ){
          iPg = 0;
        }else{
          rc = fsGetPageBefore(pFS, pRun, iPg, &iPg);
        }
      }

      nSpace = 0;
      if( iPg!=0 ){
        rc = fsPageGet(pFS, pRun, iPg, 0, ppNext, &nSpace);
        assert( (*ppNext==0)==(rc!=LSM_OK || nSpace>0) );
      }else{
        *ppNext = 0;
      }
    }while( nSpace>0 && rc==LSM_OK );

  }else{
    Redirect *pRedir = pRun ? pRun->pRedirect : 0;
    assert( eDir==1 || eDir==-1 );
    if( eDir<0 ){
      if( pRun && iPg==pRun->iFirst ){
        *ppNext = 0;
        return LSM_OK;
      }else if( fsIsFirst(pFS, iPg) ){
        assert( pPg->flags & PAGE_HASPREV );
        iPg = fsLastPageOnBlock(pFS, lsmGetU32(&pPg->aData[-4]));
      }else{
        iPg--;
      }
    }else{
      if( pRun ){
        if( iPg==pRun->iLastPg ){
          *ppNext = 0;
          return LSM_OK;
        }
      }

      if( fsIsLast(pFS, iPg) ){
        int iBlk = fsRedirectBlock(
            pRedir, lsmGetU32(&pPg->aData[pFS->nPagesize-4])
        );
        iPg = fsFirstPageOnBlock(pFS, iBlk);
      }else{
        iPg++;
      }
    }
    rc = fsPageGet(pFS, pRun, iPg, 0, ppNext, 0);
  }

  return rc;
}