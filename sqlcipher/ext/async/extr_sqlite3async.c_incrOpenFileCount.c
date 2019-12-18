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
struct TYPE_2__ {scalar_t__ nFile; int /*<<< orphan*/  ioError; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_MUTEX_QUEUE ; 
 int /*<<< orphan*/  SQLITE_OK ; 
 TYPE_1__ async ; 
 int /*<<< orphan*/  async_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  async_mutex_leave (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void incrOpenFileCount(void){
  /* We must hold the queue mutex in order to modify async.nFile */
  async_mutex_enter(ASYNC_MUTEX_QUEUE);
  if( async.nFile==0 ){
    async.ioError = SQLITE_OK;
  }
  async.nFile++;
  async_mutex_leave(ASYNC_MUTEX_QUEUE);
}