#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int (* xDelete ) (TYPE_1__*,char const*,int) ;} ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  quotaGroup ;
struct TYPE_9__ {int deleteOnClose; scalar_t__ nRef; } ;
typedef  TYPE_2__ quotaFile ;
struct TYPE_10__ {TYPE_1__* pOrigVfs; } ;

/* Variables and functions */
 int SQLITE_OK ; 
 TYPE_7__ gQuota ; 
 int /*<<< orphan*/  quotaEnter () ; 
 TYPE_2__* quotaFindFile (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  quotaGroupDeref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * quotaGroupFind (char const*) ; 
 int /*<<< orphan*/  quotaLeave () ; 
 int /*<<< orphan*/  quotaRemoveFile (TYPE_2__*) ; 
 int stub1 (TYPE_1__*,char const*,int) ; 

__attribute__((used)) static int quotaDelete(
  sqlite3_vfs *pVfs,          /* The quota VFS */
  const char *zName,          /* Name of file to be deleted */
  int syncDir                 /* Do a directory sync after deleting */
){
  int rc;                                    /* Result code */
  quotaFile *pFile;                          /* Files in the quota */
  quotaGroup *pGroup;                        /* The group file belongs to */
  sqlite3_vfs *pOrigVfs = gQuota.pOrigVfs;   /* Real VFS */

  /* Do the actual file delete */
  rc = pOrigVfs->xDelete(pOrigVfs, zName, syncDir);

  /* If the file just deleted is a member of a quota group, then remove
  ** it from that quota group.
  */
  if( rc==SQLITE_OK ){
    quotaEnter();
    pGroup = quotaGroupFind(zName);
    if( pGroup ){
      pFile = quotaFindFile(pGroup, zName, 0);
      if( pFile ){
        if( pFile->nRef ){
          pFile->deleteOnClose = 1;
        }else{
          quotaRemoveFile(pFile);
          quotaGroupDeref(pGroup);
        }
      }
    }
    quotaLeave();
  }
  return rc;
}