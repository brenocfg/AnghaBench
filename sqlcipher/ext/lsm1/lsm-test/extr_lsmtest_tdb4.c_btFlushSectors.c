#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int sqlite4_int64 ;
struct TYPE_7__ {int nSector; int nSectorSize; int /*<<< orphan*/ ** apSector; int /*<<< orphan*/  pFile; TYPE_2__* pBt; } ;
struct TYPE_6__ {TYPE_1__* pVfs; scalar_t__ bCrash; } ;
struct TYPE_5__ {int (* xSize ) (int /*<<< orphan*/ ,int*) ;int (* xWrite ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ;} ;
typedef  TYPE_3__ BtFile ;

/* Variables and functions */
 int MIN (int,int) ; 
 int SQLITE4_OK ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int stub1 (int /*<<< orphan*/ ,int*) ; 
 int stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  testFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * testMalloc (int) ; 
 int /*<<< orphan*/  testPrngArray (int,int /*<<< orphan*/ *,int) ; 
 int testPrngValue (int) ; 

__attribute__((used)) static int btFlushSectors(BtFile *p, int iFile){
  sqlite4_int64 iSz;
  int rc;
  int i;
  u8 *aTmp = 0;

  rc = p->pBt->pVfs->xSize(p->pFile, &iSz);
  for(i=0; rc==SQLITE4_OK && i<p->nSector; i++){
    if( p->pBt->bCrash && p->apSector[i] ){

      /* The system is simulating a crash. There are three choices for
      ** this sector:
      **
      **   1) Leave it as it is (simulating a successful write),
      **   2) Restore the original data (simulating a lost write),
      **   3) Populate the disk sector with garbage data.
      */
      sqlite4_int64 iSOff = p->nSectorSize*i;
      int nWrite = MIN(p->nSectorSize, iSz - iSOff);

      if( nWrite ){
        u8 *aWrite = 0;
        int iOpt = (testPrngValue(i) % 3) + 1;
        if( iOpt==1 ){
          aWrite = p->apSector[i];
        }else if( iOpt==3 ){
          if( aTmp==0 ) aTmp = testMalloc(p->nSectorSize);
          aWrite = aTmp;
          testPrngArray(i*13, (u32*)aWrite, nWrite/sizeof(u32));
        }

#if 0
fprintf(stderr, "handle sector %d of %s with %s\n", i, 
    iFile==0 ? "db" : "log",
    iOpt==1 ? "rollback" : iOpt==2 ? "write" : "omit"
);
fflush(stderr);
#endif

        if( aWrite ){
          rc = p->pBt->pVfs->xWrite(p->pFile, iSOff, aWrite, nWrite);
        }
      }
    }
    testFree(p->apSector[i]);
    p->apSector[i] = 0;
  }

  testFree(aTmp);
  return rc;
}