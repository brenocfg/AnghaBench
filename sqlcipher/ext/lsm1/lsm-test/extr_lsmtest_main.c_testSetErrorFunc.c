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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_failed () ; 

__attribute__((used)) static void testSetErrorFunc(int rc, int *pRc, const char *zFile, int iLine){
  if( rc ){
    *pRc = rc;
    fprintf(stderr, "FAILED (%s:%d) rc=%d ", zFile, iLine, rc);
    test_failed();
  }
}