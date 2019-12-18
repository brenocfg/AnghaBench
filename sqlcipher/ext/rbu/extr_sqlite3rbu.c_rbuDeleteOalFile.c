#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ rc; scalar_t__ zErrmsg; int /*<<< orphan*/  zTarget; } ;
typedef  TYPE_1__ sqlite3rbu ;
struct TYPE_8__ {int /*<<< orphan*/  (* xDelete ) (TYPE_2__*,char*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ sqlite3_vfs ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 char* rbuMPrintf (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 TYPE_2__* sqlite3_vfs_find (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuDeleteOalFile(sqlite3rbu *p){
  char *zOal = rbuMPrintf(p, "%s-oal", p->zTarget);
  if( zOal ){
    sqlite3_vfs *pVfs = sqlite3_vfs_find(0);
    assert( pVfs && p->rc==SQLITE_OK && p->zErrmsg==0 );
    pVfs->xDelete(pVfs, zOal, 0);
    sqlite3_free(zOal);
  }
}