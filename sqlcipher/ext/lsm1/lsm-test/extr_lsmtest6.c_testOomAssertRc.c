#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ bEnable; } ;
typedef  TYPE_1__ OomTest ;

/* Variables and functions */
 int LSM_NOMEM ; 
 int LSM_OK ; 
 int /*<<< orphan*/  testOomAssert (TYPE_1__*,int) ; 
 int testOomHit (TYPE_1__*) ; 

__attribute__((used)) static void testOomAssertRc(OomTest *p, int rc){
  testOomAssert(p, rc==LSM_OK || rc==LSM_NOMEM);
  testOomAssert(p, testOomHit(p)==(rc==LSM_NOMEM) || p->bEnable==0 );
}