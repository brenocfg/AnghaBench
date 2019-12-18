#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sqlite3_int64 ;
struct TYPE_5__ {int /*<<< orphan*/  f; TYPE_3__* pFile; } ;
typedef  TYPE_1__ quota_FILE ;
struct TYPE_6__ {int /*<<< orphan*/  iSize; } ;
typedef  TYPE_2__ quotaGroup ;
struct TYPE_7__ {scalar_t__ iSize; TYPE_2__* pGroup; } ;
typedef  TYPE_3__ quotaFile ;

/* Variables and functions */
 int _chsize (int /*<<< orphan*/ ,long) ; 
 int _chsize_s (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ ) ; 
 int ftruncate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  quotaEnter () ; 
 int /*<<< orphan*/  quotaLeave () ; 

int sqlite3_quota_ftruncate(quota_FILE *p, sqlite3_int64 szNew){
  quotaFile *pFile = p->pFile;
  int rc;
  if( (pFile = p->pFile)!=0 && pFile->iSize<szNew ){
    quotaGroup *pGroup;
    if( pFile->iSize<szNew ){
      /* This routine cannot be used to extend a file that is under
      ** quota management.  Only true truncation is allowed. */
      return -1;
    }
    pGroup = pFile->pGroup;
    quotaEnter();
    pGroup->iSize += szNew - pFile->iSize;
    quotaLeave();
  }
#if SQLITE_OS_UNIX
  rc = ftruncate(fileno(p->f), szNew);
#endif
#if SQLITE_OS_WIN
#  if defined(__MINGW32__) && defined(SQLITE_TEST)
     /* _chsize_s() is missing from MingW (as of 2012-11-06).  Use
     ** _chsize() as a work-around for testing purposes. */
     rc = _chsize(_fileno(p->f), (long)szNew);
#  else
     rc = _chsize_s(_fileno(p->f), szNew);
#  endif
#endif
  if( pFile && rc==0 ){
    quotaGroup *pGroup = pFile->pGroup;
    quotaEnter();
    pGroup->iSize += szNew - pFile->iSize;
    pFile->iSize = szNew;
    quotaLeave();
  }
  return rc;
}