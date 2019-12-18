#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int i64 ;
struct TYPE_27__ {int nPagesize; scalar_t__ pCompress; int nOut; TYPE_2__** apHash; int /*<<< orphan*/  nRead; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; TYPE_2__* pMapped; scalar_t__ pMap; TYPE_2__* pFree; } ;
struct TYPE_26__ {int flags; scalar_t__ nRef; scalar_t__ pMappedNext; scalar_t__ pLruNext; scalar_t__ pLruPrev; int nData; int /*<<< orphan*/ * aData; struct TYPE_26__* pHashNext; TYPE_3__* pFS; scalar_t__ iPg; struct TYPE_26__* pFreeNext; } ;
struct TYPE_25__ {int /*<<< orphan*/  pRedirect; } ;
typedef  TYPE_1__ Segment ;
typedef  TYPE_2__ Page ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_3__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int PAGE_FREE ; 
 int PAGE_HASPREV ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assert_lists_are_ok (TYPE_3__*) ; 
 scalar_t__ fsFirstPageOnBlock (TYPE_3__*,int) ; 
 int /*<<< orphan*/  fsGrowMapping (TYPE_3__*,int,int*) ; 
 scalar_t__ fsIsFirst (TYPE_3__*,scalar_t__) ; 
 scalar_t__ fsIsLast (TYPE_3__*,scalar_t__) ; 
 scalar_t__ fsMmapPage (TYPE_3__*,scalar_t__) ; 
 int fsPageBuffer (TYPE_3__*,TYPE_2__**) ; 
 int /*<<< orphan*/  fsPageBufferFree (TYPE_2__*) ; 
 TYPE_2__* fsPageFindInHash (TYPE_3__*,scalar_t__,int*) ; 
 int /*<<< orphan*/  fsPageRemoveFromLru (TYPE_3__*,TYPE_2__*) ; 
 int fsReadPagedata (TYPE_3__*,TYPE_1__*,TYPE_2__*,int*) ; 
 int lsmEnvRead (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lsmFsRedirectPage (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__* lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,scalar_t__) ; 

__attribute__((used)) static int fsPageGet(
  FileSystem *pFS,                /* File-system handle */
  Segment *pSeg,                  /* Block redirection to use (or NULL) */
  LsmPgno iPg,                    /* Page id */
  int noContent,                  /* True to not load content from disk */
  Page **ppPg,                    /* OUT: New page handle */
  int *pnSpace                    /* OUT: Bytes of free space */
){
  Page *p;
  int iHash;
  int rc = LSM_OK;

  /* In most cases iReal is the same as iPg. Except, if pSeg->pRedirect is 
  ** not NULL, and the block containing iPg has been redirected, then iReal
  ** is the page number after redirection.  */
  LsmPgno iReal = lsmFsRedirectPage(pFS, (pSeg ? pSeg->pRedirect : 0), iPg);

  assert_lists_are_ok(pFS);
  assert( iPg>=fsFirstPageOnBlock(pFS, 1) );
  assert( iReal>=fsFirstPageOnBlock(pFS, 1) );
  *ppPg = 0;

  /* Search the hash-table for the page */
  p = fsPageFindInHash(pFS, iReal, &iHash);

  if( p ){
    assert( p->flags & PAGE_FREE );
    if( p->nRef==0 ) fsPageRemoveFromLru(pFS, p);
  }else{

    if( fsMmapPage(pFS, iReal) ){
      i64 iEnd = (i64)iReal * pFS->nPagesize;
      fsGrowMapping(pFS, iEnd, &rc);
      if( rc!=LSM_OK ) return rc;

      if( pFS->pFree ){
        p = pFS->pFree;
        pFS->pFree = p->pFreeNext;
        assert( p->nRef==0 );
      }else{
        p = lsmMallocZeroRc(pFS->pEnv, sizeof(Page), &rc);
        if( rc ) return rc;
        p->pFS = pFS;
      }
      p->aData = &((u8 *)pFS->pMap)[pFS->nPagesize * (iReal-1)];
      p->iPg = iReal;

      /* This page now carries a pointer to the mapping. Link it in to
      ** the FileSystem.pMapped list.  */
      assert( p->pMappedNext==0 );
      p->pMappedNext = pFS->pMapped;
      pFS->pMapped = p;

      assert( pFS->pCompress==0 );
      assert( (p->flags & PAGE_FREE)==0 );
    }else{
      rc = fsPageBuffer(pFS, &p);
      if( rc==LSM_OK ){
        int nSpace = 0;
        p->iPg = iReal;
        p->nRef = 0;
        p->pFS = pFS;
        assert( p->flags==0 || p->flags==PAGE_FREE );

#ifdef LSM_DEBUG
        memset(p->aData, 0x56, pFS->nPagesize);
#endif
        assert( p->pLruNext==0 && p->pLruPrev==0 );
        if( noContent==0 ){
          if( pFS->pCompress ){
            rc = fsReadPagedata(pFS, pSeg, p, &nSpace);
          }else{
            int nByte = pFS->nPagesize;
            i64 iOff = (i64)(iReal-1) * pFS->nPagesize;
            rc = lsmEnvRead(pFS->pEnv, pFS->fdDb, iOff, p->aData, nByte);
          }
          pFS->nRead++;
        }

        /* If the xRead() call was successful (or not attempted), link the
        ** page into the page-cache hash-table. Otherwise, if it failed,
        ** free the buffer. */
        if( rc==LSM_OK && nSpace==0 ){
          p->pHashNext = pFS->apHash[iHash];
          pFS->apHash[iHash] = p;
        }else{
          fsPageBufferFree(p);
          p = 0;
          if( pnSpace ) *pnSpace = nSpace;
        }
      }
    }

    assert( (rc==LSM_OK && (p || (pnSpace && *pnSpace)))
         || (rc!=LSM_OK && p==0) 
    );
  }

  if( rc==LSM_OK && p ){
    if( pFS->pCompress==0 && (fsIsLast(pFS, iReal) || fsIsFirst(pFS, iReal)) ){
      p->nData = pFS->nPagesize - 4;
      if( fsIsFirst(pFS, iReal) && p->nRef==0 ){
        p->aData += 4;
        p->flags |= PAGE_HASPREV;
      }
    }else{
      p->nData = pFS->nPagesize;
    }
    pFS->nOut += (p->nRef==0);
    p->nRef++;
  }
  *ppPg = p;
  return rc;
}