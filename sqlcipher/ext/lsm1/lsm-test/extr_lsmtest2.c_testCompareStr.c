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
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  testPrintError (char*,char const*,char const*) ; 
 int /*<<< orphan*/  test_failed () ; 

void testCompareStr(const char *z1, const char *z2, int *pRc){
  if( *pRc==0 ){
    if( strcmp(z1, z2) ){
      testPrintError("testCompareStr: \"%s\" != \"%s\"\n", z1, z2);
      *pRc = 1;
      test_failed();
    }
  }
}