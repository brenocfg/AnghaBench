#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_19__ ;

/* Type definitions */
struct TYPE_23__ {int (* xOpen ) (TYPE_3__*,char const*,TYPE_4__*,int,int*) ;} ;
typedef  TYPE_3__ sqlite3_vfs ;
struct TYPE_24__ {TYPE_1__* pMethods; } ;
typedef  TYPE_4__ sqlite3_file ;
typedef  int /*<<< orphan*/  quotaGroup ;
struct TYPE_25__ {int deleteOnClose; int /*<<< orphan*/  nRef; } ;
typedef  TYPE_5__ quotaFile ;
struct TYPE_22__ {int /*<<< orphan*/ * pMethods; } ;
struct TYPE_26__ {TYPE_2__ base; TYPE_5__* pFile; } ;
typedef  TYPE_6__ quotaConn ;
struct TYPE_21__ {int iVersion; int /*<<< orphan*/  (* xClose ) (TYPE_4__*) ;} ;
struct TYPE_20__ {int /*<<< orphan*/  sIoMethodsV2; int /*<<< orphan*/  sIoMethodsV1; TYPE_3__* pOrigVfs; } ;

/* Variables and functions */
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_DELETEONCLOSE ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_WAL ; 
 TYPE_19__ gQuota ; 
 int /*<<< orphan*/  quotaEnter () ; 
 TYPE_5__* quotaFindFile (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * quotaGroupFind (char const*) ; 
 int /*<<< orphan*/  quotaLeave () ; 
 TYPE_4__* quotaSubOpen (TYPE_4__*) ; 
 int stub1 (TYPE_3__*,char const*,TYPE_4__*,int,int*) ; 
 int stub2 (TYPE_3__*,char const*,TYPE_4__*,int,int*) ; 
 int stub3 (TYPE_3__*,char const*,TYPE_4__*,int,int*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*) ; 

__attribute__((used)) static int quotaOpen(
  sqlite3_vfs *pVfs,          /* The quota VFS */
  const char *zName,          /* Name of file to be opened */
  sqlite3_file *pConn,        /* Fill in this file descriptor */
  int flags,                  /* Flags to control the opening */
  int *pOutFlags              /* Flags showing results of opening */
){
  int rc;                                    /* Result code */
  quotaConn *pQuotaOpen;                     /* The new quota file descriptor */
  quotaFile *pFile;                          /* Corresponding quotaFile obj */
  quotaGroup *pGroup;                        /* The group file belongs to */
  sqlite3_file *pSubOpen;                    /* Real file descriptor */
  sqlite3_vfs *pOrigVfs = gQuota.pOrigVfs;   /* Real VFS */

  /* If the file is not a main database file or a WAL, then use the
  ** normal xOpen method.
  */
  if( (flags & (SQLITE_OPEN_MAIN_DB|SQLITE_OPEN_WAL))==0 ){
    return pOrigVfs->xOpen(pOrigVfs, zName, pConn, flags, pOutFlags);
  }

  /* If the name of the file does not match any quota group, then
  ** use the normal xOpen method.
  */
  quotaEnter();
  pGroup = quotaGroupFind(zName);
  if( pGroup==0 ){
    rc = pOrigVfs->xOpen(pOrigVfs, zName, pConn, flags, pOutFlags);
  }else{
    /* If we get to this point, it means the file needs to be quota tracked.
    */
    pQuotaOpen = (quotaConn*)pConn;
    pSubOpen = quotaSubOpen(pConn);
    rc = pOrigVfs->xOpen(pOrigVfs, zName, pSubOpen, flags, pOutFlags);
    if( rc==SQLITE_OK ){
      pFile = quotaFindFile(pGroup, zName, 1);
      if( pFile==0 ){
        quotaLeave();
        pSubOpen->pMethods->xClose(pSubOpen);
        return SQLITE_NOMEM;
      }
      pFile->deleteOnClose = (flags & SQLITE_OPEN_DELETEONCLOSE)!=0;
      pFile->nRef++;
      pQuotaOpen->pFile = pFile;
      if( pSubOpen->pMethods->iVersion==1 ){
        pQuotaOpen->base.pMethods = &gQuota.sIoMethodsV1;
      }else{
        pQuotaOpen->base.pMethods = &gQuota.sIoMethodsV2;
      }
    }
  }
  quotaLeave();
  return rc;
}