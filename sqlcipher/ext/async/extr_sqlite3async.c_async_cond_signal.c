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
struct TYPE_2__ {int /*<<< orphan*/ * aCond; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MUTEX_QUEUE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_held (int /*<<< orphan*/ ) ; 
 TYPE_1__ primitives ; 
 int /*<<< orphan*/  pthread_cond_signal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void async_cond_signal(int eCond){
  assert( mutex_held(ASYNC_MUTEX_QUEUE) );
  pthread_cond_signal(&primitives.aCond[eCond]);
}