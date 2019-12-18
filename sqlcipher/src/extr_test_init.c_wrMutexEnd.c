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
struct TYPE_3__ {int /*<<< orphan*/  (* xMutexEnd ) () ;} ;
struct TYPE_4__ {scalar_t__ mutex_init; TYPE_1__ mutex; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  stub1 () ; 
 TYPE_2__ wrapped ; 

__attribute__((used)) static int wrMutexEnd(void){
  wrapped.mutex.xMutexEnd();
  wrapped.mutex_init = 0;
  return SQLITE_OK;
}