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
typedef  int /*<<< orphan*/  ThreadSet ;
typedef  int /*<<< orphan*/  TestDb ;
struct TYPE_6__ {int /*<<< orphan*/  nKey; int /*<<< orphan*/  nFanout; } ;
struct TYPE_5__ {int member_0; int member_1; } ;
struct TYPE_7__ {int member_1; int member_2; int member_3; int member_4; int nReadwrite; int nFastReader; int nSlowReader; char const* zSystem; int /*<<< orphan*/  nMs; TYPE_2__ param; int /*<<< orphan*/  member_5; TYPE_1__ member_0; } ;
typedef  TYPE_3__ Mt1Test ;

/* Variables and functions */
 int ArraySize (TYPE_3__*) ; 
 int /*<<< orphan*/  mt1Main ; 
 int /*<<< orphan*/  printf (char*,int,int,char const*) ; 
 int testCaseBegin (int*,char const*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 
 int /*<<< orphan*/  testClose (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * testOpen (char const*,int,int*) ; 
 int testThreadGetResult (int /*<<< orphan*/ *,int,char const**) ; 
 int /*<<< orphan*/ * testThreadInit (int) ; 
 int /*<<< orphan*/  testThreadLaunch (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  testThreadShutdown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testThreadWait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void do_test_mt1(
  const char *zSystem,            /* Database system name */
  const char *zPattern,           /* Run test cases that match this pattern */
  int *pRc                        /* IN/OUT: Error code */
){
  Mt1Test aTest[] = {
    /* param, nReadwrite, nFastReader, nSlowReader, nMs, zSystem */
    { {10, 1000},     4, 0, 0,   10000,   0 },
    { {10, 1000},     4, 4, 2,   100000,  0 },
    { {10, 100000},   4, 0, 0,   10000,   0 },
    { {10, 100000},   4, 4, 2,   100000,  0 },
  };
  int i;

  for(i=0; *pRc==0 && i<ArraySize(aTest); i++){
    Mt1Test *p = &aTest[i];
    int bRun = testCaseBegin(pRc, zPattern, 
        "mt1.%s.db=%d,%d.ms=%d.rdwr=%d.fast=%d.slow=%d", 
        zSystem, p->param.nFanout, p->param.nKey, 
        p->nMs, p->nReadwrite, p->nFastReader, p->nSlowReader
    );
    if( bRun ){
      TestDb *pDb;
      ThreadSet *pSet;
      int iThread;
      int nThread;

      p->zSystem = zSystem;
      pDb = testOpen(zSystem, 1, pRc);

      nThread = p->nReadwrite + p->nFastReader + p->nSlowReader;
      pSet = testThreadInit(nThread);
      for(iThread=0; *pRc==0 && iThread<nThread; iThread++){
        testThreadLaunch(pSet, iThread, mt1Main, (void *)p);
      }

      testThreadWait(pSet, p->nMs);
      for(iThread=0; *pRc==0 && iThread<nThread; iThread++){
        *pRc = testThreadGetResult(pSet, iThread, 0);
      }
      testCaseFinish(*pRc);

      for(iThread=0; *pRc==0 && iThread<nThread; iThread++){
        const char *zMsg = 0;
        *pRc = testThreadGetResult(pSet, iThread, &zMsg);
        printf("  Info: thread %d (%d): %s\n", iThread, *pRc, zMsg);
      }

      testThreadShutdown(pSet);
      testClose(&pDb);
    }
  }
}