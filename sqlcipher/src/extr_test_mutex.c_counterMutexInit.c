#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int (* xMutexInit ) () ;} ;
struct TYPE_4__ {int disableInit; int isInit; TYPE_1__ m; } ;

/* Variables and functions */
 TYPE_2__ g ; 
 int stub1 () ; 

__attribute__((used)) static int counterMutexInit(void){ 
  int rc;
  if( g.disableInit ) return g.disableInit;
  rc = g.m.xMutexInit();
  g.isInit = 1;
  return rc;
}