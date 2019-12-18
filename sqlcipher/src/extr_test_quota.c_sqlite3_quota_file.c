#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_int64 ;
struct TYPE_11__ {TYPE_1__* pMethods; } ;
typedef  TYPE_2__ sqlite3_file ;
typedef  int /*<<< orphan*/  quotaGroup ;
typedef  int /*<<< orphan*/  quotaFile ;
struct TYPE_13__ {int szOsFile; int mxPathname; } ;
struct TYPE_14__ {TYPE_7__ sThisVfs; TYPE_5__* pOrigVfs; } ;
struct TYPE_12__ {int (* xFullPathname ) (TYPE_5__*,char const*,int,char*) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  (* xClose ) (TYPE_2__*) ;int /*<<< orphan*/  (* xFileSize ) (TYPE_2__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int SQLITE_CANTOPEN ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_READONLY ; 
 TYPE_9__ gQuota ; 
 int /*<<< orphan*/  quotaEnter () ; 
 int /*<<< orphan*/ * quotaFindFile (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * quotaGroupFind (char*) ; 
 int /*<<< orphan*/  quotaLeave () ; 
 int quotaOpen (TYPE_7__*,char*,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  quotaRemoveFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 scalar_t__ sqlite3_malloc (int) ; 
 int strlen (char*) ; 
 int stub1 (TYPE_5__*,char const*,int,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__*) ; 

int sqlite3_quota_file(const char *zFilename){
  char *zFull = 0;
  sqlite3_file *fd;
  int rc;
  int outFlags = 0;
  sqlite3_int64 iSize;
  int nAlloc = gQuota.sThisVfs.szOsFile + gQuota.sThisVfs.mxPathname+2;

  /* Allocate space for a file-handle and the full path for file zFilename */
  fd = (sqlite3_file *)sqlite3_malloc(nAlloc);
  if( fd==0 ){
    rc = SQLITE_NOMEM;
  }else{
    zFull = &((char *)fd)[gQuota.sThisVfs.szOsFile];
    rc = gQuota.pOrigVfs->xFullPathname(gQuota.pOrigVfs, zFilename,
        gQuota.sThisVfs.mxPathname+1, zFull);
  }

  if( rc==SQLITE_OK ){
    zFull[strlen(zFull)+1] = '\0';
    rc = quotaOpen(&gQuota.sThisVfs, zFull, fd,
                   SQLITE_OPEN_READONLY | SQLITE_OPEN_MAIN_DB, &outFlags);
    if( rc==SQLITE_OK ){
      fd->pMethods->xFileSize(fd, &iSize);
      fd->pMethods->xClose(fd);
    }else if( rc==SQLITE_CANTOPEN ){
      quotaGroup *pGroup;
      quotaFile *pFile;
      quotaEnter();
      pGroup = quotaGroupFind(zFull);
      if( pGroup ){
        pFile = quotaFindFile(pGroup, zFull, 0);
        if( pFile ) quotaRemoveFile(pFile);
      }
      quotaLeave();
    }
  }

  sqlite3_free(fd);
  return rc;
}