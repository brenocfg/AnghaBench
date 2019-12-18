#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  aCkpt; } ;
typedef  TYPE_1__ CkptBuffer ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  ckptChecksum (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ckptSetValue (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void ckptAddChecksum(CkptBuffer *p, int nCkpt, int *pRc){
  if( *pRc==LSM_OK ){
    u32 aCksum[2] = {0, 0};
    ckptChecksum(p->aCkpt, nCkpt+2, &aCksum[0], &aCksum[1]);
    ckptSetValue(p, nCkpt, aCksum[0], pRc);
    ckptSetValue(p, nCkpt+1, aCksum[1], pRc);
  }
}