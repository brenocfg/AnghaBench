#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int member_1; int member_2; int member_3; int member_4; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {int member_1; int member_2; int member_3; TYPE_1__ member_0; } ;
typedef  TYPE_2__ Mctest ;

/* Variables and functions */
 int ArraySize (TYPE_2__*) ; 
 int /*<<< orphan*/  TEST_DATASOURCE_RANDOM ; 
 int /*<<< orphan*/  do_mc_test (char const*,TYPE_2__*,int*) ; 
 scalar_t__ testCaseBegin (int*,char const*,char*,char const*,int) ; 
 int /*<<< orphan*/  testCaseFinish (int) ; 

void test_mc(
  const char *zSystem,            /* Database system name */
  const char *zPattern,           /* Run test cases that match this pattern */
  int *pRc                        /* IN/OUT: Error code */
){
  int i;
  Mctest aTest[] = {
    { { TEST_DATASOURCE_RANDOM, 10,10, 100,100 }, 100, 10, 5 },
  };

  for(i=0; i<ArraySize(aTest); i++){
    if( testCaseBegin(pRc, zPattern, "mc1.%s.%d", zSystem, i) ){
      do_mc_test(zSystem, &aTest[i], pRc);
      testCaseFinish(*pRc);
    }
  }
}