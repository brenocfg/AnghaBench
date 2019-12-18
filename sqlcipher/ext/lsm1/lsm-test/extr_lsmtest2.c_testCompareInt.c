#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  testPrintError (char*,int,int) ; 
 int /*<<< orphan*/  test_failed () ; 

void testCompareInt(int i1, int i2, int *pRc){
  if( *pRc==0 && i1!=i2 ){
    testPrintError("testCompareInt: %d != %d\n", i1, i2);
    *pRc = 1;
    test_failed();
  }
}