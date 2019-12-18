#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int sqlite3_int64 ;
struct TYPE_15__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
struct TYPE_16__ {int szChunk; int nReal; scalar_t__ bTruncate; int /*<<< orphan*/  bEnabled; } ;
typedef  TYPE_3__ multiplexGroup ;
struct TYPE_17__ {TYPE_3__* pGroup; } ;
typedef  TYPE_4__ multiplexConn ;
struct TYPE_14__ {int (* xTruncate ) (TYPE_2__*,int) ;} ;
struct TYPE_13__ {int /*<<< orphan*/ * pOrigVfs; } ;

/* Variables and functions */
 int SQLITE_IOERR_TRUNCATE ; 
 int SQLITE_OK ; 
 TYPE_12__ gMultiplex ; 
 int /*<<< orphan*/  multiplexSubClose (TYPE_3__*,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* multiplexSubOpen (TYPE_3__*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,int) ; 
 int stub2 (TYPE_2__*,int) ; 
 int stub3 (TYPE_2__*,int) ; 

__attribute__((used)) static int multiplexTruncate(sqlite3_file *pConn, sqlite3_int64 size){
  multiplexConn *p = (multiplexConn*)pConn;
  multiplexGroup *pGroup = p->pGroup;
  int rc = SQLITE_OK;
  if( !pGroup->bEnabled ){
    sqlite3_file *pSubOpen = multiplexSubOpen(pGroup, 0, &rc, NULL, 0);
    if( pSubOpen==0 ){
      rc = SQLITE_IOERR_TRUNCATE;
    }else{
      rc = pSubOpen->pMethods->xTruncate(pSubOpen, size);
    }
  }else{
    int i;
    int iBaseGroup = (int)(size / pGroup->szChunk);
    sqlite3_file *pSubOpen;
    sqlite3_vfs *pOrigVfs = gMultiplex.pOrigVfs;   /* Real VFS */
    /* delete the chunks above the truncate limit */
    for(i = pGroup->nReal-1; i>iBaseGroup && rc==SQLITE_OK; i--){
      if( pGroup->bTruncate ){
        multiplexSubClose(pGroup, i, pOrigVfs);
      }else{
        pSubOpen = multiplexSubOpen(pGroup, i, &rc, 0, 0);
        if( pSubOpen ){
          rc = pSubOpen->pMethods->xTruncate(pSubOpen, 0);
        }
      }
    }
    if( rc==SQLITE_OK ){
      pSubOpen = multiplexSubOpen(pGroup, iBaseGroup, &rc, 0, 0);
      if( pSubOpen ){
        rc = pSubOpen->pMethods->xTruncate(pSubOpen, size % pGroup->szChunk);
      }
    }
    if( rc ) rc = SQLITE_IOERR_TRUNCATE;
  }
  return rc;
}