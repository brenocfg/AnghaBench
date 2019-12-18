#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rc; int iNext; scalar_t__ nFail; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ OomTest ;

/* Variables and functions */
 int /*<<< orphan*/  testMallocOom (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void (*) (void*),void*) ; 
 scalar_t__ xOomHook ; 

__attribute__((used)) static int testOomContinue(OomTest *p){
  if( p->rc!=0 || (p->iNext>1 && p->nFail==0) ){
    return 0;
  }
  p->nFail = 0;
  testMallocOom(p->pEnv, p->iNext, 0, (void (*)(void*))xOomHook, (void *)p);
  return 1;
}