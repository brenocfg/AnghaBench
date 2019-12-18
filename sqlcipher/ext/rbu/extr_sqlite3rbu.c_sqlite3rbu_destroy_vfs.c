#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ xOpen; } ;
typedef  TYPE_1__ sqlite3_vfs ;
struct TYPE_7__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ rbu_vfs ;

/* Variables and functions */
 scalar_t__ rbuVfsOpen ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_mutex_free (int /*<<< orphan*/ ) ; 
 TYPE_1__* sqlite3_vfs_find (char const*) ; 
 int /*<<< orphan*/  sqlite3_vfs_unregister (TYPE_1__*) ; 

void sqlite3rbu_destroy_vfs(const char *zName){
  sqlite3_vfs *pVfs = sqlite3_vfs_find(zName);
  if( pVfs && pVfs->xOpen==rbuVfsOpen ){
    sqlite3_mutex_free(((rbu_vfs*)pVfs)->mutex);
    sqlite3_vfs_unregister(pVfs);
    sqlite3_free(pVfs);
  }
}