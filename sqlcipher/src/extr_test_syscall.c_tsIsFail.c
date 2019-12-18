#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nCount; scalar_t__ nFail; scalar_t__ bPersist; } ;

/* Variables and functions */
 TYPE_1__ gSyscall ; 

__attribute__((used)) static int tsIsFail(void){
  gSyscall.nCount--;
  if( gSyscall.nCount==0 || (gSyscall.nFail && gSyscall.bPersist) ){
    gSyscall.nFail++;
    return 1;
  }
  return 0;
}