#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int lsm_i64 ;
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_10__ {int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* xWrite ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ;int /*<<< orphan*/  (* xOpen ) (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ;} ;
typedef  TYPE_3__ lsm_env ;
struct TYPE_11__ {char* zName; int szSector; TYPE_2__* aFile; } ;
struct TYPE_9__ {int nSector; TYPE_1__* aSector; } ;
struct TYPE_8__ {int /*<<< orphan*/ * aOld; } ;
typedef  TYPE_4__ LsmDb ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *) ; 
 TYPE_3__* tdb_lsm_env () ; 
 int /*<<< orphan*/  testFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testPrngArray (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int testPrngValue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void doSystemCrash(LsmDb *pDb){
  lsm_env *pEnv = tdb_lsm_env();
  int iFile;
  int iSeed = pDb->aFile[0].nSector + pDb->aFile[1].nSector;

  char *zFile = pDb->zName;
  char *zFree = 0;

  for(iFile=0; iFile<2; iFile++){
    lsm_file *pFile = 0;
    int i;

    pEnv->xOpen(pEnv, zFile, 0, &pFile);
    for(i=0; i<pDb->aFile[iFile].nSector; i++){
      u8 *aOld = pDb->aFile[iFile].aSector[i].aOld;
      if( aOld ){
        int iOpt = testPrngValue(iSeed++) % 3;
        switch( iOpt ){
          case 0:
            break;

          case 1:
            testPrngArray(iSeed++, (u32 *)aOld, pDb->szSector/4);
            /* Fall-through */

          case 2:
            pEnv->xWrite(
                pFile, (lsm_i64)i * pDb->szSector, aOld, pDb->szSector
            );
            break;
        }
        testFree(aOld);
        pDb->aFile[iFile].aSector[i].aOld = 0;
      }
    }
    pEnv->xClose(pFile);
    zFree = zFile = sqlite3_mprintf("%s-log", pDb->zName);
  }

  sqlite3_free(zFree);
}