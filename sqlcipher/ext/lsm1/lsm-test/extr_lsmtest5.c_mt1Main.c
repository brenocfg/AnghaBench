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
typedef  int /*<<< orphan*/  aValue ;
typedef  int /*<<< orphan*/  aRnd ;
typedef  int /*<<< orphan*/  ThreadSet ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_7__ {int nKey; } ;
struct TYPE_6__ {int nMs; int /*<<< orphan*/ * pSet; } ;
struct TYPE_5__ {int nReadwrite; int nFastReader; int nMs; TYPE_3__ param; int /*<<< orphan*/  zSystem; } ;
typedef  TYPE_1__ Mt1Test ;
typedef  TYPE_2__ Mt1DelayCtx ;

/* Variables and functions */
 int MT1_THREAD_FAST ; 
 int MT1_THREAD_RDWR ; 
 int MT1_THREAD_SLOW ; 
 int /*<<< orphan*/  dbReadOperation (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int,int*) ; 
 scalar_t__ dbWriteOperation (TYPE_3__*,int /*<<< orphan*/ *,int,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char*) ; 
 int /*<<< orphan*/  tdb_lsm_config_work_hook (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * testOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  testPrngString (int,char*,int) ; 
 int testPrngValue (int) ; 
 scalar_t__ testThreadGetHalt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testThreadSetHalt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testThreadSetResult (int /*<<< orphan*/ *,int,int,char*,...) ; 
 int /*<<< orphan*/  xMt1Delay ; 
 int /*<<< orphan*/  xMt1Work ; 

__attribute__((used)) static void mt1Main(ThreadSet *pThreadSet, int iThread, void *pCtx){
  Mt1Test *p = (Mt1Test *)pCtx;   /* Test parameters */
  Mt1DelayCtx delay;
  int nRead = 0;                  /* Number of calls to dbReadOperation() */
  int nWrite = 0;                 /* Number of completed database writes */
  int rc = 0;                     /* Error code */
  int iPrng;                      /* Prng argument variable */
  TestDb *pDb;                    /* Database handle */
  int eType;

  delay.pSet = pThreadSet;
  delay.nMs = 0;
  if( iThread<p->nReadwrite ){
    eType = MT1_THREAD_RDWR;
  }else if( iThread<(p->nReadwrite+p->nFastReader) ){
    eType = MT1_THREAD_FAST;
  }else{
    eType = MT1_THREAD_SLOW;
    delay.nMs = (p->nMs / 20);
  }

  /* Open a new database connection. Initialize the pseudo-random number
  ** argument based on the thread number.  */
  iPrng = testPrngValue(iThread);
  pDb = testOpen(p->zSystem, 0, &rc);

  if( rc==0 ){
    tdb_lsm_config_work_hook(pDb, xMt1Work, 0);
  }

  /* Loop until either an error occurs or some other thread sets the
  ** halt flag.  */
  while( rc==0 && testThreadGetHalt(pThreadSet)==0 ){
    int iKey;

    /* Perform a read operation on an arbitrarily selected key. */
    iKey = (testPrngValue(iPrng++) % p->param.nKey);
    dbReadOperation(&p->param, pDb, xMt1Delay, (void *)&delay, iKey, &rc);
    if( rc ) continue;
    nRead++;

    /* Attempt to write an arbitrary key value pair (and update the associated
    ** checksum entries). dbWriteOperation() returns 1 if the write is
    ** successful, or 0 if it failed with an LSM_BUSY error.  */
    if( eType==MT1_THREAD_RDWR ){
      char aValue[50];
      char aRnd[25];

      iKey = (testPrngValue(iPrng++) % p->param.nKey);
      testPrngString(iPrng, aRnd, sizeof(aRnd));
      iPrng += sizeof(aRnd);
      snprintf(aValue, sizeof(aValue), "%d.%s", iThread, aRnd);
      nWrite += dbWriteOperation(&p->param, pDb, iKey, aValue, &rc);
    }
  }
  testClose(&pDb);

  /* If an error has occured, set the thread error code and the threadset 
  ** halt flag to tell the other test threads to halt. Otherwise, set the
  ** thread error code to 0 and post a message with the number of read
  ** and write operations completed.  */
  if( rc ){
    testThreadSetResult(pThreadSet, iThread, rc, 0);
    testThreadSetHalt(pThreadSet);
  }else{
    testThreadSetResult(pThreadSet, iThread, 0, "r/w: %d/%d", nRead, nWrite);
  }
}