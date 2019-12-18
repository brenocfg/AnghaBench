#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_11__ {int (* xUncompress ) (int /*<<< orphan*/ ,char*,int*,char const*,int) ;int /*<<< orphan*/  pCtx; } ;
typedef  TYPE_2__ lsm_compress ;
typedef  int /*<<< orphan*/  i64 ;
typedef  int /*<<< orphan*/  aSz ;
struct TYPE_13__ {int nBuffer; int* aIBuffer; int nPagesize; TYPE_2__* pCompress; } ;
struct TYPE_12__ {int nCompress; TYPE_1__* pFS; scalar_t__ aData; int /*<<< orphan*/  iPg; } ;
struct TYPE_10__ {int nPagesize; } ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_3__ Page ;
typedef  TYPE_4__ FileSystem ;

/* Variables and functions */
 int LSM_CORRUPT_BKPT ; 
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int fsAddOffset (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ fsAllocateBuffer (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int fsReadData (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ getRecordSize (int*,int*) ; 
 int stub1 (int /*<<< orphan*/ ,char*,int*,char const*,int) ; 

__attribute__((used)) static int fsReadPagedata(
  FileSystem *pFS,                /* File-system handle */
  Segment *pSeg,                  /* pPg is part of this segment */
  Page *pPg,                      /* Page to read and uncompress data for */
  int *pnSpace                    /* OUT: Total bytes of free space */
){
  lsm_compress *p = pFS->pCompress;
  i64 iOff = pPg->iPg;
  u8 aSz[3];
  int rc;

  assert( p && pPg->nCompress==0 );

  if( fsAllocateBuffer(pFS, 0) ) return LSM_NOMEM;

  rc = fsReadData(pFS, pSeg, iOff, aSz, sizeof(aSz));

  if( rc==LSM_OK ){
    int bFree;
    if( aSz[0] & 0x80 ){
      pPg->nCompress = (int)getRecordSize(aSz, &bFree);
    }else{
      pPg->nCompress = (int)aSz[0] - sizeof(aSz)*2;
      bFree = 1;
    }
    if( bFree ){
      if( pnSpace ){
        *pnSpace = pPg->nCompress + sizeof(aSz)*2;
      }else{
        rc = LSM_CORRUPT_BKPT;
      }
    }else{
      rc = fsAddOffset(pFS, pSeg, iOff, 3, &iOff);
      if( rc==LSM_OK ){
        if( pPg->nCompress>pFS->nBuffer ){
          rc = LSM_CORRUPT_BKPT;
        }else{
          rc = fsReadData(pFS, pSeg, iOff, pFS->aIBuffer, pPg->nCompress);
        }
        if( rc==LSM_OK ){
          int n = pFS->nPagesize;
          rc = p->xUncompress(p->pCtx, 
              (char *)pPg->aData, &n, 
              (const char *)pFS->aIBuffer, pPg->nCompress
          );
          if( rc==LSM_OK && n!=pPg->pFS->nPagesize ){
            rc = LSM_CORRUPT_BKPT;
          }
        }
      }
    }
  }
  return rc;
}