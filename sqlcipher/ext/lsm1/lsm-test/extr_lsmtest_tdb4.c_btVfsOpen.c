#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite4_env ;
typedef  int /*<<< orphan*/  bt_file ;
struct TYPE_9__ {scalar_t__ pVfsCtx; } ;
typedef  TYPE_2__ bt_env ;
struct TYPE_11__ {int /*<<< orphan*/  nRef; TYPE_1__* pVfs; TYPE_3__** apFile; scalar_t__ bCrash; } ;
struct TYPE_10__ {int /*<<< orphan*/  pFile; TYPE_1__* pVfs; TYPE_4__* pBt; } ;
struct TYPE_8__ {int (* xOpen ) (int /*<<< orphan*/ *,TYPE_2__*,char const*,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_3__ BtFile ;
typedef  TYPE_4__ BtDb ;

/* Variables and functions */
 int BT_OPEN_DATABASE ; 
 int BT_OPEN_LOG ; 
 int BT_OPEN_SHARED ; 
 int SQLITE4_IOERR ; 
 int SQLITE4_NOMEM ; 
 int SQLITE4_OK ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testFree (TYPE_3__*) ; 
 scalar_t__ testMalloc (int) ; 

__attribute__((used)) static int btVfsOpen(
  sqlite4_env *pEnv, 
  bt_env *pVfs, 
  const char *zFile, 
  int flags, bt_file **ppFile
){
  BtFile *p;
  BtDb *pBt = (BtDb*)pVfs->pVfsCtx;
  int rc;

  if( pBt->bCrash ) return SQLITE4_IOERR;

  p = (BtFile*)testMalloc(sizeof(BtFile));
  if( !p ) return SQLITE4_NOMEM;
  if( flags & BT_OPEN_DATABASE ){
    pBt->apFile[0] = p;
  }else if( flags & BT_OPEN_LOG ){
    pBt->apFile[1] = p;
  }
  if( (flags & BT_OPEN_SHARED)==0 ){
    p->pBt = pBt; 
  }
  p->pVfs = pBt->pVfs; 

  rc = pBt->pVfs->xOpen(pEnv, pVfs, zFile, flags, &p->pFile);
  if( rc!=SQLITE4_OK ){
    testFree(p);
    p = 0;
  }else{
    pBt->nRef++;
  }

  *ppFile = (bt_file*)p;
  return rc;
}