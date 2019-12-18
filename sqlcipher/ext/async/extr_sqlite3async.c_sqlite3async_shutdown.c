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
typedef  int /*<<< orphan*/  sqlite3_vfs ;
struct TYPE_2__ {scalar_t__ pAppData; } ;

/* Variables and functions */
 int /*<<< orphan*/  async_os_shutdown () ; 
 TYPE_1__ async_vfs ; 
 int /*<<< orphan*/  sqlite3_vfs_unregister (int /*<<< orphan*/ *) ; 

void sqlite3async_shutdown(void){
  if( async_vfs.pAppData ){
    async_os_shutdown();
    sqlite3_vfs_unregister((sqlite3_vfs *)&async_vfs);
    async_vfs.pAppData = 0;
  }
}