#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zRight ;
typedef  int /*<<< orphan*/  zLevel ;
typedef  int /*<<< orphan*/  zLeft ;
struct TYPE_10__ {int /*<<< orphan*/  pEnv; scalar_t__ xLog; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  aRight ;
struct TYPE_11__ {int nRight; int /*<<< orphan*/ * aRhs; int /*<<< orphan*/  lhs; struct TYPE_11__* pNext; scalar_t__ flags; scalar_t__ iAge; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  int /*<<< orphan*/  Segment ;
typedef  TYPE_2__ Level ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileToString (TYPE_1__*,char*,int,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* lsmDbSnapshotLevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * lsmFsIntegrityCheck (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmInfoFreelist (TYPE_1__*,char**) ; 
 int /*<<< orphan*/  lsmLogMessage (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ **,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int) ; 
 int /*<<< orphan*/  sortedDumpSegment (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

void lsmSortedDumpStructure(
  lsm_db *pDb,                    /* Database handle (used for xLog callback) */
  Snapshot *pSnap,                /* Snapshot to dump */
  int bKeys,                      /* Output the keys from each segment */
  int bVals,                      /* Output the values from each segment */
  const char *zWhy                /* Caption to print near top of dump */
){
  Snapshot *pDump = pSnap;
  Level *pTopLevel;
  char *zFree = 0;

  assert( pSnap );
  pTopLevel = lsmDbSnapshotLevel(pDump);
  if( pDb->xLog && pTopLevel ){
    static int nCall = 0;
    Level *pLevel;
    int iLevel = 0;

    nCall++;
    lsmLogMessage(pDb, LSM_OK, "Database structure %d (%s)", nCall, zWhy);

#if 0
    if( nCall==1031 || nCall==1032 ) bKeys=1;
#endif

    for(pLevel=pTopLevel; pLevel; pLevel=pLevel->pNext){
      char zLeft[1024];
      char zRight[1024];
      int i = 0;

      Segment *aLeft[24];  
      Segment *aRight[24];

      int nLeft = 0;
      int nRight = 0;

      Segment *pSeg = &pLevel->lhs;
      aLeft[nLeft++] = pSeg;

      for(i=0; i<pLevel->nRight; i++){
        aRight[nRight++] = &pLevel->aRhs[i];
      }

#ifdef LSM_LOG_FREELIST
      if( nRight ){
        memmove(&aRight[1], aRight, sizeof(aRight[0])*nRight);
        aRight[0] = 0;
        nRight++;
      }
#endif

      for(i=0; i<nLeft || i<nRight; i++){
        int iPad = 0;
        char zLevel[32];
        zLeft[0] = '\0';
        zRight[0] = '\0';

        if( i<nLeft ){ 
          fileToString(pDb, zLeft, sizeof(zLeft), 24, aLeft[i]); 
        }
        if( i<nRight ){ 
          fileToString(pDb, zRight, sizeof(zRight), 24, aRight[i]); 
        }

        if( i==0 ){
          snprintf(zLevel, sizeof(zLevel), "L%d: (age=%d) (flags=%.4x)",
              iLevel, (int)pLevel->iAge, (int)pLevel->flags
          );
        }else{
          zLevel[0] = '\0';
        }

        if( nRight==0 ){
          iPad = 10;
        }

        lsmLogMessage(pDb, LSM_OK, "% 25s % *s% -35s %s", 
            zLevel, iPad, "", zLeft, zRight
        );
      }

      iLevel++;
    }

    if( bKeys ){
      for(pLevel=pTopLevel; pLevel; pLevel=pLevel->pNext){
        int i;
        sortedDumpSegment(pDb, &pLevel->lhs, bVals);
        for(i=0; i<pLevel->nRight; i++){
          sortedDumpSegment(pDb, &pLevel->aRhs[i], bVals);
        }
      }
    }
  }

  lsmInfoFreelist(pDb, &zFree);
  lsmLogMessage(pDb, LSM_OK, "Freelist: %s", zFree);
  lsmFree(pDb->pEnv, zFree);

  assert( lsmFsIntegrityCheck(pDb) );
}